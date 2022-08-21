/*******************************************************************************
	Author:      
	Reviewer:    
	Email:       
	Date:        20.04.2022
	Description: Watchdog implementation

*******************************************************************************/
#include "wd_api.h" 
#include "wd_shared_funcs.h"

/********************************declerations**********************************/
static struct sigaction sa_user = {0};
static sig_atomic_t signal_counter = 0;
static pthread_t wd_thred_id = 0;

/********************************declerations**********************************/
/*TODO*/
/*SetUserArgvToEnv*/
/****************************static_declerations*******************************/
static int PetTheDog(void *params);
static int AdoptPuppy(void *params);
static int CheckTheDog(void *params);
static void *ThreadFunction(void *params);
static void SigactionInit(struct sigaction *sa_struct, void (*handler)(int), int signum);
static int SchedStructInit(s_params_t *params, ilrd_sched_ty *sched, 
			    unsigned int frequency, unsigned int ratio,
			    int argc, const char *argv[]);
static int TerminateTheDog(void *params);

/****************************static_declerations*******************************/
static s_params_t *shared_memory_segment_ptr = NULL;
static char shared_memory_segment_id[] = {"0000000000"}; /*max uint digits = 4294967295*/
static void SignalHandler1(int signum);

/*********************************main*****************************************/
void StartWD(unsigned int freq, unsigned int ratio, int argc, const char **argv)
{
/*	pthread_t tid = 0;*/
	int sched_status = 0;
	ilrd_sched_ty *user_sched = NULL;
	int return_status = 0;

	s_params_t sched_args = {0, 0, 0, 0, NULL, NULL, 0, 0, {0}, NULL};

	user_sched = SchedCreate();
	if (NULL == user_sched)
	{
		exit (1);
	}

	sched_status = SchedStructInit(&sched_args, user_sched, freq, 
					ratio, argc, argv);
	if (0 != sched_status)
	{
		exit(1);
	}

	SchedAddTask(sched_args.user_sched, PetTheDog, &sched_args, 
		     time(NULL) +2, freq);      /*TODO check return value*/
	SchedAddTask(sched_args.user_sched, CheckTheDog, NULL, 
		     time(NULL)+(freq * ratio), (freq * ratio)); 

	wd_thred_id = pthread_create(&wd_thred_id, NULL, ThreadFunction, &sched_args);
	
/*	printf("\tJoining threads\n");*/
/*	return_status = pthread_join(wd_thred_id, NULL);*/
/*   	if ( return_status != 0 )*/
/*   	{*/
/*		printf("Error waiting: %s\n", strerror (return_status));*/
/*   	}*/
}

void StopWD()
{
    int return_status = 0;
    int stat = 0;
	sigset_t old_mask;
	sigset_t new_mask;
	sem_t *termination_semaphore = NULL;
	
	sigemptyset(&new_mask);
	sigaddset(&new_mask, SIGUSR1);
	sigprocmask(SIG_BLOCK, &new_mask, &old_mask);
	
	termination_semaphore = sem_open(SEM_NAME_TERMINATION, O_RDWR);
	if (termination_semaphore == SEM_FAILED) 
	{
		perror("termination sem_open(3) failed wd");
		exit(EXIT_FAILURE);
	}
	
	
    SchedAddTask(shared_memory_segment_ptr->user_sched, TerminateTheDog, NULL,
    				time(NULL), 0);
    
/*    printf("\tWaiting for termination semaphore\n");*/
    if (sem_wait(termination_semaphore) < 0)
	{
		 perror("termination sem_wait(3) failed user");
		 exit(1);
   	}
/*   	printf("\tGot termination semaphore\n");*/
   	
   	sleep(1);
   	waitpid(shared_memory_segment_ptr->wd_pid, &stat, WNOHANG);
   	
   	

/*	if (0 != error)*/
/*   	{*/
/*		 errno = return_status;*/
/*		 perror("pthread_join() failed");*/
/*   	}*/
   	
   	printf("After pthread_join in user\n");
   	sigprocmask(SIG_SETMASK, &old_mask, NULL);
   	
   	return_status = pthread_join(wd_thred_id, NULL);
  	if ( return_status != 0 )
   	{
		printf("Error waiting: %s\n", strerror (return_status));
   	}
   	
   	/*if ( return_status != 0 )
	{
		printf("Error waiting: %s\n", strerror (return_status));
  	}*/
   /*sem unlink*/
   
    /*To kill WD process we need:
    
    - send SIGUSR2
    - wait for reply / check a shared flag_position
    - pause scheduler (pass scheduler pointer via shared mem)
    - clean scheduler from leftover tasks
    - free memory
    - join thread back to main processes (pass thread id via shared mem?)
    -return success
    */
    return;
}
/*********************************main*****************************************/
/********************************static_funcs**********************************/
static void SignalHandler1(int signum)
{
	signal_counter = 0;
	(void)signum;
}
static void SigactionInit(struct sigaction *sa_struct, void (*handler)(int), int signum)
{
	int sig_ret = 0;
	sa_struct->sa_flags = SA_SIGINFO;
	sigemptyset(&sa_struct->sa_mask);
	sa_struct->sa_handler = handler;
	
	sig_ret = sigaction(signum, sa_struct, NULL);
	if (-1 == sig_ret)
	{
		exit(-1);
	}
}

/*int SetUserArgvToEnv(int argv, char **argc)*/
/*{*/
/*	int return_status = 0;*/
/*	int i = 0;*/
/*	*/
/*	return_status = setenv("USER_ARGV", argc, int overwrite)*/
/*	*/
/*	*/
/*	*/
/*	*/
/*}*/

static int AdoptPuppy(void *params)
{
	pid_t puppy_pid = 0;
	/*int stat = 0;*/
	char *argv[] = {"../out/puppy.out", 
			shared_memory_segment_id, NULL};
	puppy_pid = ChildCreation(argv);
	(void)params;
	return puppy_pid;
}


static int CheckTheDog(void *params)
{
	int return_status = 0;
	/*need somtehing else as an arg*/
	if (1 < signal_counter)
	{
		printf("\t**Puppy didn't respond, REVIVING**\n");
		
		kill(shared_memory_segment_ptr->wd_pid, SIGTERM);
		wait(NULL);
		
		return_status = AdoptPuppy(NULL);
		/*TODO add semaphore to make sure puppy has sigaction ready*/
		if (-1 == return_status)
		{
			perror("WD fork error");
			return return_status;
		}
	}
	(void)params;
	return 0;
}


static int TerminateTheDog(void *params)
{
	pid_t wd_pid = shared_memory_segment_ptr->wd_pid;
	int sig_ret = 0;
	
	
/*	printf("watchdog pid: %d\n", wd_pid);*/
	while (0 == termination_flag)
	{
		sig_ret = kill(wd_pid, SIGUSR2);
		
		if (-1 == sig_ret)
		{
			perror("signaling failed from wd_api");
			exit(-1);
		}
		sleep(5);
	}
	
	printf("flag: %d\n", termination_flag);
	/*TODO check return status if success*/
	SchedPause(shared_memory_segment_ptr->user_sched);
	(void)params;
	return 0;
}


static int PetTheDog(void *params)
{
	s_params_t arguments = *(s_params_t *)params;
	pid_t wd_pid = arguments.wd_pid;
	int sig_ret = 0;
	
/*	printf("wd_pid %d\n", wd_pid);*/
	
	sleep(1);

	write(0, "Bark bark\n", 10);
	printf("counter %d\n", signal_counter);
	
	++signal_counter;
	
	sig_ret = kill(wd_pid, SIGUSR1);
	if (-1 == sig_ret)
	{
		perror("signaling failed from wd_api");
		exit(-1);
	}
	
	/*if termination flag = 1 schedstop*/
	return 0;
}


size_t GetSizeOfArgv(int argc, char **argv)
{
	int i = 0;
	size_t argument_len = 0;
	
	for (i = 0; i < argc; i++)
	{
		argument_len += (strlen(argv[i]) +1); /*TODO maybe add another byte for space*/
	} 
	printf("argument_len %lu\n",argument_len);
	
	return argument_len;
}

void CopyArgvToStruct(int argc, char **argv, s_params_t *info_struct)
{
	int i = 0;
	
	for (i = 0; i < argc; i++)
	{
/*		strcpy(info_struct->argv[i], argv[i]);*/
		memcpy(&info_struct->argv[i], argv[i], strlen(argv[i]) +1);
		
	}
}

void CopyArgvToStructShmem(int argc, char **argv, s_params_t *info_struct)
{
	int i = 0;
	
	for (i = 0; i < argc; i++)
	{
		memcpy(&info_struct->argv[i], argv[i], strlen(argv[i]) +1);
	}
}

static void *ThreadFunction(void *params)
{
	/*what's up with this?*/
/*	int stat = 0;*/
	pid_t puppy_pid = 0;
	char *args[] = {"../out/puppy.out", NULL, NULL};

	s_params_t *arguments = (s_params_t *)params;
	sem_t *termination_semaphore = NULL;
	sem_t *semaphore = NULL;
	s_params_t *shared_memory = NULL;
	size_t argv_len = GetSizeOfArgv(arguments->argc, &arguments->argv);
	
	int segment_id = shmget(IPC_PRIVATE, sizeof(s_params_t) + argv_len, 
					 IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);
	
	int len = snprintf( NULL, 0, "%d", segment_id);

	SigactionInit(&sa_user, SignalHandler1, SIGUSR1);


	snprintf(shared_memory_segment_id, len + 1, "%d", segment_id);
	args[1] = shared_memory_segment_id;
	printf("static segm id: %s\n", shared_memory_segment_id);
	sem_unlink(SEM_NAME);
	semaphore = sem_open(SEM_NAME, O_CREAT | O_EXCL, SEM_PERMS, 
			      INITIAL_VALUE);
	if (semaphore == SEM_FAILED) 
	{
		sem_destroy(semaphore);
		perror("sem_open(3) error");
		exit(EXIT_FAILURE);
	}
	
	sem_unlink(SEM_NAME_TERMINATION);
	termination_semaphore = sem_open(SEM_NAME_TERMINATION, O_CREAT | O_EXCL, SEM_PERMS, 
			      		 INITIAL_VALUE);
	if (termination_semaphore == SEM_FAILED) 
	{
		sem_destroy(termination_semaphore);
		perror("termination sem_open(3) error");
		exit(EXIT_FAILURE);
	}
	/*made it a pointer, it didn't update the thingieloo*/
	arguments->user_pid = getpid();
	CopyArgvToStruct(arguments->argc, &arguments->argv, arguments);
	
	strcpy(arguments->user_exec_name, &arguments->argv[0]);
	
	
	arguments->wd_pid = AdoptPuppy(args);
	if (-1 == puppy_pid)
	{
		exit(-1);
	}
	
	shared_memory_segment_ptr = (s_params_t *)shmat(segment_id, NULL, 0);
	if ((void*)-1 == shared_memory_segment_ptr) 
	{
		perror("shmat() error");
		exit(1);
	}

	printf("user segment_id %d\n", segment_id);

	memcpy(shared_memory_segment_ptr, arguments, sizeof(s_params_t)+ argv_len);
	
	CopyArgvToStructShmem(arguments->argc, &arguments->argv, shared_memory_segment_ptr);
	
	if (sem_wait(semaphore) < 0) 
	{
		 perror("sem_wait(3) failed on user thread");
		 exit(1);
   	}

	SchedRun(arguments->user_sched);
	
	/*TODO cleanup functionality*/
	SchedClear(arguments->user_sched);
	SchedDestroy(arguments->user_sched);
	
	
	if (sem_post(semaphore) < 0)
	{
		perror("sem_post(3) error on child");
	}
	/*wait(&stat);*/
	printf("user prosess terminating - should never reach here\n");
	return NULL;
}

static int SchedStructInit(s_params_t *params, ilrd_sched_ty *sched, 
			    unsigned int frequency, unsigned int ratio,
			    int argc, const char *argv[])
{
	params->argc = argc;
	params->argv = *(char **)argv;
	params->wd_pid = 0;
	params->user_pid = 0;
	params->user_sched = sched;
	params->frequency = frequency;
	params->ratio = ratio;
	return 0;
}

/********************************static_funcs**********************************/







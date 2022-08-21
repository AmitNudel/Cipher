/*******************************************************************************
	Author:      Anna Kravtsova
	Reviewer:    
	Email:       
	Date:        21.04.2022
	Description: Watchdog

*******************************************************************************/
#include "wd_api.h" 
#include "wd_shared_funcs.h"
/********************************declerations**********************************/
static struct sigaction sa_puppy = {0};
static struct sigaction sa_puppy_term = {0};
static sig_atomic_t signal_counter = 0;
/********************************declerations**********************************/

/****************************static_declerations*******************************/
static void CleanupFunction(void);
static int LickTheUser(void *params);
static int ReviveTheUser(void *params);
static s_params_t *shared_memory_segment = NULL;
static void SignalHandler2(int signum);
static void SignalHandler1(int signum);
static int CheckTheOwner(void *params);
static void SigactionInit(struct sigaction *sa_struct, void (*handler)(int), int signum);
/*static void TerminateProcess(void);*/

/****************************static_declerations*******************************/
/*TODO*/
/*SchedInit*/
/*SharedMemInit*/
/*SemInit*/
/*Cleanup*/





/*********************************main*****************************************/
int main(int argc, const char *argv[])
{
	ilrd_sched_ty *pup_sched = NULL;
	s_params_t *shared_memory = NULL;
	int segment_id = atoi(argv[1]);
	unsigned int ratio = 0;
	pid_t user_pid = 0;
	unsigned int freq = 0;
	int return_status = 0;
	sem_t *termination_semaphore = NULL;
	sem_t *semaphore = NULL;
	
	semaphore = sem_open(SEM_NAME, O_RDWR);
	if (semaphore == SEM_FAILED) 
	{
		perror("sem_open(3) failed wd");
		exit(EXIT_FAILURE);
	}
	
	termination_semaphore = sem_open(SEM_NAME_TERMINATION, O_RDWR);
	if (termination_semaphore == SEM_FAILED) 
	{
		perror("termination sem_open(3) failed wd");
		exit(EXIT_FAILURE);
	}
	
	shared_memory_segment = (s_params_t *)shmat(segment_id, NULL, 0);
	if ((void*)-1 == shared_memory_segment)
	{
		perror("shmat() error wd");
		exit(1);
	}
	
	user_pid = shared_memory_segment->user_pid;
	freq = shared_memory_segment->frequency;
	ratio = shared_memory_segment->ratio; 
	
	shared_memory_segment->wd_pid = getpid();
	
	printf("puppy pid %d\n", shared_memory_segment->wd_pid);
	printf("user pid %d\n", shared_memory_segment->user_pid);

	
	SigactionInit(&sa_puppy, SignalHandler1, SIGUSR1);
	SigactionInit(&sa_puppy_term, SignalHandler2, SIGUSR2);
		
	pup_sched = SchedCreate();
	if (NULL == pup_sched)
	{
		perror("SchedCreate error wd");
		exit(-1);
	}
	
	shared_memory_segment->wd_sched = pup_sched;

	SchedAddTask(pup_sched, LickTheUser, &user_pid, time(NULL) +2, freq);
	SchedAddTask(pup_sched, CheckTheOwner, NULL, time(NULL) + (ratio * freq) + 1, freq * ratio);
	
	if (sem_post(semaphore) < 0)
	{
		perror("sem_post(3) error1 on child");
	}
    
	SchedRun(pup_sched);
	/*TODO cleanup functionality*/
/*	printf("\tAfter SchedRun\n");*/
	SchedClear(shared_memory_segment->wd_sched);
/*	printf("\tAfter SchedClear\n");*/
	SchedDestroy(shared_memory_segment->wd_sched);
/*	printf("\tAfter SchedDestroy\n");*/
	
	printf("\tPosting termination semaphore\n");
	if (sem_post(termination_semaphore) < 0)
	{
		perror("termination sem_post(3) error2 on wd");
	}
/*	TerminateProcess();*/
	(void)argc;
	return 0;
}

/*********************************main*****************************************/

/********************************static_funcs**********************************/
static void SignalHandler1(int signum)
{
	signal_counter = 0;
	(void)signum;
}
static void SignalHandler2(int signum)
{
	termination_flag = 1;
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
		perror("sigaction failed");
		exit(-1);
	}
}

static void CleanupFunction(void)
{
	printf("imagine things are cleaning up\n");
/*	SchedClear(shared_memory_segment->wd_sched);*/
/*	SchedAddTask(shared_memory_segment->pup_sched, ReviveTheUser, NULL, time(NULL)+1, 0);*/
/*	SchedRun(shared_memory_segment->wd_sched);*/
/*	SchedDestroy(shared_memory_segment->wd_sched);*/
	return;
}

static int ReviveTheUser(void *params)
{
	int sig_ret = 0;
	pid_t user_pid = 0;
	/*argv[1] -> [2]*/
	char *argv[2] = {NULL, NULL};
	argv[0] = shared_memory_segment->user_exec_name;
	argv[1] = NULL;

	user_pid = ChildCreation(argv);

	SchedPause(shared_memory_segment->wd_sched);
/*	CleanupFunction();*/
	
	/*(instead of getpid())*/
	/*sig_ret = kill(params->wd_pid, SIGTERM);*/
	/*if (-1 == sig_ret)
	{
		printf("signaling failed from watchpuppy\n");
		perror("Puppy:");
		exit(-1);
	}*/
	(void)params;
	return 1;
}
	
static int CheckTheOwner(void *params)
{
	int return_status = 0;

	/*printf("\t***Reviving user***\n");*/
	/*SchedAddTask(shared_memory_segment->wd_sched, ReviveTheUser, NULL, 
		     time(NULL)+1, 0);*/
	/*need somtehing else as an arg*/
	if (1 < signal_counter)
	{
		printf("\t**Owner didn't respond**\n");
		/*zombie treatment*/
		kill(shared_memory_segment->user_pid, SIGTERM);
		wait(NULL);
		
		if (0 == termination_flag)
		{
			ReviveTheUser(params);
		}
		else if (0 != termination_flag)
		{
			SchedPause(shared_memory_segment->wd_sched);
		}
		return 1;
	}
	
	(void)params;
	return 0;
}

static void TerminateProcess(void)
{
	pid_t wd_pid = getpid();
	int sig_ret = 0;
	sig_ret = kill(wd_pid, SIGTERM);
	if (-1 == sig_ret)
	{
		perror("SIGTERM Puppy");
	}
}


static int LickTheUser(void *params)
{
	pid_t user_pid = *(pid_t *)params;
	int sig_ret = 0;
	
	sleep(1);
	
	write(0, "\twoof woof\n", 12);
	++signal_counter;
	
	sig_ret = kill(user_pid, SIGUSR1);
	/*if (-1 == sig_ret || 1 > signal_counter)
	{
		perror("Puppy signaling failed:");
		printf("%d\n", termination_flag);
		
		if (0 == termination_flag)
		{
			ReviveTheUser(params);
		}
		else if (0 != termination_flag)
		{
			SchedPause(shared_memory_segment->wd_sched);
		}
		exit(-1);
	}*/
	return 0;
}
/********************************static_funcs**********************************/



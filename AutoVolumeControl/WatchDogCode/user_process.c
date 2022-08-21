/*******************************************************************************
	Author:      
	Reviewer:    
	Email:       
	Date:        20.04.2022
	Description: Watchdog implementation

*******************************************************************************/
#include "wd_api.h" 

int main(int argc, const char *argv[])
{
    unsigned int frequency = 4;
    unsigned int ratio = 4;
    
    time_t end = time(NULL) +20;
    
    StartWD(frequency, ratio, argc, argv);
    
    while (time(NULL) <= end)
    {
	/*empty loop*/
    }
	
    StopWD();
    return 0;
}

/*
snprintf(shared_memory_segment_id, len + 1, "%d", segment_id);
	int segment_id = atoi(argv[1]);
	int len = snprintf( NULL, 0, "%d", segment_id);
static char shared_memory_segment_id[] = {"0000000000"}; max uint digits = 4294967295*/


#include "stdlib.h"

#include "main.h"

/* #include "main.c" */

const char url[] = "https://www.youtube.com/watch?v=ndsaoMFz9J4&ab_channel=Markiplier";

void RunningProgram()
{
    pthread_t program_run;
    
    while(1)
    {
        pthread_create(&program_run, NULL, ProgramRun, NULL);    
    }
}

void PlaySound()
{
    char *youtube_video = NULL;
    asprintf(&youtube_video, "START %s", url);
    system(youtube_video);
    free(youtube_video);

}

int main()
{
    PlaySound();

}
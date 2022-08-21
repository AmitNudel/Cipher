#ifndef _AutoVolumeControl_Amit_Nudel__
#define _AutoVolumeControl_Amit_Nudel__

#include <stdio.h> /*printf*/
#include <alsa/asoundlib.h> /*alsa*/
#include <pthread.h>    /*pthread_create, pthread_join*/
#include <sys/types.h>
/* #include <unistd.h>
 */

void *ProgramRun(void *arg);
long UserPrompt();
void *Average(void *avg); /*do I need this one in here?*/
/* static float GetLevel(void); */
void SetAlsaMasterVolume(long volume);

#endif /* _AutoVolumeControl_Amit_Nudel_ */
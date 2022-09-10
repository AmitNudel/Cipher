#ifndef _AutoVolumeControl_Amit_Nudel__
#define _AutoVolumeControl_Amit_Nudel__


#include <alsa/asoundlib.h> /*alsa*/
#include <sys/types.h>

void *ProgramRun(void *arg);
void AmplitudeAverage(float *avg);
void SetAlsaMasterVolume(long volume);
float GetAmplitudeLevel(void);
float dBToFloat(int db);
int FloatTodB(float num_float);
int CheckIfEarphonePlugged();

#endif /* _AutoVolumeControl_Amit_Nudel_ */
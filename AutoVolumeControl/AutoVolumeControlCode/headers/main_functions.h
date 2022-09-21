#ifndef _AutoVolumeControl_Amit_Nudel__
#define _AutoVolumeControl_Amit_Nudel__


#include <alsa/asoundlib.h> /*alsa*/
#include <sys/types.h>

void ProgramRun();
void AmplitudeAverage(float *avg);
void SetAlsaMasterVolume(long volume);
float GetAmplitudeLevel(void);
float dBToAmp(int db);
int AmpTodB(float num_float);
int IsEarphonePlugged();

#endif /* _AutoVolumeControl_Amit_Nudel_ */


#include <stdio.h>
#include "main_functions.h"
#include "tests.h"
#include "math.h"


void SoundTest()
{
    //play sound 1 -> chck pcm 
    //play sound 2 -> chck pcm
    //play sound 3 -> chck pcm
    //what ar th diffrncs btwn th pcm rsults? chck again, agftr chnaginc th bar to hight/lowr 
    
}


void AmplitudeTest()
{
    float amplitude = GetAmplitudeLevel();
    printf("%f\n", amplitude);
    int dB = FloatTodB(amplitude);
    printf("dB: %i\n", dB);

    dB = FloatTodB(1000.0);
    printf("dB: %i\n", dB);

    amplitude = dBToFloat(60);
    printf("%f\n", amplitude);

    amplitude = dBToFloat(89);
    printf("%f\n", amplitude);
}

void Tests()
{
    AmplitudeTest();
}
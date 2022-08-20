#include "main.h"

void SetAlsaMasterVolume(long volume)
{
    long min, max;
    snd_mixer_t *handle;
    snd_mixer_selem_id_t *sid;
    const char *card = "default";
    const char *selem_name = "Master";

    snd_mixer_open(&handle, 0);
    snd_mixer_attach(handle, card);
    snd_mixer_selem_register(handle, NULL, NULL);
    snd_mixer_load(handle);

    snd_mixer_selem_id_alloca(&sid);
    snd_mixer_selem_id_set_index(sid, 0);
    snd_mixer_selem_id_set_name(sid, selem_name);
    snd_mixer_elem_t* elem = snd_mixer_find_selem(handle, sid);

    snd_mixer_selem_get_playback_volume_range(elem, &min, &max);
    snd_mixer_selem_set_playback_volume_all(elem, volume * max / 100);

    snd_mixer_close(handle);
}


static float GetLevel(void)
{
    float result = 0.0f;
    snd_pcm_t* waveform;

    // Open and initialize a waveform
    if (snd_pcm_open (&waveform, "default",
        SND_PCM_STREAM_PLAYBACK, 0) != 0)
        return 0;

    // Set the hardware parameters
    if (!snd_pcm_set_params (waveform, SND_PCM_FORMAT_S16_LE,
        SND_PCM_ACCESS_RW_INTERLEAVED, 2, 48000, 1, 0))
    {
        // Read current samples
        short buffer[256];
        if (snd_pcm_readi (waveform, buffer, 128) == 128)
        {
            // Compute the maximum peak value
            for (int i = 0; i < 256; ++i)
            {
                // Substitute better algorithm here if needed
                float s = buffer[i] / 32768.0f;
                if (s < 0) s *= -1;
                if (result < s) result = s;
            }
        }
    }

    snd_pcm_close (waveform);
    return result;
}
//on a different thread? 
void *Average(void *avg)
{
    float level = 0.0;
    for(int i = 0; i < 10; i++)
    {
        level += GetLevel();
    }
    *((long*)avg) = (long)(level / (float)10);
    pthread_exit(avg);
}

/*do I really need to use long?*/
/*later will turn to the user profiling*/
long UserPrompt()
{
    char user_input[10] = {0};
    long user_volume = 0;
    printf("AutoVolumeControl\n");
    /* do
    {
        printf("Enter a volume level (0-100): ");
        fgets(user_input, sizeof(user_input), stdin);
        user_volume = atoi(user_input);
    }while(0 > user_volume || 100 < user_volume || user_input[0] == '\n' ); */
    
    return user_volume;
}
/*how to change the volume, so it fit's the users, not only in the beggining...*/
/* void SoundLevelBeggining(long user_volume)
{
    float current_level = GetLevel();
    if (current_level != user_volume)
    {
        SetAlsaMasterVolume(user_volume);
    }

} */

void *ProgramRun(void *arg)
{
    pthread_t avg_thread;

    long user_volume = UserPrompt();
    long average = 0.0;

    SetAlsaMasterVolume(user_volume);
    /*might wanna put a flag in here, so user can stop whenever?*/
    /*how the progrsm can remember user's preferences?*/
    /*if program is killed in the middle, accident...whatchdog?*/
    while(1)
    {
        pthread_create(&avg_thread, NULL, Average, &average);
        average > user_volume ? SetAlsaMasterVolume(average - user_volume) 
                              : SetAlsaMasterVolume(user_volume - average); 
    }
    pthread_join(avg_thread, NULL);
}
int main()
{

    ProgramRun(NULL);

    /* while(1)
    {
        SetAlsaMasterVolume(user_volume);
    } */
/* 
    while(1)
    {
        pthread_create (&avg_thread, NULL, Average, &average);
        if (average > user_volume)
        {
            SetAlsaMasterVolume(user_volume);
        } 
         else if (average < user_volume)
        {
            SetAlsaMasterVolume(user_volume);
        }
    }  */

    /* long average = Average();
    printf("%ld\n", average); */
    
 /*    pthread_join(avg_thread, NULL); */
/*     return 0; */
} 
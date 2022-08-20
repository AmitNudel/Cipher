#include "main.h"

const int MAX_SOUND_RATE = 3;

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

int CheckIfEarphonePlugged()
{
    char wanted_input[] = 
    "analog-output-headphones: Headphones (priority 9900, latency offset 0 usec, available: yes)";

    char output_from_alsa[256]; 
    
    system("pacmd list-cards > jack_info.txt");

    FILE *jack_info_file = fopen("jack_info.txt", "r");

    if (NULL == jack_info_file)
    {
        fclose(jack_info_file);
        perror("Error opening jack_info.txt");
    }

   
    while(fgets(output_from_alsa, sizeof(output_from_alsa), jack_info_file))
    {
        if (strstr(output_from_alsa, wanted_input))
        {
            fclose(jack_info_file);
            return 1;
        }
    }
    
    fclose(jack_info_file);
    return 0;

}
long CheckAvgFirstTime()
{
    /*check sound for three times - 
    write down how low/high was the sound to the user
    and return the avg, as the first indecation for the system's sound
    (should be between 0-100)*/
    /*TODO - solve how to record the the avg, so next time user can just run the program*/
    /*laster on - user can make a new profile for another user/ changes their's*/
    long rating = 0;
    char *user_input = (char *)malloc(sizeof(char) * 10);
    printf("Rate the following sounds from 1 to 5, how loud they were:\n");
    printf("1 - Very quiet\n");
    printf("2 - Quiet\n");
    printf("3 - Normal\n");
    printf("4 - Loud\n");
    printf("5 - Very loud\n");
    printf("\n");

    for(int i = 0; i < MAX_SOUND_RATE; i++)
    {
        printf("Sound %d: ", i+1);
        sleep(1); /*will play here the sound and at the end will give the option to answer*/
        printf("\n");
        printf("Please rate the sound: ");
        fgets(user_input, sizeof(rating), stdin); /*add protection for numbers between 1-5 only*/
        rating += atoi(user_input);
    }
    /*if too high/ too low, run the test again until you get a better avg, then pass it to the set master*/
    
    /*keep user_input to a file, so next time it can be reclaimed*/
   
    free(user_input);
    return (rating / MAX_SOUND_RATE) * 10;
}
/*do I really need to use long?*/
/*later will turn to the user profiling*/
long UserPrompt()
{
    char user_input[10] = {0};
    /* long user_volume = 0; */
    printf("AutoVolumeControl\n");
    printf("\n");

    /*check if user input already exists, if no - then check if earphones are plugged and everything../*/

    if (0 == CheckIfEarphonePlugged())
    {
        printf("Please plug in your earphone and run again.\n");
        return 0; /*is this the right method?*/
    }

    return CheckAvgFirstTime();

}

void *ProgramRun(void *arg)
{
    pthread_t avg_thread;
    
    long user_volume = UserPrompt();
    /* long average = 0.0; */
    printf("Running...");
    while(1)
    {
        /*bug : if volume is at 0, it doesn't move*/
        SetAlsaMasterVolume(user_volume);
    }

    /*might wanna put a flag in here, so user can stop whenever?*/
    /*how the progrsm can remember user's preferences?*/
    /*if program is killed in the middle, accident...whatchdog?*/
    /* while(1)
    {
        pthread_create(&avg_thread, NULL, Average, &average);
        average > user_volume ? SetAlsaMasterVolume(average - user_volume) 
                              : SetAlsaMasterVolume(user_volume - average); 
    }
    pthread_join(avg_thread, NULL);*/
} 
int main()
{
    ProgramRun(NULL);
    return 0;
} 
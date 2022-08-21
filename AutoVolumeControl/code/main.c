#include "main.h"

const int MAX_SOUND_RATE = 3;
/* const char USER_FILE[] = "/home/myth/Desktop/'my projects'/AutoVolumeControl/user_output/user_profile_1.txt"; */
const int BASIC_BUFFER_SIZE = 256;

void SetAlsaMasterVolume(long volume)
{
    long min = 0;
    long max = 0;
    snd_mixer_t *handle = NULL;
    snd_mixer_selem_id_t *sid = NULL;
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

static float GetAmplitudeLevel(void)
{
    float result = 0.0f;
    snd_pcm_t* waveform = NULL;
    short current_samples_buffer[BASIC_BUFFER_SIZE] = {0};

    /*Open and intialize waveform*/
    if (0 != snd_pcm_open(&waveform, "default",
        SND_PCM_STREAM_PLAYBACK, 0))
    {
        printf("Failed to open and initialize waveform\n");
        return result;
    }

    /*Set the hardware parameters*/
    if (!snd_pcm_set_params (waveform, SND_PCM_FORMAT_S16_LE,
        SND_PCM_ACCESS_RW_INTERLEAVED, 2, 48000, 1, 0) &&
        128 == snd_pcm_readi(waveform, current_samples_buffer, 128))
    { 
        /*Compute the maximum peak value*/
        for (int i = 0; i < BASIC_BUFFER_SIZE; ++i)
        {
            float sound = current_samples_buffer[i] / 32768.0f;
            if (sound < 0) 
            {
                sound *= -1;
            }

            if (result < sound) 
            {
                result = sound;
            }
        }
        
    }
    snd_pcm_close(waveform);
    return result;
}

/*on a different thread? */
void *Average(void *avg)
{
    float level = 0.0;
    for(int i = 0; i < 10; i++)
    {
        level += GetAmplitudeLevel();
    }
    *((long*)avg) = (long)(level / (float)10);
    pthread_exit(avg);
}

int CheckIfEarphonePlugged()
{
    char wanted_input[] = 
    "analog-output-headphones: Headphones (priority 9900, latency offset 0 usec, available: yes)";

    char output_from_alsa[BASIC_BUFFER_SIZE] = {0}; 
    
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

void SaveUserProfile(int rating)
{
    /*add in the future option for more users*/
    /*file address should't be hardcoded*/
    FILE *user_profile = fopen("/home/myth/Desktop/my_projects/AutoVolumeControl/user_output/user_profile_1.txt", "w");
    if (NULL == user_profile)
    {
        perror("Error opening user_profile.txt");
        exit(1);
    }
    fprintf(user_profile, "%d", rating);
    fclose(user_profile);
}

void RatingSoundText()
{
     /*file address should't be hardcoded*/
    FILE *rating_sound_text = fopen("/home/myth/Desktop/my_projects/AutoVolumeControl/texts/rating_sounds.txt", "r");
    char rating_sound_text_buffer[BASIC_BUFFER_SIZE] = {0};

    if (NULL == rating_sound_text)
    {
        perror("Error opening rating_sound_text.txt");
        exit(1);
    }
    while (fgets(rating_sound_text_buffer, sizeof(rating_sound_text_buffer), rating_sound_text))
    {
        printf("%s", rating_sound_text_buffer);
    }
    fclose(rating_sound_text);
}

long CheckAvgFirstTime()
{
    /*check sound for three times - 
    write down how low/high was the sound to the user
    and return the avg, as the first indecation for the system's sound
    (should be between 0-100)*/
    /*laster on - user can make a new profile for another user/ changes their's*/
    long rating = 0;
    char *user_input = (char *)malloc(sizeof(char) * 10);
    
    RatingSoundText();
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
    rating = (rating / MAX_SOUND_RATE) * 10;
    SaveUserProfile(rating);

    free(user_input);
    return rating;
}
/*do I really need to use long?*/
/*later will turn to the user profiling*/

long CheckIfUserProfileExists()
{
    /*file address should't be hardcoded*/
    FILE *user_profile = fopen("/home/myth/Desktop/my_projects/AutoVolumeControl/user_output/user_profile_1.txt", "r");
    char *user_input = (char *)malloc(sizeof(char));

    if (NULL == user_profile)
    {
        return 0;
    }
    
    fgets(user_input, sizeof(user_input), user_profile);
    fclose(user_profile);
    return atoi(user_input);
    /*how do I prevent the user from creating a profile of 0? is it necessery?*/
}

long UserProfiling()
{
    /*check if user input already exists, if no - then check if earphones are plugged and everything..*/
    while(!CheckIfEarphonePlugged())
    {
        printf("Please plug in your headphones\n");
        sleep(5);
        system("clear");
    }
    long user_profile = CheckIfUserProfileExists();
    return 0 == user_profile ? CheckAvgFirstTime() : user_profile;
}

void *ProgramRun(void *arg)
{
    /* pthread_t avg_thread = 0; */
    (void)arg;
    long user_volume = UserProfiling();

    system("clear");
    printf("Running...\n");
    
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
    printf("AutoVolumeControl\n");
    printf("\n");

    ProgramRun(NULL);
    return 0;
} 
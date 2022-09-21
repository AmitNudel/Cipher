#include <math.h> /*log, pow*/

#include "main_functions.h"
#include "user_functions.h"


const char *JACK_INFO_FILE = "/home/myth/Desktop/my_projects/AutoVolumeControl/texts/jack_info.txt";


float dBToAmp(int db)
{
    return (float)pow(10.0 ,((double)db / 20.0));
}


int AmpTodB(float num_float)
{
    return (int)log10(num_float) * 20;
}

/**
 * @ set computer audio volume to wanted value
 */
void SetAlsaMasterVolume(long volume)
{
    long min = 0;
    long max = 0;
    snd_mixer_t *handle = NULL;
    snd_mixer_selem_id_t *sid = NULL;
    const char *card = "default";
    const char *selem_name = "Master";

    /*handling the mixer handler and initializing it*/
    snd_mixer_open(&handle, 0);
    snd_mixer_attach(handle, card);
    snd_mixer_selem_register(handle, NULL, NULL);
    snd_mixer_load(handle);
    
    /*getting id of mixer and setting name*/
    snd_mixer_selem_id_alloca(&sid);
    snd_mixer_selem_id_set_index(sid, 0);
    snd_mixer_selem_id_set_name(sid, selem_name);
    snd_mixer_elem_t* elem = snd_mixer_find_selem(handle, sid);
    
    /*getting volume range and setting to wanted volume*/
    snd_mixer_selem_get_playback_volume_range(elem, &min, &max);
    snd_mixer_selem_set_playback_volume_all(elem, volume * max / 100);

    snd_mixer_close(handle);
    handle = NULL; 
}


float GetAmplitudeLevel(void)
{
    float result = 0.0f;
    /*audio stream source*/
    snd_pcm_t* waveform = NULL;
    short current_samples_buffer[BASIC_BUFFER_SIZE] = {0};

    /*Open and intialize waveform*/
    if (0 != snd_pcm_open(&waveform, "default",
        SND_PCM_STREAM_CAPTURE, 0))
    {
        perror("Failed to open and initialize waveform\n");
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
            // float sound = current_samples_buffer[i] / 32768.0f;
            float sound = current_samples_buffer[i];
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

//do I need outparam here?
void AmplitudeAverage(float *out_avg)
{
    float amp_level = 0.0;
    for(int i = 0; i < 10; i++)
    {
        amp_level += GetAmplitudeLevel();
    }
    *out_avg = (amp_level / 10.0F);

}

int IsEarphonePlugged()
{
    /*exact sentence needed*/
    char wanted_input[] = 
    "analog-output-headphones: Headphones (priority 9900, latency offset 0 usec, available: yes)";

    char output_from_alsa[BASIC_BUFFER_SIZE] = {0}; 
    int result = 0;

    system("pacmd list-cards > /home/myth/Desktop/my_projects/AutoVolumeControl/texts/jack_info.txt");

    FILE *jack_info_file = fopen(JACK_INFO_FILE, "r");

    if (NULL == jack_info_file)
    {
        fclose(jack_info_file);
        perror("Error opening jack_info.txt");
    }

    /*jack info file, looking foe the wanted sentece*/
    while(fgets(output_from_alsa, sizeof(output_from_alsa), jack_info_file))
    {
        if (strstr(output_from_alsa, wanted_input))
        {
            result = 1;
        }
    }
    
    fclose(jack_info_file);
    return result;
}


void ProgramRun()
{
    /*get rating from user*/
    long user_volume = UserProfiling();
    
    system("clear");
    printf("Running...\n");
    SetAlsaMasterVolume(user_volume);
    while(1)
    {
        /*sample current volume*/
        /*calculate the fix*/
        /*adjust volume - calculate, and set the user*/
    }
}

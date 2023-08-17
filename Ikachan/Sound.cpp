#include "Sound.h"
#include "System.h"
//#include <dsound.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>

#include "File.h"

#include "nds.h"
#include "soundFifo.h"

#include <algorithm>
#include <math.h>

#include "Generic.h"

#include "fopen.h"

#define clamp(x, y, z) ((x > z) ? z : (x < y) ? y : x)

//DirectSound objects
SOUNDBUFFER* lpPRIMARYBUFFER;

//DirectSound buffers
#define SE_MAX 512
SOUNDBUFFER* lpSECONDARYBUFFER[SE_MAX];

#define NUM_CHANNELS 16

char channelStates[NUM_CHANNELS] = {0};

s8 getFreeChannel(void)
{
	for(u8 i=0;i<16;i++)
	{	
		if(!channelStates[i])
		{
			return i;
		}
			
	}
	return -1;
}



//Keep track of all existing sound buffers
SOUNDBUFFER *soundBuffers;


void updateChannelStates(void)
{
	//todo: optimize this
	//if a one-shot sound has passed all of its samples already, make channelStates[channel] free
	for (SOUNDBUFFER *sound = soundBuffers; sound != NULL; sound = sound->next)
	{
		if(sound->playing && sound->looping == false)
		{
			if(sound->timer++ * (sound->frequency / 63) > sound->size) // samples in a frame plus a bit
			{
				// TODO: give organbuffer priority
				sound->playing = false;
				channelStates[sound->channelId] = 0;
				soundKill(sound->channelId);
				sound->channelId = -1;
				sound->timer = 0;
			}
		}
	}
}

//Sound buffer code
SOUNDBUFFER::SOUNDBUFFER(size_t bufSize)
{
	//Set parameters
	size = bufSize;
	
	playing = false;
	looping = false;
	looped = false;

	timer = 0;
	
	frequency = 22050;
	volume = 127;
	pan = 63;
	samplePosition = 0;
	channelId = -1;
	
	//Create waveform buffer
	data = new s8[bufSize];
	memset(data, 0x80, bufSize);
	
	//Add to buffer list
	this->next = soundBuffers;
	soundBuffers = this;
}

SOUNDBUFFER::~SOUNDBUFFER()
{
	//Free buffer
	if (data)
		delete[] data;
	
	//Remove from buffer list
	for (SOUNDBUFFER **soundBuffer = &soundBuffers; *soundBuffer != NULL; soundBuffer = &(*soundBuffer)->next)
	{
		if (*soundBuffer == this)
		{
			*soundBuffer = this->next;
			break;
		}
	}
}

void SOUNDBUFFER::Release()
{
	//TODO: find a better and more stable(?) way to handle this function
	channelStates[channelId] = 0;
	delete this;
}

void SOUNDBUFFER::Lock(s8 **outBuffer, size_t *outSize)
{
	if (outBuffer != NULL)
		*outBuffer = data;

	if (outSize != NULL)
		*outSize = size;
}

void SOUNDBUFFER::Unlock()
{
	//Nothing
}

void SOUNDBUFFER::SetCurrentPosition(uint32_t dwNewPosition)
{
	samplePosition = dwNewPosition;
}

void SOUNDBUFFER::SetFrequency(uint32_t dwFrequency)
{
	frequency = dwFrequency;
	//SCHANNEL_TIMER(channelId) = SOUND_FREQ(frequency);
	if (channelId == -1) return;
	soundSetFreq(channelId, (u16)frequency);
}

float MillibelToVolume(int32_t lVolume)
{
	//Volume is in hundredths of decibels, from 0 to -10000

	lVolume = clamp(lVolume, (int32_t)-10000, (int32_t)0);
	return (float)pow(10.0, lVolume / 2000.0);
}

void SOUNDBUFFER::SetVolume(int32_t lVolume)
{
	float vol = MillibelToVolume(lVolume);
	volume = (vol * 127);
	
	//SCHANNEL_CR(channelId) = SCHANNEL_ENABLE | SOUND_FORMAT_8BIT | SOUND_VOL(lVolume);
	if (channelId == -1) return;
	soundSetVolume(channelId, volume);
}

void SOUNDBUFFER::SetPan(int32_t lPan)
{
	pan = (int)((double)lPan / 512.0 * 127.0); // pan_tbl max to nds 127 pan max
	if (channelId == -1) return;
	soundSetPan(channelId, pan);
}

int played = false;

void SOUNDBUFFER::Play(bool bLooping)
{

	if (!data) return;
	playing = true;
	looping = bLooping;

	if (channelId != -1 && size < 257 && !looping) 
	{
		//org for some reason sends a play message without looping for stopping..
		//so it is better to just cut it off here rather than start a new sound
		playing = false;
		channelStates[channelId] = 0;
		soundKill(channelId);
		channelId = -1;
		timer = 0;
		return;
	}
	if (channelId == -1)
	{
		channelId = getFreeChannel();
	}

	if(channelId == -1) return;
	channelStates[channelId] = 1;

	//printf() pan

	soundPlaySampleC(data, SoundFormat_8Bit, (u32)size, (u16)frequency, (u8)volume, (u8)pan, looping, (u16)0, channelId);
	timer = 0;
}

void SOUNDBUFFER::Stop()
{
	playing = false;
	if(channelId != -1) soundKill(channelId);
	channelStates[channelId] = false;
	channelId = -1;
}








//DirectSound interface
BOOL InitDirectSound(void)
{
	soundEnable();

	//Clear secondary sound buffers
	for (int i = 0; i < SE_MAX; i++)
		lpSECONDARYBUFFER[i] = NULL;
	return TRUE;
}

void EndDirectSound()
{
	//Release secondary sound buffers
	for (int i = 0; i < 8; i++) //Should be SE_MAX
	{
		if (lpSECONDARYBUFFER[i] != NULL)
		{
			lpSECONDARYBUFFER[i]->Release();
			lpSECONDARYBUFFER[i] = NULL;
		}
	}

	//Release primary sound buffer
	if (lpPRIMARYBUFFER != NULL)
	{
		lpPRIMARYBUFFER->Release();
		lpPRIMARYBUFFER = NULL;
	}

}

//Sound object creation and release
void ReleaseSoundObject(int no)
{
	if (lpSECONDARYBUFFER[no] != NULL)
	{
		lpSECONDARYBUFFER[no]->Release();
		lpSECONDARYBUFFER[no] = NULL;
	}
}

BOOL InitSoundObject(const char* resname, int no)
{

    //Get file path
    char path[MAX_PATH];
    sprintf(path, "Wave/%s.raw", resname);
    
	
    //Open file
    FILE_e *fp = fopen_embed(path, "rb");
    if (fp == NULL)
        return FALSE;
	size_t size = fp->size;
    //Read file
    signed char *data = (signed char *)malloc(size);
    if (data == NULL)
    {
        fclose_embed(fp);
        return FALSE;
    }

    fread_embed(data, size, 1, fp);
    fclose_embed(fp);
    
    //Create buffer
    lpSECONDARYBUFFER[no] = new SOUNDBUFFER(size);
    if (lpSECONDARYBUFFER[no] == NULL)
        return FALSE;
    

    //Upload data to buffer
    s8 *buf;
    lpSECONDARYBUFFER[no]->Lock(&buf, NULL);
    memcpy(buf, data, size);
    lpSECONDARYBUFFER[no]->Unlock();
    lpSECONDARYBUFFER[no]->SetFrequency(22050);
	free(data);
    return TRUE;
}

void PlaySoundObject(int no, int mode)
{
	if (lpSECONDARYBUFFER[no] != NULL)
	{
		switch (mode)
		{
			case SOUND_MODE_STOP: //Stop
				lpSECONDARYBUFFER[no]->Stop();
				break;

			case SOUND_MODE_PLAY: //Play
				lpSECONDARYBUFFER[no]->Stop();
				lpSECONDARYBUFFER[no]->SetCurrentPosition(0);
				lpSECONDARYBUFFER[no]->Play(false);
				break;

			case SOUND_MODE_PLAY_LOOP: //Play looped
				lpSECONDARYBUFFER[no]->Play(true);
				break;
		}
	}
}

void ChangeSoundFrequency(int no, DWORD rate) //100 is MIN, 9999 is MAX, and 2195 is normal
{
	if (lpSECONDARYBUFFER[no] != NULL)
		lpSECONDARYBUFFER[no]->SetFrequency((rate * 10) + 100);
}

void ChangeSoundVolume(int no, long volume) //300 is MAX and 300 is normal
{
	if (lpSECONDARYBUFFER[no] != NULL)
		lpSECONDARYBUFFER[no]->SetVolume((volume - 300) * 8);
}

void ChangeSoundPan(int no, long pan) //512 is MAX and 256 is normal
{
	if (lpSECONDARYBUFFER[no] != NULL)
		lpSECONDARYBUFFER[no]->SetPan(pan);
}

//PiyoPiyo sound
int freq_tbl[12] = { 1551, 1652, 1747, 1848, 1955, 2074, 2205, 2324, 2461, 2616, 2770, 2938 };

BOOL MakePiyoPiyoSoundObject(CHAR *wave, BYTE *envelope, int octave, int data_size, int no)
{
	BOOL result;
	int i;

	//Construct sound buffers
	for (i = 0; i < 24; i++)
	{
		lpSECONDARYBUFFER[no + i] = new SOUNDBUFFER(data_size);
	}
	   //Precalculate envelope
    WORD *pre_env = (WORD*)malloc(data_size * sizeof(WORD));
    WORD *pre_env_p = pre_env;
    for (int j = 0; j < data_size; j++)
        *pre_env_p++ = ((WORD)envelope[(j << 6) / data_size]) << 1;
    
    //Write sound data
    WORD *wp = (WORD*)malloc(data_size * sizeof(WORD));
    WORD *wpp;
    
    for (i = 0; i < 24; i++)
    {
        //Get frequency
        int freq;
        if (i < 12)
            freq = octave * freq_tbl[i] / 16;
        else
            freq = octave * freq_tbl[i - 12] / 8;
        
        //Construct waveform
        union
        {
            WORD word;
            struct
            {
                BYTE lower;
                BYTE upper;
            } fixed;
        } wp_sub = { 0 };
        pre_env_p = pre_env;
        wpp = wp;
        
        for (int j = 0; j < data_size; j++)
        {
            //Set sample and increment sub-pos
            *wpp++ = (wave[wp_sub.fixed.upper]) * (*pre_env_p++);
            wp_sub.word += freq;
        }
        s8 *buf;
   		lpSECONDARYBUFFER[no + i]->Lock(&buf, NULL);

        //Copy waveform
        wpp = wp;
        for (int v = 0; v < data_size; v++)
            *buf++ = ((*wpp++ >> 8));
        
		lpSECONDARYBUFFER[no + i]->Unlock();
    	lpSECONDARYBUFFER[no + i]->SetFrequency(22050);
        
    }
    
    //Check if there was an error and free wave buffer
    if (i == 24)
        result = TRUE;
    free(wp);
    free(pre_env);
    return result;
}
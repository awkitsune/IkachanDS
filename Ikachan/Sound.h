#pragma once
//#include <windows.h>
#include "WindowsWrapper.h"
#include "nds/ndstypes.h"

class SOUNDBUFFER
{
	public:
		SOUNDBUFFER(size_t bufSize);
		~SOUNDBUFFER();
		
		void Release();
		
		void Lock(s8 **buffer, size_t *size);
		void Unlock();
		
		void SetCurrentPosition(uint32_t dwNewPosition);
		void SetFrequency(uint32_t dwFrequency);
		void SetVolume(int32_t lVolume);
		void SetPan(int32_t lPan);
		void Play(bool bLooping);
		void Stop();
		
		void Mix(long *stream, uint32_t samples);
		
		SOUNDBUFFER *next;
	
	public:
		s8 *data;
		size_t size;
		
		bool playing;
		bool looping;
		bool looped;
		
		int timer;

		int frequency;
		int volume;
		int pan;
		
		int samplePosition;

		signed char channelId;
};


enum SOUND_ID
{
	SOUND_ID_NODMG = 0,
	SOUND_ID_DASH = 1,
	SOUND_ID_OUCH = 2,
	SOUND_ID_ITEM = 3,
	SOUND_ID_HITHEAD = 4,
	SOUND_ID_CRASH = 5,
	SOUND_ID_READY = 6,
	SOUND_ID_GO = 7,
	SOUND_ID_MESSAGE = 8,
	SOUND_ID_DEAD = 9,
	SOUND_ID_WIN = 10,
	SOUND_ID_LEVELUP = 11,
	SOUND_ID_LIFEUP = 12,
	SOUND_ID_SAVE = 13,
	SOUND_ID_YESNO = 14,
	SOUND_ID_QUAKE = 15,
	SOUND_ID_BOSSOUCH = 20,
};

enum SOUND_MODE
{
	SOUND_MODE_PLAY_LOOP = -1,
	SOUND_MODE_STOP = 0,
	SOUND_MODE_PLAY = 1
};

BOOL InitDirectSound(void);
void EndDirectSound();
void ReleaseSoundObject(int no);
BOOL InitSoundObject(const char* resname, int no);
void PlaySoundObject(int no, int mode);
void ChangeSoundFrequency(int no, DWORD rate);
void ChangeSoundVolume(int no, long volume);
void ChangeSoundPan(int no, long pan);
BOOL MakePiyoPiyoSoundObject(CHAR *wave, BYTE *envelope, int octave, int data_size, int no);
void updateChannelStates(void);

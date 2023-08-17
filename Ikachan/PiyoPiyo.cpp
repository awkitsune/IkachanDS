#include "PiyoPiyo.h"
#include "Sound.h"
#include "System.h"
#include <stdio.h>
#include <assert.h>

#include <stdlib.h>

#include "fopen.h"

#define MAX_RECORD 1000

struct PIYOPIYO_TRACKHEADER
{
	//Track information
	BYTE octave; //x0
	BYTE icon; //x1
	//alignment x2 x3
	DWORD length; //x4
	DWORD volume; //x8
	DWORD unk1, unk2; //xC x10
	CHAR wave[0x100]; //x14
	BYTE envelope[0x40]; //x114
};

struct PIYOPIYO_HEADER
{
	//Header
	char magic[3]; //x0
	BOOLEAN writable; //x3
	DWORD p_track1; //x4
	DWORD wait; //x8
	int repeat_x; //xC
	int end_x; //x10
	int records; //x14
	
	//Track headers
	PIYOPIYO_TRACKHEADER track[3]; //x18 x16C x2C0
	DWORD percussion_volume; //x414
};

struct PIYOPIYO
{
	//Loaded header
	PIYOPIYO_HEADER header; //x0

	//Playback state
	BOOLEAN playing; //x418
	//alignment x419 x41A x41B
	int position; //x41C
	DWORD tick; //x420
	DWORD *record[4]; //x424
	BOOL init; //x428
};

PIYOPIYO gPiyoPiyo;

BOOL InitPiyoPiyo()
{
	//Load drums
	InitSoundObject("BASS1", 472);
	gPiyoPiyo.init = TRUE;
	InitSoundObject("BASS1", 473);
	InitSoundObject("BASS2", 474);
	InitSoundObject("BASS2", 475);
	InitSoundObject("SNARE1", 476);
	InitSoundObject("SNARE1", 477);
	InitSoundObject("SNARE1", 478);
	InitSoundObject("SNARE1", 479);
	InitSoundObject("HAT1", 480);
	InitSoundObject("HAT1", 481);
	InitSoundObject("HAT2", 482);
	InitSoundObject("HAT2", 483);
	InitSoundObject("SYMBAL1", 484);
	InitSoundObject("SYMBAL1", 485);
	InitSoundObject("SYMBAL1", 486);
	InitSoundObject("SYMBAL1", 487);
	InitSoundObject("SYMBAL1", 488);
	InitSoundObject("SYMBAL1", 489);
	InitSoundObject("SYMBAL1", 490);
	InitSoundObject("SYMBAL1", 491);
	InitSoundObject("SYMBAL1", 492);
	InitSoundObject("SYMBAL1", 493);
	InitSoundObject("SYMBAL1", 494);
	InitSoundObject("SYMBAL1", 495);
	
	//Allocate buffers
	gPiyoPiyo.record[0] = (DWORD*)malloc(MAX_RECORD * 4);
	gPiyoPiyo.record[1] = (DWORD*)malloc(MAX_RECORD * 4);
	gPiyoPiyo.record[2] = (DWORD*)malloc(MAX_RECORD * 4);
	gPiyoPiyo.record[3] = (DWORD*)malloc(MAX_RECORD * 4);
	
	//Make sure buffers successfully allocated
	if (gPiyoPiyo.record[0] == NULL || gPiyoPiyo.record[1] == NULL || gPiyoPiyo.record[2] == NULL || gPiyoPiyo.record[3] == NULL)
	{
		if (gPiyoPiyo.record[0] != NULL)
		{
			free(gPiyoPiyo.record[0]);
			gPiyoPiyo.record[0] = NULL;
		}
		if (gPiyoPiyo.record[1] != NULL)
		{
			free(gPiyoPiyo.record[1]);
			gPiyoPiyo.record[1] = NULL;
		}
		if (gPiyoPiyo.record[2] != NULL)
		{
			free(gPiyoPiyo.record[2]);
			gPiyoPiyo.record[2] = NULL;
		}
		if (gPiyoPiyo.record[3] != NULL)
		{
			free(gPiyoPiyo.record[3]);
			gPiyoPiyo.record[3] = NULL;
		}
	}
	return TRUE;
}

void EndPiyoPiyo()
{
	//Release buffers
	if (gPiyoPiyo.record[0] != NULL)
	{
		free(gPiyoPiyo.record[0]);
		gPiyoPiyo.record[0] = NULL;
	}
	if (gPiyoPiyo.record[1] != NULL)
	{
		free(gPiyoPiyo.record[1]);
		gPiyoPiyo.record[1] = NULL;
	}
	if (gPiyoPiyo.record[2] != NULL)
	{
		free(gPiyoPiyo.record[2]);
		gPiyoPiyo.record[2] = NULL;
	}
	if (gPiyoPiyo.record[3] != NULL)
	{
		free(gPiyoPiyo.record[3]);
		gPiyoPiyo.record[3] = NULL;
	}
}

BOOL ReadPiyoPiyo(const char* path)
{
	//Fail if PiyoPiyo hasn't been initialised
	if (gPiyoPiyo.init == FALSE)
		return FALSE;
	
	//Open file
	FILE_e *fp = fopen_embed(path, "rb");
	if (fp == NULL)
		return FALSE;
	
	//Read data
	fread_embed(&gPiyoPiyo.header, sizeof(PIYOPIYO_HEADER), 1, fp);
	fread_embed(gPiyoPiyo.record[0], 4, gPiyoPiyo.header.records, fp);
	fread_embed(gPiyoPiyo.record[1], 4, gPiyoPiyo.header.records, fp);
	fread_embed(gPiyoPiyo.record[2], 4, gPiyoPiyo.header.records, fp);
	fread_embed(gPiyoPiyo.record[3], 4, gPiyoPiyo.header.records, fp);
	fclose_embed(fp);
	gPiyoPiyo.position = -1;
	return TRUE;
}

int tick_count = 0;

void PiyoPiyoProc()
{

	const unsigned int frameDelays[3] = {17, 16, 17};
	static unsigned int frame;

	const unsigned int delay = frameDelays[frame % 3];
	++frame;
	
	int pan_tbl[8] = {
		0, 96, 180, 224, 256, 288, 332, 420
	};
	//Check if next step should be played
	tick_count += delay;
	if (gPiyoPiyo.init && gPiyoPiyo.playing && tick_count > (gPiyoPiyo.tick + gPiyoPiyo.header.wait))
	{
		//Check if position passes loop point
		if (++gPiyoPiyo.position > (gPiyoPiyo.header.end_x - 1) || gPiyoPiyo.position > (gPiyoPiyo.header.records - 1))
			gPiyoPiyo.position = gPiyoPiyo.header.repeat_x;
		
		//Step channels
		for (int i = 0; i < 4; i++)
		{
			//Get this record
			DWORD record = gPiyoPiyo.record[i][gPiyoPiyo.position];
			
			//Change pan
			if (record & 0xFF000000)
			{
				int pan = record >> 24;
				for (int j = 0; j < 24; j++)
					ChangeSoundPan(400 + (i * 24) + j, pan_tbl[pan]);
			}
			
			//Play notes
			for (int j = 0; j < 24; j++)
			{
				if (record & 1)
					PlaySoundObject(400 + (i * 24) + j, 1);
				record >>= 1;
			}
		}
		
		//Remember previous tick
		gPiyoPiyo.tick = tick_count;
	}
	updateChannelStates();	
}

void MakePiyoPiyoSoundObjects()
{
	//Make sure PiyoPiyo has been initialised
	if (gPiyoPiyo.init)
	{
		//Setup each melody track
		for (int i = 0; i < 3; i++)
		{
			//Get octave
			int octave = 1 << gPiyoPiyo.header.track[i].octave;
			
			//Release previous objects
			for (int j = 0; j < 24; j++)
				ReleaseSoundObject(400 + (i * 24) + j);
			
			//Make new objects
			MakePiyoPiyoSoundObject(
				gPiyoPiyo.header.track[i].wave,
				gPiyoPiyo.header.track[i].envelope,
				octave, 
				gPiyoPiyo.header.track[i].length,
				400 + (24 * i));
			
			//Set track volume
			for (int j = 0; j < 24; j++)
				ChangeSoundVolume(400 + (i * 24) + j, gPiyoPiyo.header.track[i].volume);
		}
		
		//Set drum volume
		for (int i = 0; i < 24; i += 2)
		{
			ChangeSoundVolume(472 + i, gPiyoPiyo.header.percussion_volume);
			ChangeSoundVolume(473 + i, 70 * gPiyoPiyo.header.percussion_volume / 100);
		}
	}
}

void ChangePiyoPiyoVolume(PIYOPIYO_CONTROL *piyocont)
{
	if (gPiyoPiyo.init)
	{
		//Set melody volume
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 24; j++)
				ChangeSoundVolume(400 + (i * 24) + j, gPiyoPiyo.header.track[i].volume - piyocont->volume);
		}
		
		//Set drum volume
		for (int i = 0; i < 24; i += 2)
		{
			ChangeSoundVolume(472 + i, gPiyoPiyo.header.percussion_volume - piyocont->volume);
			ChangeSoundVolume(473 + i, 70 * gPiyoPiyo.header.percussion_volume / 100 - piyocont->volume);
		}
	}
}

//PiyoPiyo control
const char* gMusicList[6] =
{
	"Pmd/Ikachan.pmd",
	"Pmd/Magirete.pmd",
	"Pmd/Buriki.pmd",
	"Pmd/Mizuno.pmd",
	"Pmd/Quake.pmd",
	"Pmd/Tidepool.pmd",
};

void PiyoPiyoControl(PIYOPIYO_CONTROL *piyocont)
{
	//Check if PiyoPiyo's been initialised
	if (gPiyoPiyo.init)
	{
		switch (piyocont->mode)
		{
			case 1:
				if (gPiyoPiyo.playing && piyocont->track == piyocont->prev_track)
				{
					//Track hasn't changed, do nothing
					piyocont->mode = 0;
				}
				else
				{
					//Stop playing previous song
					gPiyoPiyo.playing = FALSE;
					
					//Read given track
					char path[MAX_PATH];
					sprintf(path, "%s", gMusicList[piyocont->track]);
					ReadPiyoPiyo(path);
					MakePiyoPiyoSoundObjects();
					piyocont->prev_track = piyocont->track;
					piyocont->mode = 2;
				}
				break;
			case 2:
				//Play loaded track
				gPiyoPiyo.position = -1;
				gPiyoPiyo.playing = TRUE;
				piyocont->volume = 0;
				ChangePiyoPiyoVolume(piyocont);
				piyocont->mode = 0;
				break;
			case 3:
				//Stop loaded track
				gPiyoPiyo.playing = FALSE;
				piyocont->mode = 0;
				break;
			case 4:
				//Fade loaded track
				piyocont->volume++;
				if(piyocont->volume % 8 == 0) // avoid lagging the heck out of yes
					ChangePiyoPiyoVolume(piyocont);
				
				//Check if song should stop
				if (piyocont->volume > 250)
				{
					piyocont->mode = 0;
					gPiyoPiyo.playing = FALSE;
				}
				break;
			case 5:
				//Play loaded track at low volume
				piyocont->volume = 100;
				ChangePiyoPiyoVolume(piyocont);
				piyocont->mode = 0;
				break;
			case 6:
				//Play loaded track at full volume
				piyocont->volume = 0;
				ChangePiyoPiyoVolume(piyocont);
				piyocont->mode = 0;
				break;
			default:
				return;
		}
	}
}

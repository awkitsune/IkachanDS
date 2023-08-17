#include "System.h"
#include "Draw.h"
#include "Sound.h"
#include "Generic.h"
#include "PiyoPiyo.h"
#include "Dialog.h"
#include "Game.h"
#include <stdio.h>

#include <cstring>

#include "nds.h"
#include <filesystem.h>
#include "nds/fifocommon.h"

#include "fat.h"

//Keys
DWORD gKey;
DWORD gMouse;

//Window name
//LPCTSTR lpCaption = "Ikachan";

//Windows objects
//HWND ghWnd;
//HACCEL hAccel;

//Window size
//WND_SIZE gWndSize;
int gWndWidth, gWndHeight;

//Filepath
char gModulePath[MAX_PATH];

//LRESULT CALLBACK WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

int Random(int min, int max)
{
	const int range = max - min + 1;
	return (rand() % range) + min;
}

int main(int argc, char *argv[])
{
	fatInitDefault();

	//Get module path
	strcpy(gModulePath, "/");
	

	StartDirectDraw();
	//consoleDemoInit();

	RECT rcLoading = { 0, 0, 64, 8 };
	RECT rcFull = { 0, 0, 0, 0 };
	rcFull.right = SURFACE_WIDTH;
	rcFull.bottom = SURFACE_HEIGHT;

	//Load the "LOADING" text
	BOOL b = MakeSurface_File("Pbm/Loading2.png", SURFACE_ID_LOADING2);

	//Draw loading screen
	CortBox(&rcFull, 0x000000);
	PutBitmap3(&rcFull, (SURFACE_WIDTH / 2) - 32, (SURFACE_HEIGHT / 2) - 4, &rcLoading, SURFACE_ID_LOADING2);
	if (!Flip_SystemTask())
	{
		//Release Ikachan mutex
		return 1;
	}
	
	//Initialize DirectSound
	if (InitDirectSound())
	{
		//Initialize game
		InitTextObject();
		InitPiyoPiyo();

		//Run game loop
		Game();
		
		//End game
		EndPiyoPiyo();
		EndTextObject();

		//End DirectDraw and DirectSound
		EndDirectSound();
		EndDirectDraw();
	}

	return 1;
}

//Window process
BOOL bActive;

void InactiveWindow()
{
	bActive = FALSE;
}

//System task
BOOL SystemTask()
{

	return TRUE;
}

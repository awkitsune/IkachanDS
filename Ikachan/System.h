#pragma once
//#include <windows.h>
#include "WindowsWrapper.h"
//Keys
#define MOUSE_RIGHT (0x00000001)
#define MOUSE_LEFT  (0x00000002)

#define CEY_LEFT  (0x00000001)
#define CEY_RIGHT (0x00000002)
#define CEY_UP    (0x00000004)
#define CEY_DOWN  (0x00000008)
#define CEY_SPACE (0x00000010)
#define CEY_X     (0x00000020)
#define CEY_Z     (0x00000040)
#define CEY_S     (0x00000080)

extern DWORD gKey, gKeyTrg;
extern DWORD gMouse, gMouseTrg, gMouseTrg2;

//Window size
enum WND_SIZE
{
	WS_FULLSCREEN,
	WS_320x240,
	WS_640x480,
};
extern WND_SIZE gWndSize;

//Windows objects

//Filepath
extern char gModulePath[MAX_PATH];

int Random(int min, int max);
BOOL SystemTask();

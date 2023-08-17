#pragma once
//#include <windows.h>
#include "System.h"
#include "WindowsWrapper.h"
#include "nds.h"

#ifdef TWO_SCREENS
#define SURFACE_WIDTH 384
#define SURFACE_HEIGHT 256
#else
#define SURFACE_WIDTH 256
#define SURFACE_HEIGHT 192
#endif

static const u8 font_space[32*3] = {
    2,2,4,8,6,8,7,2,4,4,8,6,3,6,2,4,6,3,6,6,7,6,6,6,6,6,2,3,4,6,4,5,
    8,6,6,6,6,5,5,6,6,2,5,6,5,6,6,6,6,6,6,5,6,6,6,6,6,6,5,4,4,4,4,6,
    3,6,6,6,6,6,5,6,6,2,4,5,3,8,6,6,6,6,5,5,5,6,6,6,6,6,6,5,2,5,6,4,
};

struct BUFFER_PIXEL
{
	char color;
};

struct SURFACE
{
	int w;
	int h;
	int textureid;
	int xoffset;
	int yoffset;
	int paletteOffset; //offset from palette vram banks
	int paletteAddress; //real address of palette in memory
	GL_TEXTURE_TYPE_ENUM paletteType;
	int palettesize;
	BUFFER_PIXEL *data;
	u16* palette;
	char name[16];
};


#define MAX_SURFACE 512
extern SURFACE surf[MAX_SURFACE];



enum SurfaceID
{
	SURFACE_ID_STATUS = 0,
	SURFACE_ID_MYCHAR = 2,
	SURFACE_ID_FIGURE = 4,
	SURFACE_ID_TEXT0 = 6,
	SURFACE_ID_TEXT1 = 7,
	SURFACE_ID_MSGBOX = 8,
	SURFACE_ID_ITEMBOX = 9,
	SURFACE_ID_ITEM = 10,
	SURFACE_ID_BACK = 11,
	SURFACE_ID_LOADING = 12,
	SURFACE_ID_NPCTYPE = 13,
	SURFACE_ID_CURSOR = 14,
	SURFACE_ID_EDITOR = 15,
	SURFACE_ID_YESNO = 16,
	SURFACE_ID_OPENING = 17,
	SURFACE_ID_FADE = 18,
	SURFACE_ID_BACKUP = 19,
	SURFACE_ID_MARUAME = 20,
	SURFACE_ID_MYCHAR3 = 21,
	SURFACE_ID_MYCHAR2 = 22,
	SURFACE_ID_END = 23,
	SURFACE_ID_STAFF = 24,
	SURFACE_ID_LOADING2 = 25,
	SURFACE_ID_WORDS0 = 40,
	SURFACE_ID_WORDS1 = 41,
	SURFACE_ID_WORDS2 = 42,
	SURFACE_ID_WORDS3 = 43,
	SURFACE_ID_WORDS4 = 44,
	SURFACE_ID_WORDS5 = 45,
	SURFACE_ID_WORDS6 = 46,
	SURFACE_ID_WORDS7 = 47,
	SURFACE_ID_WORDS8 = 48,
	SURFACE_ID_WORDS9 = 49,
	SURFACE_ID_WORDS10 = 50,
	SURFACE_ID_STAR = 60,
	SURFACE_ID_BUBBLE = 61,
	SURFACE_ID_DAMAGE = 62,
	SURFACE_ID_LEVELUP = 63,
	SURFACE_ID_PRTBACK = 70,
	SURFACE_ID_PRTFILT = 71,
	SURFACE_ID_PRTITEM = 72,
	SURFACE_ID_PRTDIR = 73,
	SURFACE_ID_PRTBLOCK = 74,
	SURFACE_ID_PRTDMG = 75,
	SURFACE_ID_PRTSNACK = 77,
	SURFACE_ID_HARI = 80,
	SURFACE_ID_ISOGIN = 81,
	SURFACE_ID_KANI = 82,
	SURFACE_ID_SLEEP = 83,
	SURFACE_ID_CHIBI = 84,
	SURFACE_ID_HOSHI = 85,
	SURFACE_ID_DUM = 86,
	SURFACE_ID_CARRY = 87,
	SURFACE_ID_JUEL = 88,
	SURFACE_ID_UFO = 89,
	SURFACE_ID_IRONHEAD = 100,
	SURFACE_ID_FONT = 101,
};

extern RECT grcFull;

BOOL Flip_SystemTask(void);
BOOL StartDirectDraw();
void EndDirectDraw(void);
void ReleaseSurface(SurfaceID s);
BOOL MakeSurface_Resource(const char *name, int surf_no);
BOOL MakeSurface_File(const char *name, int surf_no);
BOOL ReloadBitmap_Resource(const char *name, int surf_no);
BOOL ReloadBitmap_File(const char *name, int surf_no);
BOOL MakeSurface_Generic(int bxsize, int bysize, int surf_no);
void BackupSurface(SurfaceID surf_no, RECT *rect);
void CopyFaceTexture(int face);
void PutBitmap3(RECT *rcView, int x, int y, RECT *rect, int surf_no);
void PutBitmap4(RECT *rcView, int x, int y, RECT *rect, int surf_no);
void Surface2Surface(int x, int y, RECT *rect, int to, int from);
void Surface2Texture(int x, int y, RECT *rect, int to, int from);
unsigned long GetCortBoxColor(unsigned long col);
void CortBox(RECT *rect, unsigned long col);
void CortBox2(RECT *rect, unsigned long col, int surf_no);
int RestoreSurfaces(void);
void InitTextObject();
int GetTextSpacing(const char *text);
void PutText(RECT* rcView, int x, int y, const char *text, unsigned long color);
void PutText2(int x, int y, const char *text, unsigned long color, int surf_no);
void EndTextObject(void);
BOOL CopyDataToTexture(int paletteType, int textureid, int surf_no,  int xoffset, int yoffset, RECT* rect);

void glBegin2D( void );
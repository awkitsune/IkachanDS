#pragma once

#include <stdio.h>

#define RGB(r,g,b) ((r) | ((g) << 8) | ((b) << 16))

typedef bool BOOL;
typedef bool BOOLEAN;
typedef short WORD;
typedef int DWORD;
typedef unsigned char BYTE;
typedef signed char CHAR;
typedef long LONG;

#define FALSE false
#define TRUE true

struct RECT
{
	long left;
	long top;
	long right;
	long bottom;
};

#define MAX_PATH FILENAME_MAX

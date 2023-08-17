#include "PixelScript.h"
#include "EventScript.h"
#include <stdio.h>
#include <stdlib.h>
#include "Generic.h"

#include "fopen.h"

#define IS_COMMAND1(c1) (ptx->data[ptx->p_read] == '<' && ptx->data[ptx->p_read + 1] == (c1))
#define IS_COMMAND2(c1, c2) (ptx->data[ptx->p_read] == '<' && ptx->data[ptx->p_read + 1] == (c1) && ptx->data[ptx->p_read + 2] == (c2))

RECT rcPsIllust = { 0, 0, 320, 240 };
RECT rcPsEnd = { 0, 0, 48, 24 };
RECT rcPsLine = { 0, 0, SURFACE_WIDTH, 16 };


BOOL ReadPixelScript(PIX_SCR *ptx, const char* path)
{


	//Open file
	FILE_e *fp = fopen_embed(path, "rt");
	if (fp == NULL)
		return FALSE;
	//Allocate data
	ptx->size = fp->size;
	ptx->data = (char*)malloc(ptx->size + 1);
	
	//Read file
	fread_embed(ptx->data, ptx->size, 1, fp);
	fclose_embed(fp);
	return TRUE;
}

void LoadPixelScript(PIX_SCR *ptx, const char* path, char scale)
{
	//Initialize Pixel Script
	ptx->end = FALSE;
	ptx->p_read = 0;
	ptx->scale = scale;
	ptx->line = 0;
	for (int i = 0; i < MAX_PSLINES; i++)
	{
		ptx->ypos_line[i] = i * 24 * ptx->scale;
		CortBox2(&rcPsLine, 0x000000, SURFACE_ID_WORDS0 + i);
	}

	//Read script
	ReadPixelScript(ptx, path);
	//DebugPutText(ptx->data);
}

char c[10][44];

int PixelScriptProc(PIX_SCR *ptx, PIYOPIYO_CONTROL *piyocont, BOOL ending)
{

	
	//Draw illustration
	if (ending)
		PutBitmap3(&grcFull, (SURFACE_WIDTH - 320) / 2, (SURFACE_HEIGHT - 240) / 2, &rcPsIllust, SURFACE_ID_STAFF);
	else
		PutBitmap3(&grcFull, (SURFACE_WIDTH - 320) / 2, (SURFACE_HEIGHT - 240) / 2, &rcPsIllust, SURFACE_ID_MARUAME);
	
	if (ptx->end)
	{
		//If the game's ended, draw "END" text
		PutBitmap3(&grcFull, (SURFACE_WIDTH / 2) - 24, (SURFACE_HEIGHT / 2) - 14, &rcPsEnd, SURFACE_ID_END);
		return 1;
	}
	else
	{
		//Process script and lines
		for (int i = 0; i < MAX_PSLINES; i++)
		{
			//Draw line
			PutText(&grcFull, 0, ptx->ypos_line[i] / ptx->scale + 1, c[i], RGB(0x00, 0x00, 0xFF));
			PutText(&grcFull, 0, ptx->ypos_line[i] / ptx->scale + 0, c[i], RGB(0x00, 0x88, 0xFF));

			//Scroll line
			ptx->ypos_line[i] -= 2;
			if ((gKey & CEY_SPACE) || (gKey & CEY_Z))
				ptx->ypos_line[i] -= 6;

			//Check if line's scrolled over the top of the screen
			if (ptx->ypos_line[i] / ptx->scale < -24)
			{
				//Clear line and move to bottom of screen
				ptx->ypos_line[i] = SURFACE_HEIGHT * ptx->scale;
				c[i][0] = 0;
				//CortBox2(&rcPsLine, 0x000000, SURFACE_ID_WORDS0 + i);

				//Read new line
				for (int j = 0; j < 40; j++)
				{
					if (ptx->data[ptx->p_read] == ' ')
					{
						//Type space
						c[ptx->line][j] = ' ';
						ptx->p_read++;
					}
					else if (ptx->data[ptx->p_read] & 0x80)
					{
						//Type Shift-JIS
						c[ptx->line][j] = ptx->data[ptx->p_read];
						c[ptx->line][++j] = ptx->data[ptx->p_read + 1];
						ptx->p_read += 2;
					}
					else if (IS_COMMAND2('p','f'))
					{
						//Fade PiyoPiyo
						ptx->p_read += 4;
						piyocont->mode = 4;
						j = 999;
					}
					else if (IS_COMMAND2('e', 'n'))
					{
						//Bring up "END" text
						ptx->end = TRUE;
					}
					else if (ptx->data[ptx->p_read] >= 'A' && ptx->data[ptx->p_read] <= 'z')
					{
						//English alphabet
						c[ptx->line][j] = ptx->data[ptx->p_read++];
					}
					else if (ptx->data[ptx->p_read] >= '0' && ptx->data[ptx->p_read] <= '9')
					{
						//English numerals
						c[ptx->line][j] = ptx->data[ptx->p_read++];
					}
					else if (ptx->data[ptx->p_read] == '.' || ptx->data[ptx->p_read] == '/' || ptx->data[ptx->p_read] == ',')
					{
						//Other specific characters
						c[ptx->line][j] = ptx->data[ptx->p_read++];
					}
					else if (IS_COMMAND1('e'))
					{
						//Start gameplay
						return 1;
					}
					else if (ptx->data[ptx->p_read] == '+')
					{
						//Print text onto line
						c[ptx->line][j] = 0;
						if (++ptx->line >= MAX_PSLINES)
							ptx->line = 0;
						ptx->p_read += 1;
						j = 999;
					}
					else
					{
						c[ptx->line][j] = 0;
						if (++ptx->line >= MAX_PSLINES)
							ptx->line = 0;
						ptx->p_read += 1;
						j = 999;
					}
				}
			}
		}

		//If the game's ended, draw "END" text
		if (ptx->end)
			PutBitmap3(&grcFull, (SURFACE_WIDTH / 2) - 24, (SURFACE_HEIGHT / 2) - 14, &rcPsEnd, SURFACE_ID_END);
		return 0;
	}
}

void EndPixelScript(PIX_SCR *ptx)
{
	//Release data
	free(ptx->data);
}
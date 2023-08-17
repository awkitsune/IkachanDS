#include <cstring>
#include <stdlib.h>

//File references
#include "../incbin.h"
#define INCBIN_PREFIX

// we are in the "build" folder

INCBIN(Eventptx, "../game_english/Event.ptx");
INCBIN(NPChardat, "../game_english/NPChar.dat");
INCBIN(Staffptx, "../game_english/Staff.ptx");
INCBIN(Wordsptx, "../game_english/Words.ptx");

INCBIN(BASS1raw, "../game_english/Wave/BASS1.raw");
INCBIN(BASS2raw, "../game_english/Wave/BASS2.raw");
INCBIN(BOSSOUCHraw, "../game_english/Wave/BOSSOUCH.raw");
INCBIN(CRASHraw, "../game_english/Wave/CRASH.raw");
INCBIN(DASHraw, "../game_english/Wave/DASH.raw");
INCBIN(DEADraw, "../game_english/Wave/DEAD.raw");
INCBIN(GOraw, "../game_english/Wave/GO.raw");
INCBIN(HAT1raw, "../game_english/Wave/HAT1.raw");
INCBIN(HAT2raw, "../game_english/Wave/HAT2.raw");
INCBIN(HITHEADraw, "../game_english/Wave/HITHEAD.raw");
INCBIN(ITEMraw, "../game_english/Wave/ITEM.raw");
INCBIN(LEVELUPraw, "../game_english/Wave/LEVELUP.raw");
INCBIN(LIFEUPraw, "../game_english/Wave/LIFEUP.raw");
INCBIN(MESSAGEraw, "../game_english/Wave/MESSAGE.raw");
INCBIN(NODMGraw, "../game_english/Wave/NODMG.raw");
INCBIN(OUCHraw, "../game_english/Wave/OUCH.raw");
INCBIN(QUAKEraw, "../game_english/Wave/QUAKE.raw");
INCBIN(READYraw, "../game_english/Wave/READY.raw");
INCBIN(SAVEraw, "../game_english/Wave/SAVE.raw");
INCBIN(SNARE1raw, "../game_english/Wave/SNARE1.raw");
INCBIN(SYMBAL1raw, "../game_english/Wave/SYMBAL1.raw");
INCBIN(WINraw, "../game_english/Wave/WIN.raw");
INCBIN(YESNOraw, "../game_english/Wave/YESNO.raw");

INCBIN(Burikipmd, "../game_english/Pmd/Buriki.pmd");
INCBIN(Ikachanpmd, "../game_english/Pmd/Ikachan.pmd");
INCBIN(Magiretepmd, "../game_english/Pmd/Magirete.pmd");
INCBIN(Mizunopmd, "../game_english/Pmd/Mizuno.pmd");
INCBIN(Quakepmd, "../game_english/Pmd/Quake.pmd");
INCBIN(Tidepoolpmd, "../game_english/Pmd/Tidepool.pmd");


INCBIN(Backpng, "../game_english/Pbm/Back.png");
INCBIN(Bubblepng, "../game_english/Pbm/Bubble.png");
INCBIN(Carrypng, "../game_english/Pbm/Carry.png");
INCBIN(Chibipng, "../game_english/Pbm/Chibi.png");
INCBIN(Cursorpng, "../game_english/Pbm/Cursor.png");
INCBIN(Damagepng, "../game_english/Pbm/Damage.png");
INCBIN(Dumpng, "../game_english/Pbm/Dum.png");
INCBIN(Editorpng, "../game_english/Pbm/Editor.png");
INCBIN(Endpng, "../game_english/Pbm/End.png");
INCBIN(Fadepng, "../game_english/Pbm/Fade.png");
INCBIN(Figurepng, "../game_english/Pbm/Figure.png");
INCBIN(Haripng, "../game_english/Pbm/Hari.png");
INCBIN(Hoshipng, "../game_english/Pbm/Hoshi.png");
INCBIN(Ironheadpng, "../game_english/Pbm/Ironhead.png");
INCBIN(Isoginpng, "../game_english/Pbm/Isogin.png");
INCBIN(ItemBoxpng, "../game_english/Pbm/ItemBox.png");
INCBIN(Itempng, "../game_english/Pbm/Item.png");
INCBIN(Juelpng, "../game_english/Pbm/Juel.png");
INCBIN(Kanipng, "../game_english/Pbm/Kani.png");
INCBIN(LevelUppng, "../game_english/Pbm/LevelUp.png");
INCBIN(Loading2png, "../game_english/Pbm/Loading2.png");
INCBIN(Loadingpng, "../game_english/Pbm/Loading.png");
INCBIN(Map1pbm, "../game_english/Pbm/Map1.pbm");
INCBIN(MaruAmepng, "../game_english/Pbm/MaruAme.png");
INCBIN(Msgboxpng, "../game_english/Pbm/Msgbox.png");
INCBIN(MyChar2png, "../game_english/Pbm/MyChar2.png");
INCBIN(MyChar3png, "../game_english/Pbm/MyChar3.png");
INCBIN(MyCharpng, "../game_english/Pbm/MyChar.png");
INCBIN(NpcTypepng, "../game_english/Pbm/NpcType.png");
INCBIN(Openingpng, "../game_english/Pbm/Opening.png");
INCBIN(PrtBlockpng, "../game_english/Pbm/PrtBlock.png");
INCBIN(PrtDirpng, "../game_english/Pbm/PrtDir.png");
INCBIN(PrtDmgpng, "../game_english/Pbm/PrtDmg.png");
INCBIN(Prtfiltpng, "../game_english/Pbm/Prtfilt.png");
INCBIN(PrtItempng, "../game_english/Pbm/PrtItem.png");
INCBIN(PrtSnackpng, "../game_english/Pbm/PrtSnack.png");
INCBIN(Sleeppng, "../game_english/Pbm/Sleep.png");
INCBIN(smalfontpng, "../game_english/Pbm/smalfont.png");
INCBIN(Staffpng, "../game_english/Pbm/Staff.png");
INCBIN(Starpng, "../game_english/Pbm/Star.png");
INCBIN(Statuspng, "../game_english/Pbm/Status.png");
INCBIN(Ufopng, "../game_english/Pbm/Ufo.png");
INCBIN(YesNopng, "../game_english/Pbm/YesNo.png");

typedef struct {
	const unsigned char *data;
	unsigned int size;
	const char *path;
} FILEREF;

const FILEREF files[] = {
	{EventptxData, EventptxSize, "Event.ptx"},
	{NPChardatData, NPChardatSize, "NPChar.dat"},
	{StaffptxData, StaffptxSize, "Staff.ptx"},
	{WordsptxData, WordsptxSize, "Words.ptx"},
	{BASS1rawData, BASS1rawSize, "Wave/BASS1.raw"},
	{BASS2rawData, BASS2rawSize, "Wave/BASS2.raw"},
	{BOSSOUCHrawData, BOSSOUCHrawSize, "Wave/BOSSOUCH.raw"},
	{CRASHrawData, CRASHrawSize, "Wave/CRASH.raw"},
	{DASHrawData, DASHrawSize, "Wave/DASH.raw"},
	{DEADrawData, DEADrawSize, "Wave/DEAD.raw"},
	{GOrawData, GOrawSize, "Wave/GO.raw"},
	{HAT1rawData, HAT1rawSize, "Wave/HAT1.raw"},
	{HAT2rawData, HAT2rawSize, "Wave/HAT2.raw"},
	{HITHEADrawData, HITHEADrawSize, "Wave/HITHEAD.raw"},
	{ITEMrawData, ITEMrawSize, "Wave/ITEM.raw"},
	{LEVELUPrawData, LEVELUPrawSize, "Wave/LEVELUP.raw"},
	{LIFEUPrawData, LIFEUPrawSize, "Wave/LIFEUP.raw"},
	{MESSAGErawData, MESSAGErawSize, "Wave/MESSAGE.raw"},
	{NODMGrawData, NODMGrawSize, "Wave/NODMG.raw"},
	{OUCHrawData, OUCHrawSize, "Wave/OUCH.raw"},
	{QUAKErawData, QUAKErawSize, "Wave/QUAKE.raw"},
	{READYrawData, READYrawSize, "Wave/READY.raw"},
	{SAVErawData, SAVErawSize, "Wave/SAVE.raw"},
	{SNARE1rawData, SNARE1rawSize, "Wave/SNARE1.raw"},
	{SYMBAL1rawData, SYMBAL1rawSize, "Wave/SYMBAL1.raw"},
	{WINrawData, WINrawSize, "Wave/WIN.raw"},
	{YESNOrawData, YESNOrawSize, "Wave/YESNO.raw"},
	{BurikipmdData, BurikipmdSize, "Pmd/Buriki.pmd"},
	{IkachanpmdData, IkachanpmdSize, "Pmd/Ikachan.pmd"},
	{MagiretepmdData, MagiretepmdSize, "Pmd/Magirete.pmd"},
	{MizunopmdData, MizunopmdSize, "Pmd/Mizuno.pmd"},
	{QuakepmdData, QuakepmdSize, "Pmd/Quake.pmd"},
	{TidepoolpmdData, TidepoolpmdSize, "Pmd/Tidepool.pmd"},
	{BackpngData, BackpngSize, "Pbm/Back.png"},
	{BubblepngData, BubblepngSize, "Pbm/Bubble.png"},
	{CarrypngData, CarrypngSize, "Pbm/Carry.png"},
	{ChibipngData, ChibipngSize, "Pbm/Chibi.png"},
	{CursorpngData, CursorpngSize, "Pbm/Cursor.png"},
	{DamagepngData, DamagepngSize, "Pbm/Damage.png"},
	{DumpngData, DumpngSize, "Pbm/Dum.png"},
	{EditorpngData, EditorpngSize, "Pbm/Editor.png"},
	{EndpngData, EndpngSize, "Pbm/End.png"},
	{FadepngData, FadepngSize, "Pbm/Fade.png"},
	{FigurepngData, FigurepngSize, "Pbm/Figure.png"},
	{HaripngData, HaripngSize, "Pbm/Hari.png"},
	{HoshipngData, HoshipngSize, "Pbm/Hoshi.png"},
	{IronheadpngData, IronheadpngSize, "Pbm/Ironhead.png"},
	{IsoginpngData, IsoginpngSize, "Pbm/Isogin.png"},
	{ItemBoxpngData, ItemBoxpngSize, "Pbm/ItemBox.png"},
	{ItempngData, ItempngSize, "Pbm/Item.png"},
	{JuelpngData, JuelpngSize, "Pbm/Juel.png"},
	{KanipngData, KanipngSize, "Pbm/Kani.png"},
	{LevelUppngData, LevelUppngSize, "Pbm/LevelUp.png"},
	{Loading2pngData, Loading2pngSize, "Pbm/Loading2.png"},
	{LoadingpngData, LoadingpngSize, "Pbm/Loading.png"},
	{Map1pbmData, Map1pbmSize, "Pbm/Map1.pbm"},
	{MaruAmepngData, MaruAmepngSize, "Pbm/MaruAme.png"},
	{MsgboxpngData, MsgboxpngSize, "Pbm/Msgbox.png"},
	{MyChar2pngData, MyChar2pngSize, "Pbm/MyChar2.png"},
	{MyChar3pngData, MyChar3pngSize, "Pbm/MyChar3.png"},
	{MyCharpngData, MyCharpngSize, "Pbm/MyChar.png"},
	{NpcTypepngData, NpcTypepngSize, "Pbm/NpcType.png"},
	{OpeningpngData, OpeningpngSize, "Pbm/Opening.png"},
	{PrtBlockpngData, PrtBlockpngSize, "Pbm/PrtBlock.png"},
	{PrtDirpngData, PrtDirpngSize, "Pbm/PrtDir.png"},
	{PrtDmgpngData, PrtDmgpngSize, "Pbm/PrtDmg.png"},
	{PrtfiltpngData, PrtfiltpngSize, "Pbm/PrtFilt.png"},
	{PrtItempngData, PrtItempngSize, "Pbm/PrtItem.png"},
	{PrtSnackpngData, PrtSnackpngSize, "Pbm/PrtSnack.png"},
	{SleeppngData, SleeppngSize, "Pbm/Sleep.png"},
	{smalfontpngData, smalfontpngSize, "Pbm/smalfont.png"},
	{StaffpngData, StaffpngSize, "Pbm/Staff.png"},
	{StarpngData, StarpngSize, "Pbm/Star.png"},
	{StatuspngData, StatuspngSize, "Pbm/Status.png"},
	{UfopngData, UfopngSize, "Pbm/Ufo.png"},
	{YesNopngData, YesNopngSize, "Pbm/YesNo.png"},
};

//File struct functions
#include "fopen.h"

FILE_e *fopen_embed(const char *file, const char *mode)
{
	//Get our referenced file
	const FILEREF *fileref = NULL;
	FILE_e *fp;
	int i;
	
	for (i = 0; i < sizeof(files) / sizeof(FILEREF); i++)
	{
		if (!strcmp(file, files[i].path))
		{
			fileref = &files[i];
			break;
		}
			
	}
	
	if (fileref == NULL)
		return NULL;
	
	//Allocate file struct and construct
	fp = (FILE_e*)malloc(sizeof(FILE_e));
	fp->file = fileref->data;
	fp->point = fp->file;
	fp->size = fileref->size;
	fp->position = 0;
	
	return fp;
}

void fclose_embed(FILE_e *fp)
{
	//Free file struct
	free(fp);
}

size_t fread_embed(void *ptr, size_t size, size_t nmemb, FILE_e *fp)
{
	//Lazy memcpy
	memcpy(ptr, fp->point + fp->position, size * nmemb);
	fp->position += size * nmemb;
	return nmemb;
}

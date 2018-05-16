#include <pspkernel.h>
#include "jmpfont.h"
#include "imports.h"

typedef struct sceFont_t_initRec {
	void *userData;
	unsigned long maxNumFonts;
	void *cache;
	void *(*allocFunc)(void *, unsigned long);
	void (*freeFunc)(void *, void *);
	void *(*openFunc)(void *, void *, signed long *);
	signed long (*closeFunc)(void *, void *);
	unsigned long (*readFunc)(void *, void *, void *, unsigned long, unsigned long, signed long *);
	signed long (*seekFunc)(void *, void *, unsigned long);
	signed long (*onErrorFunc)(void *, signed long);
	signed long (*whenDoneReadFunc)(void *, signed long);
} sceFont_t_initRec;

static void *my_open(void *pdata, char *filename, int *error)
{
	SceUID fd = sceIoOpen(filename, PSP_O_RDONLY, 0777);
	if(fd < 0) {*error = 0x80460005; return 0;}
	*error = 0; return (void *)fd;
}

static int my_close(void *pdata, void *fileid)
{
	return sceIoClose((SceUID)fileid) < 0 ? 0x80460006 : 0;
}

static int my_read(void *pdata, void *fileid, void *pbuf, int byte, int unit, int *error)
{
	int count = byte * unit;
	int retv = sceIoRead((SceUID)fileid, pbuf, count);
	if(retv < count) {*error = 0x80460007; return 0;}
	*error = 0; return unit;
}

static int my_seek(void *pdata, void *fileid, int offset)
{
	return sceIoLseek32((SceUID)fileid, offset, PSP_SEEK_SET) < 0 ? 0x80460008 : 0;
}

int jmpFontFlush(int fontHandle)
{
	return sceFontFlush(fontHandle);
}

int jmpFontFindOptimumFont(int fontLibHandle, int fontStylePtr, int errorCodePtr)
{
	return sceFontFindOptimumFont(fontLibHandle, fontStylePtr, errorCodePtr);
}

int jmpFontGetFontInfo(int fontHandle, int fontInfoPtr)
{
	return sceFontGetFontInfo(fontHandle, fontInfoPtr);
}

int jmpFontGetNumFontList(int fontLibHandle, int errorCodePtr)
{
	return sceFontGetNumFontList(fontLibHandle, errorCodePtr);
}

int jmpFontCalcMemorySize(int fontLibHandle, int fontStylePtr, int errorCodePtr)
{
	return sceFontCalcMemorySize(fontLibHandle, fontStylePtr, errorCodePtr);
}

int jmpFontClose(int fontHandle)
{
	return sceFontClose(fontHandle);
}

int jmpFontPointToPixelV(int fontLibHandle, int fontPointsV, int errorCodePtr)
{
	return sceFontPointToPixelV(fontLibHandle, fontPointsV, errorCodePtr);
}

int jmpFontPointToPixelH(int fontLibHandle, int fontPointsH, int errorCodePtr)
{
	return sceFontPointToPixelH(fontLibHandle, fontPointsH, errorCodePtr);
}

int jmpFontSetResolution(int fontLibHandle, int hRes, int vRes)
{
	return sceFontSetResolution(fontLibHandle, hRes, vRes);
}

int jmpFontGetShadowImageRect(int fontHandle, int charCode, int shadowRectPtr)
{
	return sceFontGetShadowImageRect(fontHandle, charCode, shadowRectPtr);
}

int jmpFontGetFontInfoByIndexNumber(int fontLibHandle, int fontInfoPtr, int fontIndex)
{
	return sceFontGetFontInfoByIndexNumber(fontLibHandle, fontInfoPtr, fontIndex);
}

int jmpFontGetShadowGlyphImage(int fontHandle, int charCode, int shadowGlyphImagePtr)
{
	return sceFontGetShadowGlyphImage(fontHandle, charCode, shadowGlyphImagePtr);
}

int jmpFontDoneLib(int fontLibHandle)
{
	return sceFontDoneLib(fontLibHandle);
}

int jmpFontOpenUserFile(int fontLibHandle, int fileNameAddr, int mode, int errorCodePtr)
{
	return sceFontOpenUserFile(fontLibHandle, fileNameAddr, mode, errorCodePtr);
}

int jmpFontGetCharImageRect(int fontHandle, int charCode, int charRectPtr)
{
	return sceFontGetCharImageRect(fontHandle, charCode, charRectPtr);
}

int jmpFontGetShadowGlyphImage_Clip(int fontHandle, int charCode, int shadowGlyphImagePtr, int clipXPos, int clipYPos, int clipWidth, int clipHeight)
{
	return sceFontGetShadowGlyphImage_Clip(fontHandle, charCode, shadowGlyphImagePtr, clipXPos, clipYPos, clipWidth, clipHeight);
}

int jmpFontNewLib(int paramsPtr, int errorCodePtr)
{
	sceFont_t_initRec *p = (sceFont_t_initRec *)paramsPtr;
	if(!p->openFunc) p->openFunc = (void *)my_open;
	if(!p->closeFunc) p->closeFunc = (void *)my_close;
	if(!p->readFunc) p->readFunc = (void *)my_read;
	if(!p->seekFunc) p->seekFunc = (void *)my_seek;
	return sceFontNewLib(paramsPtr, errorCodePtr);
}

int jmpFontFindFont(int fontLibHandle, int fontStylePtr, int errorCodePtr)
{
	return sceFontFindFont(fontLibHandle, fontStylePtr, errorCodePtr);
}

int jmpFontPixelToPointH(int fontLibHandle, int fontPixelsH, int errorCodePtr)
{
	return sceFontPixelToPointH(fontLibHandle, fontPixelsH, errorCodePtr);
}

int jmpFontGetCharGlyphImage(int fontHandle, int charCode, int glyphImagePtr)
{
	return sceFontGetCharGlyphImage(fontHandle, charCode, glyphImagePtr);
}

int jmpFontOpen(int fontLibHandle, int index, int mode, int errorCodePtr)
{
	return sceFontOpenUserFile(fontLibHandle, (int)"disc0:/PSP_GAME/USRDIR/MGP.PGF", mode, errorCodePtr);
}

int jmpFontGetShadowInfo(int fontHandle, int charCode, int shadowCharInfoPtr)
{
	return sceFontGetShadowInfo(fontHandle, charCode, shadowCharInfoPtr);
}

int jmpFontOpenUserMemory(int fontLibHandle, int memoryFontPtr, int memoryFontLength, int errorCodePtr)
{
	return sceFontOpenUserMemory(fontLibHandle, memoryFontPtr, memoryFontLength, errorCodePtr);
}

int jmpFontGetFontList(int fontLibHandle, int fontStylePtr, int numFonts)
{
	return sceFontGetFontList(fontLibHandle, fontStylePtr, numFonts);
}

int jmpFontGetCharGlyphImage_Clip(int fontHandle, int charCode, int glyphImagePtr, int clipXPos, int clipYPos, int clipWidth, int clipHeight)
{
	return sceFontGetCharGlyphImage_Clip(fontHandle, charCode, glyphImagePtr, clipXPos, clipYPos, clipWidth, clipHeight);
}

int jmpFontGetCharInfo(int fontHandle, int charCode, int charInfoPtr)
{
	return sceFontGetCharInfo(fontHandle, charCode, charInfoPtr);
}

int jmpFontSetAltCharacterCode(int fontLibHandle, int charCode)
{
	return sceFontSetAltCharacterCode(fontLibHandle, charCode);
}

int jmpFontPixelToPointV(int fontLibHandle, int fontPixelsV, int errorCodePtr)
{
	return sceFontPixelToPointV(fontLibHandle, fontPixelsV, errorCodePtr);
}


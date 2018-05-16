#ifndef JMPFONT_H_
#define JMPFONT_H_

int jmpFontFlush(int fontHandle);
int jmpFontFindOptimumFont(int fontLibHandle, int fontStylePtr, int errorCodePtr);
int jmpFontGetFontInfo(int fontHandle, int fontInfoPtr);
int jmpFontGetNumFontList(int fontLibHandle, int errorCodePtr);
int jmpFontCalcMemorySize(int fontLibHandle, int fontStylePtr, int errorCodePtr);
int jmpFontClose(int fontHandle);
int jmpFontPointToPixelV(int fontLibHandle, int fontPointsV, int errorCodePtr);
int jmpFontPointToPixelH(int fontLibHandle, int fontPointsH, int errorCodePtr);
int jmpFontSetResolution(int fontLibHandle, int hRes, int vRes);
int jmpFontGetShadowImageRect(int fontHandle, int charCode, int shadowRectPtr);
int jmpFontGetFontInfoByIndexNumber(int fontLibHandle, int fontInfoPtr, int fontIndex);
int jmpFontGetShadowGlyphImage(int fontHandle, int charCode, int shadowGlyphImagePtr);
int jmpFontDoneLib(int fontLibHandle);
int jmpFontOpenUserFile(int fontLibHandle, int fileNameAddr, int mode, int errorCodePtr);
int jmpFontGetCharImageRect(int fontHandle, int charCode, int charRectPtr);
int jmpFontGetShadowGlyphImage_Clip(int fontHandle, int charCode, int shadowGlyphImagePtr, int clipXPos, int clipYPos, int clipWidth, int clipHeight);
int jmpFontNewLib(int paramsPtr, int errorCodePtr);
int jmpFontFindFont(int fontLibHandle, int fontStylePtr, int errorCodePtr);
int jmpFontPixelToPointH(int fontLibHandle, int fontPixelsH, int errorCodePtr);
int jmpFontGetCharGlyphImage(int fontHandle, int charCode, int glyphImagePtr);
int jmpFontOpen(int fontLibHandle, int index, int mode, int errorCodePtr);
int jmpFontGetShadowInfo(int fontHandle, int charCode, int shadowCharInfoPtr);
int jmpFontOpenUserMemory(int fontLibHandle, int memoryFontPtr, int memoryFontLength, int errorCodePtr);
int jmpFontGetFontList(int fontLibHandle, int fontStylePtr, int numFonts);
int jmpFontGetCharGlyphImage_Clip(int fontHandle, int charCode, int glyphImagePtr, int clipXPos, int clipYPos, int clipWidth, int clipHeight);
int jmpFontGetCharInfo(int fontHandle, int charCode, int charInfoPtr);
int jmpFontSetAltCharacterCode(int fontLibHandle, int charCode);
int jmpFontPixelToPointV(int fontLibHandle, int fontPixelsV, int errorCodePtr);

#endif /* JMPFONT_H_ */


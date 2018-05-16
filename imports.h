#ifndef IMPORTS_H_
#define IMPORTS_H_

int sceFontFlush(int fontHandle);
int sceFontFindOptimumFont(int fontLibHandle, int fontStylePtr, int errorCodePtr);
int sceFontGetFontInfo(int fontHandle, int fontInfoPtr);
int sceFontGetNumFontList(int fontLibHandle, int errorCodePtr);
int sceFontCalcMemorySize(int fontLibHandle, int fontStylePtr, int errorCodePtr);
int sceFontClose(int fontHandle);
int sceFontPointToPixelV(int fontLibHandle, int fontPointsV, int errorCodePtr);
int sceFontPointToPixelH(int fontLibHandle, int fontPointsH, int errorCodePtr);
int sceFontSetResolution(int fontLibHandle, int hRes, int vRes);
int sceFontGetShadowImageRect(int fontHandle, int charCode, int shadowRectPtr);
int sceFontGetFontInfoByIndexNumber(int fontLibHandle, int fontInfoPtr, int fontIndex);
int sceFontGetShadowGlyphImage(int fontHandle, int charCode, int shadowGlyphImagePtr);
int sceFontDoneLib(int fontLibHandle);
int sceFontOpenUserFile(int fontLibHandle, int fileNameAddr, int mode, int errorCodePtr);
int sceFontGetCharImageRect(int fontHandle, int charCode, int charRectPtr);
int sceFontGetShadowGlyphImage_Clip(int fontHandle, int charCode, int shadowGlyphImagePtr, int clipXPos, int clipYPos, int clipWidth, int clipHeight);
int sceFontNewLib(int paramsPtr, int errorCodePtr);
int sceFontFindFont(int fontLibHandle, int fontStylePtr, int errorCodePtr);
int sceFontPixelToPointH(int fontLibHandle, int fontPixelsH, int errorCodePtr);
int sceFontGetCharGlyphImage(int fontHandle, int charCode, int glyphImagePtr);
int sceFontOpen(int fontLibHandle, int index, int mode, int errorCodePtr);
int sceFontGetShadowInfo(int fontHandle, int charCode, int shadowCharInfoPtr);
int sceFontOpenUserMemory(int fontLibHandle, int memoryFontPtr, int memoryFontLength, int errorCodePtr);
int sceFontGetFontList(int fontLibHandle, int fontStylePtr, int numFonts);
int sceFontGetCharGlyphImage_Clip(int fontHandle, int charCode, int glyphImagePtr, int clipXPos, int clipYPos, int clipWidth, int clipHeight);
int sceFontGetCharInfo(int fontHandle, int charCode, int charInfoPtr);
int sceFontSetAltCharacterCode(int fontLibHandle, int charCode);
int sceFontPixelToPointV(int fontLibHandle, int fontPixelsV, int errorCodePtr);

#endif /* IMPORTS_H_ */


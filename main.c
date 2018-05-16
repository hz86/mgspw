#include <pspkernel.h>
#include "mgpchs.h"

PSP_MODULE_INFO("jmpFont_Library", 0x0006, 1, 1);

static int jmpFont_Thread(SceSize args, void *argp)
{
	char libfont[] = "disc0:/PSP_GAME/USRDIR/modules/libfont.prx";
	SceUID libfont_modid = sceKernelLoadModule(libfont, 0, NULL);
	if(libfont_modid >= 0)
	{
		sceKernelStartModule(libfont_modid, 0, NULL, NULL, NULL);
		mgpchs_in();
	}
	sceKernelExitDeleteThread(0);
	return 0;
}

int module_start(SceSize args, void *argp)
{
	SceUID thid = sceKernelCreateThread("jmpFont_Thread", jmpFont_Thread, 0x18, 0x800, 0, NULL);
	if(thid >= 0) sceKernelStartThread(thid, 0, NULL);
	return 0;
}

int module_stop (SceSize args, void *argp)
{
	mgpchs_un();
	return 0;
}


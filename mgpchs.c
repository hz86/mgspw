#include <pspkernel.h>
#include <string.h>
#include "mgpchs.h"
#include "libadler.h"

static SceUID file = -1;
static SceUID headeruid = -1;
static unsigned int header = 0;
static unsigned int headersize = 0;
static unsigned int hook_loc_000714C8 = 0;

//计算olang长度
static unsigned int getolanglen(unsigned int data, unsigned int len)
{
	if(len < 4) return 0;
	if(0x00584252 != *(unsigned int *)data) return 0;

	unsigned int offset1 = *(unsigned int *)(data + 24);
	unsigned int offset2 = *(unsigned int *)(data + 28);

	unsigned int offsetmax = 0;
	unsigned int offset3 = offset1;
	while(offset3 < offset2) {
		unsigned int tmp = *(unsigned int *)(data + offset3 + 4);
		offsetmax = tmp > offsetmax ? tmp : offsetmax;
		offset3 += 12;
	}

	char *s, *str = (char *)(data + offset2 + offsetmax);
	for (s = str; *s; ++s);
	unsigned int ret = offset2 + offsetmax + (s - str + 1);
	return ret % 2 ? ret + 1: ret;
}

//计算ypk长度
static unsigned int getypklen(unsigned int data, unsigned int len)
{
	if(len < 4) return 0;
	unsigned int offset = 0;
	while(1) {
		if(0x00545447 != *(unsigned int *)(data + offset)) break;
		unsigned short slen = *(unsigned short *)(data + offset + 12);
		unsigned short alen = slen % 16;
		alen = alen ? slen + (16-alen) : slen;
		offset += alen;
	}
	return offset;
}

//ohd其中一种
static unsigned int getohdlen(unsigned int data, unsigned int len)
{
	if(len < 8) return 0;
	if(0x0000001B != *(unsigned int *)data) return 0;
	if(0x00000004 != *(unsigned int *)(data + 4)) return 0;
	return (*(unsigned int *)(data + 8)) * 128 + 12;
}

//内存补丁
static int pw_chs_patch(unsigned int k32, unsigned int data, unsigned int len)
{
	for(unsigned int i = 0; i < headersize; i++)
	{
		if(k32 == *(unsigned int *)(header + i*12))
		{
			unsigned int offset = *(unsigned int *)(header + i*12 + 4);
			unsigned int size = *(unsigned int *)(header + i*12 + 8);
			if(len == size) {
				sceIoLseek(file, offset, PSP_SEEK_SET);
				sceIoRead(file, (void *)data, len);
				return 1;
			}
		}
	}
	return 0;
}

static unsigned int j_loc_000714C8[4];
typedef unsigned int (*old_loc_000714C8)(unsigned int a0, unsigned int a1, unsigned int a2, unsigned int a3, unsigned int t0, unsigned int t1, unsigned int t2);
static unsigned int loc_000714C8(unsigned int a0, unsigned int a1, unsigned int a2, unsigned int a3, unsigned int t0, unsigned int t1, unsigned int t2)
{
	if(a1 && a2)	//a1 数据指针, a2 数据大小
	{
		unsigned int len = 0;
		if(!len) len = getolanglen(a1, a2);
		if(!len) len = getypklen(a1, a2);
		if(!len) len = getohdlen(a1, a2);

		if(len)
		{
			unsigned int k32 = Adler32(1, (void *)a1, len);
			pw_chs_patch(k32, a1, len);
		}
	}
	return ((old_loc_000714C8)j_loc_000714C8)(a0, a1, a2, a3, t0, t1, t2);
}

static void hook_loc_000714C8_in(void)
{
	//asm
	unsigned int *address = (unsigned int *)0x088754C8;

	j_loc_000714C8[0] = address[0];
	j_loc_000714C8[1] = address[1];
	j_loc_000714C8[2] = 0x08000000 | ((unsigned int)&address[2] & 0x0FFFFFFC) >> 2;	//j
	j_loc_000714C8[3] = 0;	//nop

	address[0] = 0x08000000 | ((unsigned int)loc_000714C8 & 0x0FFFFFFC) >> 2;	//j
	address[1] = 0;	//nop

	sceKernelDcacheWritebackInvalidateRange(address, 8);
	sceKernelIcacheInvalidateRange(address, 8);
}

static void hook_loc_000714C8_un(void)
{
	//asm
	unsigned int *address = (unsigned int *)0x088754C8;
	address[0] = j_loc_000714C8[0];
	address[1] = j_loc_000714C8[1];

	sceKernelDcacheWritebackInvalidateRange(address, 8);
	sceKernelIcacheInvalidateRange(address, 8);
}

void mgpchs_in(void)
{
	file = sceIoOpen("disc0:/PSP_GAME/USRDIR/PW.CHS", PSP_O_RDONLY, 0777);
	if(file >= 0)
	{
		if(sceIoRead(file, &headersize, 4) == 4)
		{
			headeruid = sceKernelAllocPartitionMemory(2, "mgpchs", PSP_SMEM_Low, headersize * 12, NULL);
			if(headeruid >= 0)
			{
				header = (unsigned int)sceKernelGetBlockHeadAddr(headeruid);
				if(sceIoRead(file, (void *)header, headersize * 12) == headersize * 12) {
					hook_loc_000714C8_in(); hook_loc_000714C8 = 1;
					return;
				}
				sceKernelFreePartitionMemory(headeruid);
				headeruid = -1;
			}
		}
		sceIoClose(file);
		file = -1;
	}
}

void mgpchs_un(void)
{
	if(hook_loc_000714C8) {
		hook_loc_000714C8_un();
		hook_loc_000714C8 = 0;
	}

	if(headeruid >= 0) {
		sceKernelFreePartitionMemory(headeruid);
		headeruid = -1;
	}

	if(file >= 0) {
		sceIoClose(file);
		file = -1;
	}
}



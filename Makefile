TARGET = jmpfont
OBJS = main.o jmpfont.o imports.o libadler.o mgpchs.o

INCDIR = 
CFLAGS = -O2 -G0 -Wall -std=c99
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

PRX_EXPORTS = exports.exp
PSP_FW_VERSION = 620
BUILD_PRX = 1

LIBDIR = 
LDFLAGS = -mno-crt0 -nostartfiles
LIBS = 

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak



TOP:=../

TOOLCHAIN=arm-elf-eabi

AS := $(TOOLCHAIN)-as
CC := $(TOOLCHAIN)-gcc
LD := $(TOOLCHAIN)-ld

TARG:=kernel
CFLAGS:=\
	-nostdlib\
	-ffreestanding\
	-DLOGLEVEL=KLOG_DEBUG\
	-Wall -pedantic\
	-Wno-long-long\
	-O2 -g3\
	-I. -I$(TOP)/port
OBJS:=\
	boot.o\
	main.o
LIBS:=\
	-lgcc
#include $(TOP)/port/Makefile

$(TARG).bin: $(TARG)
	$(TOOLCHAIN)-objcopy $(TARG) -O binary $@

$(TARG): $(OBJS) link.ld
	$(CC) $(CFLAGS) $(LDFLAGS) -Tlink.ld -o $@ $(OBJS) $(LIBS)
clean:
	rm -f $(TARG) $(TARG).bin *.o

raspboot: $(TARG).bin
	raspbootcom /dev/ttyUSB0 $(TARG).bin

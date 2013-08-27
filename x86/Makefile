
TOP:=../

TOOLCHAIN=i586-elf

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
	main.o\
	serial.o\
	gdt.o
LIBS:=\
	-lgcc
include $(TOP)/port/Makefile

$(TARG): $(OBJS) link.ld
	$(CC) $(CFLAGS) $(LDFLAGS) -Tlink.ld -o $@ $(OBJS) $(LIBS)
clean:
	rm -f $(TARG) *.o

qemu: $(TARG)
	qemu-system-i386 -kernel $(TARG) -serial stdio
qemu-debug: $(TARG)
	qemu-system-i386 -kernel $(TARG) -serial stdio -s -S

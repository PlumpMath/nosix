
TOOLCHAIN=i586-elf

AS = $(TOOLCHAIN)-as
CC = $(TOOLCHAIN)-gcc
LD = $(TOOLCHAIN)-ld

TARG=kernel
CFLAGS=\
	-nostdlib\
	-ffreestanding\
	-Wall -pedantic\
	-O2 -g3
OBJS=\
	boot.o\
	main.o\
	serial.o
LIBS=\
	-lgcc

$(TARG): $(OBJS) link.ld
	$(CC) $(CFLAGS) $(LDFLAGS) -Tlink.ld -o $@ $(OBJS) $(LIBS)
clean:
	rm -f $(TARG) *.o

qemu: $(TARG)
	qemu-system-i386 -kernel $(TARG) -serial stdio
qemu-debug: $(TARG)
	qemu-system-i386 -kernel $(TARG) -serial stdio -s -S

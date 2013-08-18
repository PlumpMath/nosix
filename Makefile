
ASFLAGS=--32
LDFLAGS=-melf_i386
CFLAGS=\
	-m32\
	-nostdlib\
	-fno-builtin\
	-ffreestanding\
	-Wall -std=c99 -pedantic\
	-O2
OBJS=\
	boot.o\
	main.o
TARG=kernel

$(TARG): $(OBJS) link.ld
	$(LD) $(LDFLAGS) -Tlink.ld -o $@ $(OBJS)
clean:
	rm -f $(TARG) *.o


ASFLAGS=--32
LDFLAGS=-melf_i386

OBJS=\
	boot.o
TARG=kernel

$(TARG): $(OBJS) link.ld
	$(LD) $(LDFLAGS) -Tlink.ld -o $@ $(OBJS)
clean:
	rm -f $(TARG) *.o

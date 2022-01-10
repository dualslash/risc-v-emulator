TARGETS = hello.bin hellof.bin \
	comp.bin \
	matvec.bin matvecu.bin \
	sumdemo.bin

CC = riscv64-unknown-elf-gcc
CFLAGS = -Wall -O0 -nostdlib -fno-builtin -nodefaultlibs
CRT = minicrt-riscv.s

all:		$(TARGETS)

hello.bin:	hello.c
		$(CC) $(CFLAGS) -o $@ $< $(CRT)

hellof.bin:	hellof.c
		$(CC) $(CFLAGS) -o $@ $< $(CRT)

%.bin:		%.c
		$(CC) $(CFLAGS) -o $@ $< roman.c $(CRT)

clean:
		rm -f $(TARGETS)

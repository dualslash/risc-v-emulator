#
# rv64-emu -- Simple 64-bit RISC-V simulator
#

SHELL = /bin/bash

runtests:	../rv64-emu
		@echo "Running unit tests ..."
		@pass=0;failed=0;			\
		for testfile in *.conf; do	\
			echo -en "+ $$testfile\t";	\
			../rv64-emu -t $$testfile;	\
			if [ $$? -eq 0 ]; then		\
				echo "OK";		\
				pass=$$((pass+1));	\
			else				\
				echo "FAIL";		\
				failed=$$((failed+1));	\
			fi;				\
		done;					\
		echo "$$pass passed; $$failed failed"

%.bin:		%.s
		riscv64-unknown-elf-gcc -Wall -O0 -nostdlib -fno-builtin -nodefaultlibs -o $@ $<

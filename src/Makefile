#
# rv64-emu -- Simple 64-bit RISC-V simulator
#

CXX = c++
CXXFLAGS = -std=c++14 -Wall -g


OBJECTS = \
	alu.o \
	config-file.o \
	elf-file.o \
	inst-decoder.o \
	inst-formatter.o \
	main.o \
	memory.o \
	memory-bus.o \
	processor.o \
	serial.o \
	sys-control.o

HEADERS = \
	alu.h \
	arch.h \
	config-file.h \
	elf-file.h \
	inst-decoder.h \
	memory.h \
	memory-bus.h \
	memory-interface.h \
	processor.h \
	reg-file.h \
	serial.h \
	sys-control.h


all:    	rv64-emu

rv64-emu:	$(OBJECTS)
		$(CXX) $(CXXFLAGS) -o $@ $(OBJECTS)

%.o:		%.cc $(HEADERS)
		$(CXX) $(CXXFLAGS) -c $<

clean:
		rm -f rv64-emu
		rm -f $(OBJECTS)

runtests:	rv64-emu
		make -C tests

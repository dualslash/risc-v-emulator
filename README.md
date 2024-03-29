# 64 Bit RISC-V ISA Emulator

RISC-V to x86/64 instruction emulator accepting RISC-V ELF binaries for Unix written in C++.

## Requirements

* Unix Environment
* GCC/G++
* RISC-V ELF `sudo apt install gcc-riscv64-unknown-elf`

## Usage

    ./rv64-emu [-d] [-r register] <programFilename>
    ./rv64-emu [-d] -t testfile

    Where 'register' is a register initializer in the form
    rX=Y with X a register number and Y the initializer value.
    'testfile' is a unit test configuration file.

    -d enables debug mode in which every decoded instruction is 
    printed to the terminal.

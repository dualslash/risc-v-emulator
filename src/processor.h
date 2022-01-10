/*
 * rv64-emu -- Simple 64-bit RISC-V simulator
 * processor.h - Processor class tying all components together.
 */

#ifndef __PROCESSOR_H__
#define __PROCESSOR_H__

#pragma once

#include "arch.h"

#include "elf-file.h"
#include "inst-decoder.h"
#include "alu.h"
#include "memory-bus.h"
#include "memory.h"
#include "sys-control.h"

class Processor
{
  public:
    Processor(ELFFile &program, bool debugMode=false);

    /* Command-line register initialization 
		*/
    void initRegister(RegNumber regnum, RegValue value);
    RegValue getRegister(RegNumber regnum) const;

    /* Instruction execution steps 
		*/
    bool run(bool testMode=false);

    void instructionFetch(void);
    bool instructionDecode(void);
    void execute(void);
    void memory(void);
    void writeBack(void);

    /* Debugging and statistics 
		*/
    void dumpRegisters(void) const;
    void dumpStatistics(void) const;

  private:
    bool debugMode;

    /* Statistics 
		*/
    int nCycles;
    int nInstructions;

    /* Components making up the system 
		*/
    MemAddress PC;
    uint32_t instruction;
    DecodedInstruction decoded;
    RegValue result;

    InstructionDecoder decoder;
    RegisterFile regfile;
    ALU alu;

    MemoryBus bus;
    std::shared_ptr<SysControl> control;
};

#endif /* __PROCESSOR_H__ */

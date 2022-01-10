/*
 * rv64-emu -- Simple 64-bit RISC-V simulator
 * alu.h - ALU component.
 */

#ifndef __ALU_H__
#define __ALU_H__

#pragma once

#include "inst-decoder.h"
#include "reg-file.h"
#include "memory-bus.h"
#include "arch.h"

#include <map>

/* The ALU component performs the specified operation on operands A and B,
 * placing the result in result. The operation is specified through
 * opcode and/or function code.
 */

class ALU
{
  public:
    void clear();
    void setA(RegValue A) { this->A = A; }
    void setB(RegValue B) { this->B = B; }

    RegValue getResult() const { return result; }
    RegValue getFlag() const { return flag; }

    void execute(DecodedInstruction data,RegisterFile & reg, MemAddress & PC);
    void memorycontroller(DecodedInstruction data,RegisterFile & reg,MemoryBus & mem);

  private:
    void add(RegValue L, RegValue R);
    void sub(RegValue L, RegValue R);
    void li(int I);
    void addi(RegValue L, int I);
    void sll(RegValue L, int I);
    void srl(RegValue L, int I);
    void mv(RegValue L);
    void andi(RegValue L, int I);

    void beq(RegValue L, RegValue R, MemAddress addr, MemAddress & PC);
    void bne(RegValue L, RegValue R, MemAddress addr, MemAddress & PC);
    void blt(RegValue L, RegValue R, MemAddress addr, MemAddress & PC);
    void ble(RegValue L, RegValue R, MemAddress addr, MemAddress & PC);
    void call(MemAddress addr, MemAddress & PC);
    void jump(MemAddress addr, MemAddress & PC);

    void store(RegValue addr, RegValue value, int funct3, MemoryBus & mem);
    void load(RegValue addr, int funct3, MemoryBus & mem);

    RegValue A;
    RegValue B;
    RegValue result;
    RegValue flag;
};

#endif /* __ALU_H__ */

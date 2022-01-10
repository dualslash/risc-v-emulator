/* 
 * rv64-emu -- Simple 64-bit RISC-V simulator
 * alu.h - ALU component.
 */

#include "alu.h"
#include "memory.h"

#include <iostream>

#include <stdexcept>

#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>

#include <cstdlib>
#include <cstring>

#include <bitset>

void
ALU::execute(DecodedInstruction data,RegisterFile & reg, MemAddress & PC)
{
  ////////////
  // R-TYPE //
  ////////////
  if(data.opcode == 0x33 || data.opcode == 0x3b)
  {
    if(data.funct5 == 0x00)
      add(reg.readRegister(data.reg[1]),reg.readRegister(data.reg[2]));
    if(data.funct5 == 0x08)
      sub(reg.readRegister(data.reg[1]),reg.readRegister(data.reg[2]));
  }

  ////////////
  // I-TYPE //
  ////////////
  if(data.opcode == 0x13 || data.opcode == 0x1b)
  {
    if(data.funct3 == 0x00)
    {
      if(!data.reg[1])
        li(data.immediate);
      else if(!data.reg[2])
        addi(reg.readRegister(data.reg[1]),data.immediate);
      else
        mv(reg.readRegister(data.reg[1]));
    }

    if(data.funct3 == 0x01)
    {
      sll(reg.readRegister(data.reg[1]),data.immediate);
    }

    if(data.funct3 == 0x05)
    {
      srl(reg.readRegister(data.reg[1]),data.immediate);
    }

    if(data.funct3 == 0x07)
    {
      andi(reg.readRegister(data.reg[1]),data.immediate);
    }
  }

  if(data.opcode == 0x67)
  {
    jump(reg.readRegister(data.reg[1]),PC);
  }

  /////////////
  // SB-TYPE //
  /////////////
  if(data.opcode == 0x63)
  {
    if(data.funct3 == 0x00)
    {
      beq(reg.readRegister(data.reg[1]),reg.readRegister(data.reg[2]),data.immediate,PC);
    }

    if(data.funct3 == 0x01)
    {
      bne(reg.readRegister(data.reg[1]),reg.readRegister(data.reg[2]),data.immediate,PC);
    }

    if(data.funct3 == 0x04)
    {
      blt(reg.readRegister(data.reg[1]),reg.readRegister(data.reg[2]),data.immediate,PC);
    }

    if(data.funct3 == 0x05 || data.funct3 == 0x07)
    {
      ble(reg.readRegister(data.reg[1]),reg.readRegister(data.reg[2]),data.immediate,PC);
    }
  }

  ////////////
  // U-TYPE //
  ////////////
  if(data.opcode == 0x37)
  {
    result = data.immediate * 0x1000;
  }

  /////////////
  // UJ-TYPE //
  /////////////
  if(data.opcode == 0x6f)
  {
    result = PC;
    call(data.immediate,PC);
  }
}

void
ALU::memorycontroller(DecodedInstruction data,RegisterFile & reg,MemoryBus & mem)
{

  ////////////
  // S-TYPE //
  ////////////
  if(data.opcode == 0x23)
  {
    addi(reg.readRegister(data.reg[1]),data.immediate);
    store(getResult(),reg.readRegister(data.reg[2]),data.funct3,mem);
  }

  ////////////
  // I-TYPE //
  ////////////
  if(data.opcode == 0x03)
  {
    addi(reg.readRegister(data.reg[1]),data.immediate);
    load(getResult(),data.funct3,mem);
  }
}

//////////
// META //
//////////
void
ALU::clear()
{
  result = 0;
  flag = false;
}

////////////////
// ARITHMETIC //
//   &LOGIC   //
////////////////
void
ALU::add(RegValue L, RegValue R)
{
  result = L + R;
}

void
ALU::sub(RegValue L, RegValue R)
{
  result = L - R;
}

void
ALU::li(int I)
{
  result = I;
}

void
ALU::addi(RegValue L, int I)
{
  result = L + I;
}

void
ALU::sll(RegValue L, int I)
{
  std::bitset<64> R1 = std::bitset<64>(L);
  R1 = (R1<<I);

  result = R1.to_ulong();
}

void
ALU::srl(RegValue L, int I)
{
  std::bitset<64> R1 = std::bitset<64>(L);
  R1 = (R1>>I);

  result = R1.to_ulong();
}

void
ALU::mv(RegValue L)
{
  result = L;
}

void
ALU::andi(RegValue L, int I)
{
    std::bitset<64> R1 = std::bitset<64>(L);
    std::bitset<64> R2 = std::bitset<64>(I);
    std::bitset<64> R3 = (R1&=R2);

    result = R3.to_ulong();
}

/////////////
// CONTROL //
/////////////
void
ALU::beq(RegValue L, RegValue R, MemAddress addr, MemAddress & PC)
{
  if(L == R)
    call(addr,PC);
}

void
ALU::bne(RegValue L, RegValue R, MemAddress addr, MemAddress & PC)
{
  if(L != R)
    call(addr,PC);
}

void
ALU::blt(RegValue L, RegValue R, MemAddress addr, MemAddress & PC)
{
  if(L < R)
    call(addr,PC);
}

void
ALU::ble(RegValue L, RegValue R, MemAddress addr, MemAddress & PC)
{
  if(L >= R)
    call(addr,PC);
}

void
ALU::call(MemAddress addr, MemAddress & PC)
{
  PC += ((addr * 4) - 4);
}

void
ALU::jump(MemAddress addr, MemAddress & PC)
{
  PC = addr;
}

////////////
// MEMORY //
////////////
void
ALU::store(RegValue addr, RegValue value, int funct3, MemoryBus & mem)
{
  int size;

  if(funct3 == 0x00)
    size = 1;
  if(funct3 == 0x01)
    size = 2;
  if(funct3 == 0x02)
    size = 4;
  if(funct3 == 0x03)
    size = 8;

  uint8_t *segment = NULL;
  uint8_t align = 16;
  posix_memalign((void **)&segment, align, size);
  memset(segment, 0, size);

  std::shared_ptr<Memory> memory(new Memory("data", segment,
                                            addr,
                                            size));
  memory->setMayWrite(true);

  mem.addClient(std::shared_ptr<MemoryInterface>(memory));

  if(funct3 == 0x00)
    mem.writeByte(addr,value);
  if(funct3 == 0x01)
    mem.writeHalfWord(addr,value);
  if(funct3 == 0x02)
    mem.writeWord(addr,value);
  if(funct3 == 0x03)
    mem.writeDoubleWord(addr,value);
}

void
ALU::load(RegValue addr, int funct3, MemoryBus & mem)
{
  if(funct3 == 0x00 || funct3 == 0x04)
    result = mem.readByte(addr);
  if(funct3 == 0x01 || funct3 == 0x05)
    result = mem.readHalfWord(addr);
  if(funct3 == 0x02 || funct3 == 0x06)
    result = mem.readWord(addr);
  if(funct3 == 0x03 || funct3 == 0x07)
    result = mem.readDoubleWord(addr);
}

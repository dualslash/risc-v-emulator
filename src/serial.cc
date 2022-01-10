/*
 * rv64-emu -- Simple 64-bit RISC-V simulator
 * serial.cc - Write-only serial interface.
 */

#include "serial.h"

#include <iostream>

Serial::Serial(const MemAddress base)
  : base(base)
{
}

Serial::~Serial()
{
}

/*
 * MemoryInterface
 */

uint8_t
Serial::readByte(MemAddress addr)
{
  throw IllegalAccess("Not supported on serial interface");
}

uint16_t
Serial::readHalfWord(MemAddress addr)
{
  throw IllegalAccess("Not supported on serial interface");
}

uint32_t
Serial::readWord(MemAddress addr)
{
  throw IllegalAccess("Not supported on serial interface");
}

uint64_t
Serial::readDoubleWord(MemAddress addr)
{
  throw IllegalAccess("Not supported on serial interface");
}


void
Serial::writeByte(MemAddress addr, uint8_t value)
{
  if (addr != base)
    throw IllegalAccess("Invalid address");

  std::cerr << (char)value;
}

void
Serial::writeHalfWord(MemAddress addr, uint16_t value)
{
  throw IllegalAccess("Not supported on serial interface");
}

void
Serial::writeWord(MemAddress addr, uint32_t value)
{
  throw IllegalAccess("Not supported on serial interface");
}

void
Serial::writeDoubleWord(MemAddress addr, uint64_t value)
{
  throw IllegalAccess("Not supported on serial interface");
}

bool
Serial::contains(MemAddress addr) const
{
  return base <= addr && addr < base + 1;
}

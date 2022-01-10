/*
 * rv64-emu -- Simple 64-bit RISC-V simulator
 * sys-control.h - System control module.
 */

#include "sys-control.h"

#include <iostream>

SysControl::SysControl(const MemAddress base)
  : base(base), shouldHaltFlag(false)
{
}

SysControl::~SysControl()
{
}

/*
 * MemoryInterface
 */

uint8_t
SysControl::readByte(MemAddress addr)
{
  throw IllegalAccess("Not supported on syscontrol interface");
}

uint16_t
SysControl::readHalfWord(MemAddress addr)
{
  throw IllegalAccess("Not supported on syscontrol interface");
}

uint32_t
SysControl::readWord(MemAddress addr)
{
  throw IllegalAccess("Not supported on syscontrol interface");
}

uint64_t
SysControl::readDoubleWord(MemAddress addr)
{
  throw IllegalAccess("Not supported on syscontrol interface");
}


void
SysControl::writeByte(MemAddress addr, uint8_t value)
{
  if (addr != base + 0x8)
    throw IllegalAccess("Invalid system controller address");

  std::cerr << "System halt requested." << std::endl;
  shouldHaltFlag = true;
}

void
SysControl::writeHalfWord(MemAddress addr, uint16_t value)
{
  throw IllegalAccess("Not supported on syscontrol interface");
}

void
SysControl::writeWord(MemAddress addr, uint32_t value)
{
  if (addr != base + 0x8)
    throw IllegalAccess("Invalid system controller address");

  std::cerr << "System halt requested." << std::endl;
  shouldHaltFlag = true;
}

void
SysControl::writeDoubleWord(MemAddress addr, uint64_t value)
{
  throw IllegalAccess("Not supported on syscontrol interface");
}

bool
SysControl::contains(MemAddress addr) const
{
  return base <= addr && addr < base + 0x10;
}

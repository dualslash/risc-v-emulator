/*
 * rv64-emu -- Simple 64-bit RISC-V simulator
 * memory.h - A simple memory.
 */

#include "memory.h"

#include <cstdlib>

#include <iostream>

Memory::Memory(const std::string &name,
               uint8_t * const data,
               const MemAddress base,
               const size_t size)
  : name(name), mayWrite(false), base(base), size(size), data(data)
{
}

Memory::~Memory()
{
  free(data);
}

void
Memory::setMayWrite(bool setting)
{
  mayWrite = setting;
}

/*
 * MemoryInterface
 */

template <typename T>
T
Memory::readData(MemAddress addr)
{
  if (! canAccess(addr, sizeof(T), false))
    throw IllegalAccess(addr, sizeof(T));

  MemAddress effectiveAddr = addr - base;

  return *(T *)(data + effectiveAddr);
}

uint8_t
Memory::readByte(MemAddress addr)
{
  return readData<uint8_t>(addr);
}

uint16_t
Memory::readHalfWord(MemAddress addr)
{
  return readData<uint16_t>(addr);
}

uint32_t
Memory::readWord(MemAddress addr)
{
  return readData<uint32_t>(addr);
}

uint64_t
Memory::readDoubleWord(MemAddress addr)
{
  return readData<uint64_t>(addr);
}


template <typename T>
void
Memory::writeData(MemAddress addr, T value)
{
  if (! canAccess(addr, sizeof(value), true))
    throw IllegalAccess(addr, sizeof(value));

  MemAddress effectiveAddr = addr - base;
  *(T *)(data + effectiveAddr) = value;
}

void
Memory::writeByte(MemAddress addr, uint8_t value)
{
  writeData(addr, value);
}

void
Memory::writeHalfWord(MemAddress addr, uint16_t value)
{
  writeData(addr, value);
}

void
Memory::writeWord(MemAddress addr, uint32_t value)
{
  writeData(addr, value);
}

void
Memory::writeDoubleWord(MemAddress addr, uint64_t value)
{
  writeData(addr, value);
}

bool
Memory::contains(MemAddress addr) const
{
  return base <= addr && addr < base + size;
}


/*
 * Private methods
 */
bool
Memory::canAccess(MemAddress addr, size_t size, bool write) const
{
  if (addr < base || addr + size > base + this->size)
    return false;

  if (write && !mayWrite)
    return false;

  return true;
}

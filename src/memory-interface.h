/*
 * rv64-emu -- Simple 64-bit RISC-V simulator
 * memory-interface.h - Interface for memory bus clients.
 */

#ifndef __MEMORY_INTERFACE_H__
#define __MEMORY_INTERFACE_H__

#include "arch.h"

#include <stdexcept>
#include <string>
#include <sstream>
#include <iomanip>

#include <cstdint>

class MemoryInterface
{
  public:
    virtual uint8_t readByte(MemAddress addr) = 0;
    virtual uint16_t readHalfWord(MemAddress addr) = 0;
    virtual uint32_t readWord(MemAddress addr) = 0;
    virtual uint64_t readDoubleWord(MemAddress addr) = 0;

    virtual void writeByte(MemAddress addr, uint8_t value) = 0;
    virtual void writeHalfWord(MemAddress addr, uint16_t value) = 0;
    virtual void writeWord(MemAddress addr, uint32_t value) = 0;
    virtual void writeDoubleWord(MemAddress addr, uint64_t value) = 0;

    virtual bool contains(MemAddress addr) const = 0;
};

/* Exception that is thrown when an illegal memory address and/or access
 * is encountered.
 */
class IllegalAccess : public std::exception
{
  public:
    explicit IllegalAccess(const char *what)
      : message(what)
    { }

    explicit IllegalAccess(const MemAddress addr)
    {
      std::stringstream ss;
      ss << "Invalid access at " << std::hex << addr;
      message = ss.str();
    }

    explicit IllegalAccess(const MemAddress addr, const size_t size)
    {
      std::stringstream ss;
      ss << "Invalid access of size " << size << " at " << std::hex << addr;
      message = ss.str();
    }

    virtual const char* what() const noexcept override
    {
      return message.c_str();
    }

  private:
    std::string message;
};

#endif /* __MEMORY_INTERFACE_H__ */

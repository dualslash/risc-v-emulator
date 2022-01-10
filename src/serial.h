/*
 * rv64-emu -- Simple 64-bit RISC-V simulator
 * serial.h - Dumb write-only serial interface.
 */

#ifndef __SERIAL_H__
#define __SERIAL_H__

#include "memory-interface.h"

class Serial : public MemoryInterface
{
  public:
    Serial(const MemAddress base);
    virtual ~Serial();

    /* MemoryInterface 
		*/
    virtual uint8_t readByte(MemAddress addr) override;
    virtual uint16_t readHalfWord(MemAddress addr) override;
    virtual uint32_t readWord(MemAddress addr) override;
    virtual uint64_t readDoubleWord(MemAddress addr) override;

    virtual void writeByte(MemAddress addr, uint8_t value) override;
    virtual void writeHalfWord(MemAddress addr, uint16_t value) override;
    virtual void writeWord(MemAddress addr, uint32_t value) override;
    virtual void writeDoubleWord(MemAddress addr, uint64_t value) override;

    virtual bool contains(MemAddress addr) const override;

  private:
    const MemAddress base;
};

#endif /* __SERIAL_H__ */

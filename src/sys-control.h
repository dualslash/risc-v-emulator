/* 
 * rv64-emu -- Simple 64-bit RISC-V simulator
 * sys-control.h - System control module.
 */

/* The system control module currently only supported halting the
 * system. Other functionalities could be implemented here at different
 * memory addresses. (For instance, reading the instruction counter).
 */

#ifndef __SYS_CONTROL_H__
#define __SYS_CONTROL_H__

#include "memory-interface.h"

class SysControl : public MemoryInterface
{
  public:
    SysControl(const MemAddress base);
    virtual ~SysControl();

    bool shouldHalt(void) const { return shouldHaltFlag; }

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

    bool shouldHaltFlag;
};

#endif /* __SYS_CONTROL_H__ */

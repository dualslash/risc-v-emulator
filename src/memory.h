/*
 * rv64-emu -- Simple 64-bit RISC-V simulator
 * memory.h - A simple memory.
 */

#ifndef __MEMORY_H__
#define __MEMORY_H__

#include "memory-interface.h"

#include <memory>
#include <string>

class Memory : public MemoryInterface
{
  public:
    /* Constructor transfers ownership of data to this new object. 
		*/
    Memory(const std::string &name,
           uint8_t * const data,
           const MemAddress base,
           const size_t size);
    virtual ~Memory();

    void setMayWrite(bool setting);

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
    const std::string name;

    /* Assume memory may always be read. Do not maintain
     * separate execute bit.
     */
    bool mayWrite;

    const MemAddress base;
    const size_t size;

    /* We are being passed in dynamically-aligned memory areas which
     * are allocated using C functions (to save trouble). So we don't
     * bother using a unique_ptr in this case.
     */
    uint8_t * const data;

    /* Private helper methods 
		*/
    bool canAccess(MemAddress addr, size_t size, bool write) const;

    template <typename T>
    T readData(MemAddress addr);
    template <typename T>
    void writeData(MemAddress addr, T value);
};

#endif /* __MEMORY_H__ */

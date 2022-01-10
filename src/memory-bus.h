/*
 * rv64-emu -- Simple 64-bit RISC-V simulator
 * memory-bus.h - "Interconnect" for different memory bus clients.
 */

#ifndef __MEMORY_BUS_H__
#define __MEMORY_BUS_H__

#include "memory-interface.h"

#include <memory>
#include <vector>

class MemoryBus : public MemoryInterface
{
  public:
    MemoryBus(std::vector<std::shared_ptr<MemoryInterface> > &&clients);
    virtual ~MemoryBus();

    void addClient(std::shared_ptr<MemoryInterface> client);

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
    std::vector<std::shared_ptr<MemoryInterface> > clients;

    std::shared_ptr<MemoryInterface> findClient(MemAddress addr) noexcept;
    std::shared_ptr<MemoryInterface> getClient(MemAddress addr);
};

#endif /* __MEMORY_BUS_H__ */

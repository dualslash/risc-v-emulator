/*
 * rv64-emu -- Simple 64-bit RISC-V simulator
 * memory-bus.h - "Interconnect" for different memory bus clients.
 */

#include "memory-bus.h"

MemoryBus::MemoryBus(std::vector<std::shared_ptr<MemoryInterface> > &&clients)
  : clients(std::move(clients))
{
}

MemoryBus::~MemoryBus()
{
}

void
MemoryBus::addClient(std::shared_ptr<MemoryInterface> client)
{
  clients.push_back(client);
}

uint8_t
MemoryBus::readByte(MemAddress addr)
{
  return getClient(addr)->readByte(addr);
}

uint16_t
MemoryBus::readHalfWord(MemAddress addr)
{
  return getClient(addr)->readHalfWord(addr);
}

uint32_t
MemoryBus::readWord(MemAddress addr)
{
  return getClient(addr)->readWord(addr);
}

uint64_t
MemoryBus::readDoubleWord(MemAddress addr)
{
  return getClient(addr)->readDoubleWord(addr);
}

void
MemoryBus::writeByte(MemAddress addr, uint8_t value)
{
  return getClient(addr)->writeByte(addr, value);
}

void
MemoryBus::writeHalfWord(MemAddress addr, uint16_t value)
{
  return getClient(addr)->writeHalfWord(addr, value);
}

void
MemoryBus::writeWord(MemAddress addr, uint32_t value)
{
  return getClient(addr)->writeWord(addr, value);
}

void
MemoryBus::writeDoubleWord(MemAddress addr, uint64_t value)
{
  return getClient(addr)->writeDoubleWord(addr, value);
}

bool
MemoryBus::contains(MemAddress addr) const
{
  return true;
}

/*
 * Private methods
 */
std::shared_ptr<MemoryInterface>
MemoryBus::findClient(MemAddress addr) noexcept
{
  for (auto &client : clients)
    if (client->contains(addr))
      return client;

  return nullptr;
}

std::shared_ptr<MemoryInterface>
MemoryBus::getClient(MemAddress addr)
{
  auto client = findClient(addr);
  if (!client)
    throw IllegalAccess(addr);

  return client;
}

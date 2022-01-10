/*
 * rv64-emu -- Simple 64-bit RISC-V simulator
 * arch.h - Definitions specifying architectural properties
 */

#ifndef __ARCH_H__
#define __ARCH_H__

#include <cstdint>

/* Hard-coded values for the 64-bit RISC-V architecture.
 */
using RegValue = uint64_t;
using MemAddress = uint64_t;

static const int NumRegs = 32;
using RegNumber = uint8_t;
static const int MaxRegs = 256;

#endif /* __ARCH_H__ */

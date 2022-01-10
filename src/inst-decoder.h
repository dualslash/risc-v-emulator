/*
 * rv64-emu -- Simple 64-bit RISC-V simulator
 * inst-decoder.h - RISC-V instruction decoder.
 */

#ifndef __INST_DECODER_H__
#define __INST_DECODER_H__

#include "reg-file.h"

#include <stdexcept>
#include <cstdint>

/* Exception that should be thrown when an illegal instruction
 * is encountered.
 */
class IllegalInstruction : public std::runtime_error
{
  public:
    explicit IllegalInstruction(const std::string &what)
      : std::runtime_error(what)
    { }

    explicit IllegalInstruction(const char *what)
      : std::runtime_error(what)
    { }
};

/* Structure to keep together all data for a single decoded instruction.
 */
struct DecodedInstruction
{
  int opcode;
  int immediate;
  int funct2;
  int funct3;
  int funct5;
  int reg[3];
};

std::ostream &operator<<(std::ostream &os, const DecodedInstruction &decoded);


/* InstructionDecoder component to be used by class Processor 
*/
class InstructionDecoder
{
  public:
    void                decodeInstruction(const uint32_t instruction);
    DecodedInstruction  getDecodedInstruction(void) const;

  private:
    DecodedInstruction decoded;
};


#endif /* __INST_DECODER_H__ */

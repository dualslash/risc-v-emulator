/*
 * rv64-emu -- Simple 64-bit RISC-V simulator
 * inst-formatter.cc - RISC-V instruction printer (disassembler)
 */

#include "inst-decoder.h"

#include <functional>
#include <map>
#include <iostream>
#include <sstream>

#include <bitset>
#include <stdint.h>
#include <inttypes.h>

/* Output operator to print DecodedInstructions. 
*/
std::ostream &
operator<<(std::ostream &os, const DecodedInstruction &decoded)
{
  std::bitset<7> op(decoded.opcode);
  std::bitset<20> imm(decoded.immediate);
  std::bitset<2> f2(decoded.funct2);
  std::bitset<3> f3(decoded.funct3);
  std::bitset<5> f5(decoded.funct5);
  std::bitset<5> map0(decoded.reg[0]);
  std::bitset<5> map1(decoded.reg[1]);
  std::bitset<5> map2(decoded.reg[2]);

  /* print binary as well as hexadecimal operands for
   * each instruction
	*/
  os  << "imm: " << imm << "\t: 0x" << decoded.immediate << "\n"
      << "f5 : " << f5 << "\t\t\t: 0x" << decoded.funct5 << "\n"
      << "f2 : " << f2 << "\t\t\t\t: 0x" << decoded.funct2 << "\n"
      << "rs2: " << map2 << "\t\t\t: 0x" << decoded.reg[2] << "\n"
      << "rs1: " << map1 << "\t\t\t: 0x" << decoded.reg[1] << "\n"
      << "f3 : " << f3 << "\t\t\t: 0x" << decoded.funct3 << "\n"
      << "rd : " << map0 << "\t\t\t: 0x" << decoded.reg[0] << "\n"
      << "op : " << op << "\t\t\t: 0x" << decoded.opcode << "\n"
      << "\n";

  return os;
}

/* 
 * rv64-emu -- Simple 64-bit RISC-V simulator
 * inst-decoder.cc - RISC-V instruction decoder.
 */

#include "inst-decoder.h"

#include <functional>
#include <iostream>

#include <bitset>
#include <map>


/* Decodes a single instruction. The decoded instruction should be
 * stored in the class member "decoded" of type DecodedInstruction.
 */

void
InstructionDecoder::decodeInstruction(const uint32_t instruction)
{
  /* set the binary layout for each instruction parameters 
	*/
  std::bitset<7> op;
  std::bitset<20> imm;
  std::bitset<2> f2;
  std::bitset<3> f3;
  std::bitset<5> f5;
  std::bitset<5> map[3];
  std::bitset<32>bin(instruction);

  bool neg = false;

  ////////////
  // OPCODE //
  ////////////
  for(int i = 0; i < 7; i++)
    op.set(i,bin[i]);
  decoded.opcode = (int)(op.to_ulong());

  ////////////
  // I-TYPE //
  ////////////
  if(decoded.opcode == 0x13 || decoded.opcode == 0x03 || decoded.opcode == 0x67 || decoded.opcode == 0x1b)
  {
    for(int i = 7; i <= 11; i++)
      map[0].set(i-7,bin[i]);
    for(int i = 12; i <= 14; i++)
      f3.set(i-12,bin[i]);
    for(int i = 15; i <= 19; i++)
      map[1].set(i-15,bin[i]);
    for(int i = 20; i <= 31; i++)
      imm.set(i-20,bin[i]);

    /* correct immediate for negative value */
    if(imm.test(11))
    {
      neg = true;
      std::bitset<12> temp;
      temp = std::bitset<12>(imm.to_ulong());
      temp = ~temp;
      imm = std::bitset<20>(temp.to_ulong()+1);
    }
  }

  ////////////
  // S-TYPE //
  ////////////
  if(decoded.opcode == 0x23)
  {
      for(int i = 7; i <= 11; i++)
        imm.set(i-7,bin[i]);
      for(int i = 12; i <= 14; i++)
        f3.set(i-12,bin[i]);
      for(int i = 15; i <= 19; i++)
        map[1].set(i-15,bin[i]);
      for(int i = 20; i <= 24; i++)
        map[2].set(i-20,bin[i]);
      for(int i = 25; i <= 31; i++)
        imm.set(i-20,bin[i]);

      /* correct offset for negative value 
			*/
      if(imm.test(11))
      {
        neg = true;
        std::bitset<12> temp;
        temp = std::bitset<12>(imm.to_ulong());
        temp = ~temp;
        imm = std::bitset<20>(temp.to_ulong()+1);
      }
  }

  ////////////
  // R-TYPE //
  ////////////
  if(decoded.opcode == 0x33 || decoded.opcode == 0x3b)
  {
    for(int i = 7; i <= 11; i++)
      map[0].set(i-7,bin[i]);
    for(int i = 12; i <= 14; i++)
      f3.set(i-12,bin[i]);
    for(int i = 15; i <= 19; i++)
      map[1].set(i-15,bin[i]);
    for(int i = 20; i <= 24; i++)
      map[2].set(i-20,bin[i]);
    for(int i = 25; i <= 26; i++)
      f2.set(i-25,bin[i]);
    for(int i = 27; i <= 31; i++)
      f5.set(i-27,bin[i]);
  }

  /////////////
  // SB-TYPE //
  /////////////
  if(decoded.opcode == 0x63)
  {
    for(int i = 7; i <= 7; i++)
      imm.set(i+3,bin[i]);
    for(int i = 8; i <= 11; i++)
      imm.set(i-8,bin[i]);
    for(int i = 12; i <= 14; i++)
      f3.set(i-12,bin[i]);
    for(int i = 15; i <= 19; i++)
      map[1].set(i-15,bin[i]);
    for(int i = 20; i <= 24; i++)
      map[2].set(i-20,bin[i]);
    for(int i = 25; i <= 30; i++)
      imm.set(i-21,bin[i]);
    for(int i = 31; i <= 31; i++)
      imm.set(i-20,bin[i]);

    /* correct offset for negative value 
		*/
    if(imm.test(11))
    {
      neg = true;
      std::bitset<12> temp;
      temp = std::bitset<12>(imm.to_ulong());
      temp = ~temp;
      temp >>= 1;
      imm = std::bitset<20>(temp.to_ulong()+1);
    }
  }

  ////////////
  // U-TYPE //
  ////////////
  if(decoded.opcode == 0x37)
  {
    for(int i = 7; i <= 11; i++)
      map[0].set(i-7,bin[i]);
    for(int i = 12; i <= 31; i++)
      imm.set(i-12,bin[i]);
  }

  /////////////
  // UJ-TYPE //
  /////////////
  if(decoded.opcode == 0x6f)
  {
    for(int i = 7; i <= 11; i++)
      map[0].set(i-7,bin[i]);
    for(int i = 12; i <= 19; i++)
        imm.set(i-1,bin[i]);
    for(int i = 20; i <= 20; i++)
        imm.set(i-10,bin[i]);
    for(int i = 21; i <= 30; i++)
        imm.set(i-21,bin[i]);
    for(int i = 31; i <= 31; i++)
        imm.set(i-12,bin[i]);

    /* correct offset for negative value
		*/
    if(imm.test(19))
    {
        neg = true;
        imm = ~imm;
        imm >>= 1;
        imm = std::bitset<20>(imm.to_ulong()+1);
    }
    else
        imm >>= 1;
  }

  /* convert each binary element to integer and store in decoded struct 
	*/
  for(int i = 0; i < 3; i++)
    decoded.reg[i] = (int)(map[i].to_ulong());

  if(neg)
    decoded.immediate = -(int)(imm.to_ulong());
  else
    decoded.immediate = (int)(imm.to_ulong());

  decoded.funct2 = (int)(f2.to_ulong());
  decoded.funct3 = (int)(f3.to_ulong());
  decoded.funct5 = (int)(f5.to_ulong());
}

DecodedInstruction
InstructionDecoder::getDecodedInstruction(void) const
{
  return decoded;
}

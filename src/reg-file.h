/*
 * rv64-emu -- Simple 64-bit RISC-V simulator
 * reg-file.h - Register file.
 */

#ifndef __REG_FILE__
#define __REG_FILE__

#include "arch.h"

#include <array>

#include <sstream>

/* For now hard-coded for a single zero-register and
 * (NumRegs - 1) general-purpose registers.
 */
class RegisterFile
{
  public:
    RegisterFile()
    {
      /* Zero initialize all registers 
			*/
      registers.fill(0);
    }

    RegValue readRegister(const RegNumber regnum) const
    {
      checkRegNumber(regnum);

      if (regnum == 0)
        return 0;
      return registers[regnum - 1];
    }

    void writeRegister(const RegNumber regnum,
                       RegValue        value)
    {
      checkRegNumber(regnum);

      if (regnum == 0)
        return;
      registers[regnum - 1] = value;
    }

  private:
    std::array<RegValue, NumRegs - 1> registers;

    void checkRegNumber(const RegNumber regnum) const
    {
      if (regnum >= NumRegs)
        {
          std::stringstream msg;
          msg << "register number " << (int)regnum << " out of range.";
          throw std::out_of_range(msg.str());
        }
    }
};

#endif /* __REG_FILE_H__ */

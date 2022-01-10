/* 
 * rv64-emu -- Simple 64-bit RISC-V simulator
 * processor.h - Processor class tying all components together
 */

#include "processor.h"
#include "inst-decoder.h"
#include "serial.h"

#include "memory.h"

#include <iostream>
#include <iomanip>

#include <bitset>
#include <stdint.h>
#include <inttypes.h>


#include <stdexcept>

#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>

#include <cstdlib>
#include <cstring>

class InstructionFetchFailure : public std::exception
{
  public:
    explicit InstructionFetchFailure(const MemAddress addr)
    {
      std::stringstream ss;
      ss << "Instruction fetch failed at address " << std::hex << addr;
      message = ss.str();
    }

    virtual const char* what() const noexcept override
    {
      return message.c_str();
    }

  private:
    std::string message;
};


Processor::Processor(ELFFile &program, bool debugMode)
  : debugMode(debugMode), nCycles(0), nInstructions(0),
    PC(program.getEntrypoint()), bus(program.createMemories()),
  control(new SysControl(0x270))
{
  bus.addClient(std::shared_ptr<MemoryInterface>(new Serial(0x200)));
  bus.addClient(control);
}

/* This method is used to initialize registers using values
 * passed as command-line argument.
 */
void
Processor::initRegister(RegNumber regnum, RegValue value)
{
  regfile.writeRegister(regnum, value);
}

RegValue
Processor::getRegister(RegNumber regnum) const
{
  return regfile.readRegister(regnum);
}


/* Processor main loop. Each iteration should execute an instruction.
 * One step in executing and instruction takes exactly 1 clock cycle.
 *
 * The return value indicates whether an exception occurred during
 * execution [false] or whether the whole program was completed 
 * succesfully [true].
 *
 * In "testMode" instruction fetch failures are not fatal. This is because
 * a clean shutdown of the program requires the store instruction to be
 * implemented, so that the system controller can be informed. In unit tests,
 * we want to test as little instructions as possible and thus allow test
 * programs without store instruction to run without error.
 */
bool
Processor::run(bool testMode)
{
  while (! control->shouldHalt())
    {
      try
        {
          ++nCycles;
          instructionFetch();

          ++nCycles;
          bool jumped = instructionDecode();
          if (jumped)
            continue;

          ++nCycles;
          execute();

          ++nCycles;
          memory();

          ++nCycles;
          writeBack();

          ++nInstructions;
        }
      catch (InstructionFetchFailure &e)
        {
          if (testMode)
            return true;
          /* else */
          std::cerr << "ABNORMAL PROGRAM TERMINATION; PC = "
                    << std::hex << PC << std::dec << std::endl;
          std::cerr << "Reason: " << e.what() << std::endl;
          return false;
        }
      catch (std::exception &e)
        {
          /* Catch exceptions such as IllegalInstruction and InvalidAccess */
          std::cerr << "ABNORMAL PROGRAM TERMINATION; PC = "
                    << std::hex << PC << std::dec << std::endl;
          std::cerr << "Reason: " << e.what() << std::endl;
          return false;
        }
    }

  return true;
}

void
Processor::instructionFetch(void)
{
  try
  {
    instruction = bus.readWord(PC);
    PC += 0x04;
  }
  catch (std::exception &e)
  {
    throw InstructionFetchFailure(PC);
  }
}

/* Decodes the instruction and stores it in the decoded
 * instruction cache.
 */
bool
Processor::instructionDecode(void)
{

  decoder.decodeInstruction(instruction);
  decoded = decoder.getDecodedInstruction();

  if (debugMode)
  {
    /* Dump program counter & decoded instruction in debug mode 
		*/
    auto storeFlags(std::cerr.flags());

    std::bitset<32>bin(instruction);
    std::cerr << "------------------- " << std::dec << nInstructions + 1 << std::hex << " ------------------- \n";
    std::cerr << "pc : 0x" << PC - 4 << "\n"
              << "ins: " << bin << "\n\n";
    std::cerr << decoded;
    std::cerr << "Press Enter to Execute Instruction \n";
    std::cin.ignore();

    std::cerr.setf(storeFlags);
  }

  return false;
}

/* Execute the decoded instruction 
*/
void
Processor::execute(void)
{
  alu.clear();
  alu.execute(decoded,regfile,PC);
}

/* Send memory instruction to the memory controller 
*/
void
Processor::memory(void)
{
   alu.memorycontroller(decoded,regfile,bus);

   if(debugMode)
   {
     std::cerr << std::hex << "alu: 0x" << alu.getResult() << "\n\n";
     std::cerr << "Press Enter to Continue" << std::endl;
     std::cin.ignore();
   }
}

/* Write to return register if specified 
*/
void
Processor::writeBack(void)
{
  if(decoded.reg[0] != 0)
    regfile.writeRegister(decoded.reg[0],alu.getResult());
}

void
Processor::dumpRegisters(void) const
{
  const int NumColumns(2);
  const int valueFieldWidth(18);
  auto storeFlags(std::cerr.flags());

  for (int i = 0; i < NumRegs / NumColumns; ++i)
    {
      std::cerr << "R" << std::setw(2) << std::setfill('0') << i << " "
                << std::setw(valueFieldWidth)
                << std::hex << std::showbase
                << regfile.readRegister(i)
                << "\t";
      std::cerr.setf(storeFlags);
      std::cerr << "R" << std::setw(2) << (i + NumRegs/NumColumns) << " "
                << std::setw(valueFieldWidth)
                << std::hex << std::showbase
                << regfile.readRegister(i + NumRegs/NumColumns)
                << std::endl;
      std::cerr.setf(storeFlags);
    }
}

void
Processor::dumpStatistics(void) const
{
  std::cerr << nCycles << " clock cycles, "
            << nInstructions << " instructions executed." << std::endl
            << "CPI: " << ((float)nCycles / nInstructions) << std::endl;
}

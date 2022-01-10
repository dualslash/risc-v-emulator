/*
 * rv64-emu -- Simple 64-bit RISC-V simulator
 * main.cc - Command line parsing, program start.
 */

#include "arch.h"

#include <iostream>
#include <vector>
#include <regex>

#include <getopt.h>
#include <cstdlib>

#include "elf-file.h"
#include "config-file.h"
#include "processor.h"


enum ExitCodes : int
{
  Success = 0,
  AbnormalTermination = 1,
  HelpDisplayed = 2,
  InitializationError = 3
};

/* Class to parse and store a register initializer pair consisting of
 * a register number and the value to initialize that register with.
 */
class RegisterInit
{
  public:
    RegisterInit(RegNumber number, RegValue value)
      : number(number), value(value)
    { }

    RegisterInit(const std::string &initstr)
    {
      std::regex init_regex("r([0-9]{1,2})=([0-9]+)");
      std::smatch match;

      if (std::regex_match(initstr, match, init_regex))
        {
          int regnum = atoi(match[1].str().c_str());

          /* Perform a first verification, a real check whether the register
           * number is valid is performed when initializing the register file.
           */
          if (regnum < 0 || regnum >= MaxRegs)
            {
              std::stringstream str;

              str << "Error: register regnum out of range: " << regnum;
              throw std::out_of_range(str.str());
            }

          number = regnum;
          value = atoi(match[2].str().c_str());
        }
    }

    RegNumber number;
    RegValue value;
};

/* A test file contains "pre" and "post" sections, containing the values
 * the registers should be initialized with and the values the registers
 * should have at program end respectively. The filename of a test file
 * should end with ".conf". The corresponding executable has the same
 * filename, but with extension ".bin".
 */
class TestFile : public ConfigFile
{
  public:
    TestFile(const std::string &filename)
      : ConfigFile(filename), filename(filename)
    {
      validate();
    }

    std::vector<RegisterInit> getPreRegisters(void) const
    {
      return getRegisters("pre");
    }

    std::vector<RegisterInit> getPostRegisters(void) const
    {
      return getRegisters("post");
    }

    /* Return the name of the executable to run given the name of the
     * test file.
     */
    std::string getExecutable(void) const
    {
      std::string ret(filename);
      ret.replace(filename.length() - 5, 5, ".bin");
      return ret;
    }

  private:
    std::string filename;

    void validate(void) const
    {
      validateSection("pre");
      validateSection("post");
    }

    /* Verify that all properties in the given section consist of an
     * register name (rXX) and integer value.
     */
    void validateSection(const std::string &sectionName) const
    {
      if (!hasSection(sectionName))
        throw std::runtime_error("Section '" + sectionName + "' missing.");

      std::regex regnameRegex("r([0-9]{1,2})");
      std::smatch match;

      for (auto &kv : getProperties(sectionName))
        {
          if (std::regex_match(kv.first, match, regnameRegex))
            throw std::runtime_error("Invalid register name " + kv.first);
        }
    }

    /* Note that this method can only be called after the ConfigFile
     * has been successfully validated.
     */
    std::vector<RegisterInit> getRegisters(const std::string &sectionName) const
    {
      std::vector<RegisterInit> result;

      /* Translate all properties into register init pairs. Note that
       * kv.first stores the register *name*, so we need to skip the R.
       * validateSection already validated that the register name is in
       * the right form.
       */
      for (auto &kv : getProperties(sectionName))
        result.push_back(RegisterInit(atoi(kv.first.c_str() + 1),
                                      atoi(kv.second.c_str())));

      return result;
    }
};

static void
validateRegisters(const Processor &p,
                  const std::vector<RegisterInit> &expectedValues)
{
  if (!expectedValues.empty())
    {
      for (auto &reginit : expectedValues)
        {
          if (reginit.value != p.getRegister(reginit.number))
            {
              std::cerr << "Register R" << (int)reginit.number
                  << " expected " << reginit.value
                  << " (" << std::hex << std::showbase
                  << reginit.value
                  << std::dec << std::noshowbase << ")"
                  << " got " << p.getRegister(reginit.number)
                  << " (" << std::hex << std::showbase
                  << p.getRegister(reginit.number)
                  << std::dec << std::noshowbase << ")"
                  << std::endl;
            }
        }
    }
}


/* Start the emulator by either executing a test or running a regular
 * program.
 */
static int
launcher(const char *testFilename,
         const char *execFilename,
         bool debugMode,
         std::vector<RegisterInit> initializers)
{
  try
    {
      std::string programFilename;
      std::vector<RegisterInit> postRegisters;

      if (testFilename)
        {
          std::string testConfig(testFilename);

          if (testConfig.length() < 6 or
              testConfig.substr(testConfig.length() - 5) != std::string(".conf"))
            {
              std::cerr << "Error: test filename must end with .conf"
                        << std::endl;
              return ExitCodes::InitializationError;
            }

          try
            {
              TestFile testfile(testConfig);
              initializers = testfile.getPreRegisters();
              postRegisters = testfile.getPostRegisters();
              programFilename = testfile.getExecutable();
            }
          catch (std::exception &e)
            {
              std::cerr << "Error loading test config: " << e.what() << std::endl;
              return ExitCodes::InitializationError;
            }
        }
      else
        programFilename = std::string(execFilename);

      /* Read the ELF file and start the emulator */
      ELFFile program(programFilename);
      Processor p(program, debugMode);

      for (auto &initializer : initializers)
        p.initRegister(initializer.number, initializer.value);

      p.run(testFilename != nullptr);

      /* Dump registers and statistics when not running a unit test. */
      if (!testFilename)
        {
          p.dumpRegisters();
          p.dumpStatistics();
        }

      validateRegisters(p, postRegisters);
    }
  catch (std::runtime_error &e)
    {
      std::cerr << "Couldn't load program: " << e.what()
                << std::endl;
      return ExitCodes::InitializationError;
    }
  catch (std::out_of_range &e)
    {
      std::cerr << "Out of range parameter: " << e.what()
                << std::endl;
      return ExitCodes::InitializationError;
    }

  return ExitCodes::Success;
}

static void
showHelp(const char *progName)
{
  std::cerr << progName << " [-d] [-r reginit] <programFilename>" << std::endl;
  std::cerr << std::endl << "    or" << std::endl << std::endl;
  std::cerr << progName << " [-d] -t testfile" << std::endl;
  std::cerr <<
R"HERE(
    Where 'reginit' is a register initializer in the form
    rX=Y with X a register number and Y the initializer value.
    'testfile' is a unit test configuration file.

    -d enables debug mode in which every decoded instruction is printed
    to the terminal.
)HERE";
}


int
main(int argc, char **argv)
{
  char c;
  bool debugMode = false;
  std::vector<RegisterInit> initializers;
  const char *testFilename = nullptr;

  /* Command line option processing */
  const char *progName = argv[0];

  while ((c = getopt(argc, argv, "dr:t:h")) != -1)
    {
      switch (c)
        {
          case 'd':
            debugMode = true;
            break;

          case 'r':
            if (testFilename != nullptr)
              {
                std::cerr << "Error: Cannot set unit test and individual "
                          << "registers at the same time." << std::endl;
                return ExitCodes::InitializationError;
              }

            try
              {
                RegisterInit init((std::string(optarg)));
                initializers.push_back(init);
              }
            catch (std::exception &e)
              {
                std::cerr << "Error: Malformed register initialization specifier "
                          << optarg << std::endl;
                return ExitCodes::InitializationError;
              }
            break;

          case 't':
            if (testFilename != nullptr)
              {
                std::cerr << "Error: Cannot specify testfile more than once."
                          << std::endl;
                return ExitCodes::InitializationError;
              }

            testFilename = optarg;
            break;

          case 'h':
          default:
            showHelp(progName);
            return ExitCodes::HelpDisplayed;
            break;
        }
    }

  argc -= optind;
  argv += optind;

  if (!testFilename and argc < 1)
    {
      std::cerr << "Error: No executable specified." << std::endl << std::endl;
      showHelp(progName);
      return ExitCodes::InitializationError;
    }

  return launcher(testFilename, argv[0], debugMode, initializers);
}

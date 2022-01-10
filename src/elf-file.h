/* 
 * rv64-emu -- Simple 64-bit RISC-V simulator
 * elf-file.h - ELF file parsing class
 *
 * Based on the original S.M.A.C.K Implementation
 *
 * S.M.A.C.K - An operating system kernel
 * Copyright (C) 2010,2011 Mattias Holm and Kristian Rietveld
 */

#ifndef __ELF_FILE_H__
#define __ELF_FILE_H__

#include "memory-interface.h"

#include <vector>
#include <memory>
#include <string>

/* The ELFFile class loads a program from an ELF file by creating memories
 * for every section that needs to be loaded. During construction of
 * the Processor class, these memories are added to the memory bus
 * of the system.
 */
class ELFFile
{
  public:
    ELFFile(const std::string &filename);
    ~ELFFile();

    void load(const std::string &filename);
    void unload(void);

    std::vector<std::shared_ptr<MemoryInterface>> createMemories(void);
    uint64_t getEntrypoint(void) const;

  private:
    int fd;
    size_t programSize;
    void *mapAddr;

    bool isBad;

    bool isELF(void) const;
    bool isTarget(const uint8_t elf_class,
                  const uint8_t endianness,
                  const uint8_t machine) const;
};

#endif /* __ELF_FILE_H__ */

/*
 * rv64-emu -- Simple 64-bit RISC-V simulator
 * elf-file.cc - ELF file parsing class
 *
 * Based on the original S.M.A.C.K Implementation
 *
 * S.M.A.C.K - An operating system kernel
 * Copyright (C) 2010,2011 Mattias Holm and Kristian Rietveld
 */

#include "elf-file.h"
#include "memory.h"

#include "elf.h"

#include <stdexcept>

#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>

#include <cstdlib>
#include <cstring>

#include <iostream>

ELFFile::ELFFile(const std::string &filename)
  : isBad(true)
{
  load(filename);
}

ELFFile::~ELFFile()
{
  if (! isBad)
    unload();
}

void
ELFFile::load(const std::string &filename)
{
  fd = open(filename.c_str(), O_RDONLY);
  if (fd < 0)
    throw std::runtime_error("Could not open file.");

  struct stat statbuf;
  if (fstat(fd, &statbuf) < 0)
    {
      close(fd);
      throw std::runtime_error("Could not retrieve file attributes.");
    }

  if (statbuf.st_mode & S_IFDIR)
    {
      close(fd);
      throw std::runtime_error("Filename is a directory.");
    }

  programSize = statbuf.st_size;
  mapAddr = mmap(NULL, programSize, PROT_READ, MAP_PRIVATE, fd, 0);
  if (mapAddr == MAP_FAILED)
    {
      close(fd);
      throw std::runtime_error("Failed to setup memory map.");
    }

  /* For now, we hardcode the RISCV target */
  if (! isELF() || ! isTarget(ELFCLASS64, ELFDATA2LSB, EM_RISCV))
    {
      unload();
      throw std::runtime_error("File is not a RISC-V ELF file.");
    }

  isBad = false;
}

void
ELFFile::unload(void)
{
  munmap(mapAddr, programSize);
  close(fd);

  mapAddr = NULL;
  fd = 0;
}

bool
ELFFile::isELF(void) const
{
  const Elf64_Ehdr *elf = (Elf64_Ehdr *)mapAddr;

  if (!(elf->e_ident[EI_MAG0] == 0x7f
        && elf->e_ident[EI_MAG1] == 'E'
        && elf->e_ident[EI_MAG2] == 'L'
        && elf->e_ident[EI_MAG3] == 'F'))
    return false;

  if (elf->e_ident[EI_VERSION] != EV_CURRENT)
    return false;

  return true;
}

bool
ELFFile::isTarget(const uint8_t elf_class,
                  const uint8_t endianness,
                  const uint8_t machine) const
{
  const Elf64_Ehdr *elf = (Elf64_Ehdr *)mapAddr;

  if (elf->e_ident[EI_CLASS] != elf_class)
    return false;

  if (elf->e_ident[EI_DATA] != endianness)
    return false;

  if (elf->e_type == ET_EXEC
      && elf->e_machine != machine
      && elf->e_version != EV_CURRENT)
    return false;

  if (elf->e_phoff == 0)
    // Not a proper elf executable (must have program header)
    return false;

  return true;
}

std::vector<std::shared_ptr<MemoryInterface>>
ELFFile::createMemories(void)
{
  std::vector<std::shared_ptr<MemoryInterface>> memories;

  const Elf64_Ehdr *elf = (Elf64_Ehdr *)mapAddr;
  const Elf64_Shdr *sheader =
      (Elf64_Shdr *)((uintptr_t)elf + (uintptr_t)elf->e_shoff);

  for (int i = 0; i < elf->e_shnum; ++i)
    {
      if ((sheader[i].sh_flags & SHF_ALLOC) == SHF_ALLOC)
        {
          /* Create the memory area using some low-level C calls, because
           * we must get the alignment right. Note that posix_memalign
           * demands the alignment to at least be of sizeof(void *).
           */
          uint8_t *segment = NULL;

          uint8_t align = sheader[i].sh_addralign;
          if (align < sizeof(void *))
            align = sizeof(void *);

          posix_memalign((void **)&segment, align, sheader[i].sh_size);

          /* Transfer section data or clear the section. */
          if (sheader[i].sh_type == SHT_PROGBITS)
            {
              void *segdata = (void *)(((uintptr_t )elf) + sheader[i].sh_offset);
              memcpy(segment, segdata, sheader[i].sh_size);
            }
          else
            memset(segment, 0, sheader[i].sh_size);

          /* FIXME: determine correct name for segment. */
          std::string name("data");
          if ((sheader[i].sh_flags & SHF_EXECINSTR) == SHF_EXECINSTR)
            name = "text";

          std::shared_ptr<Memory> memory(new Memory(name, segment,
                                                    sheader[i].sh_addr,
                                                    sheader[i].sh_size));
          if ((sheader[i].sh_flags & SHF_WRITE) == SHF_WRITE)
            memory->setMayWrite(true);

          memories.push_back(std::move(memory));
        }
    }

  return memories;
}

uint64_t
ELFFile::getEntrypoint(void) const
{
  const Elf64_Ehdr *elf = (Elf64_Ehdr *)mapAddr;
  return elf->e_entry;
}

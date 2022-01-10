/* 
 * rv64-emu -- Simple 64-bit RISC-V simulator
 * elf.h - Definitions for reading ELF files
 *
 * Based on the original S.M.A.C.K Implementation
 *
 * S.M.A.C.K - An operating system kernel
 * Copyright (C) 2010,2011 Mattias Holm and Kristian Rietveld
 */

#ifndef __ELF_H__
#define __ELF_H__

#include <cstdint>

typedef uint32_t Elf32_Addr;
typedef uint16_t Elf32_Half;
typedef uint32_t Elf32_Off;
typedef int32_t  Elf32_Sword;
typedef uint32_t Elf32_Word;

typedef uint64_t Elf64_Addr;
typedef uint16_t Elf64_Half;
typedef int16_t  Elf64_SHalf;
typedef uint64_t Elf64_Off;
typedef int32_t  Elf64_Sword;
typedef uint32_t Elf64_Word;
typedef uint64_t Elf64_Xword;
typedef int64_t  Elf64_Sxword;

#define EI_MAG0 0       //File identification
#define EI_MAG1 1       //File identification
#define EI_MAG2 2       //File identification
#define EI_MAG3 3       //File identification
#define EI_CLASS        4       //File class
#define EI_DATA 5       //Data encoding
#define EI_VERSION      6       //File version
#define EI_OSABI        7       //Operating system/ABI identification
#define EI_ABIVERSION   8       //ABI version
#define EI_PAD  9       //Start of padding bytes
#define EI_NIDENT 16 // Size of e_ident[]

#define ELFCLASSNONE    0       //Invalid class
#define ELFCLASS32      1       //32-bit objects
#define ELFCLASS64      2       //64-bit objects

#define ELFDATANONE     0       // Invalid data encoding
#define ELFDATA2LSB     1       // Little endian
#define ELFDATA2MSB     2       // Big endian


#define ET_NONE   0       // No file type
#define ET_REL    1       // Relocatable file
#define ET_EXEC   2       // Executable file
#define ET_DYN    3       // Shared object file
#define ET_CORE   4       // Core file
#define ET_LOOS   0xfe00  // Operating system-specific
#define ET_HIOS   0xfeff  // Operating system-specific
#define ET_LOPROC 0xff00  // Processor-specific
#define ET_HIPROC 0xffff  // Processor-specific

#define EM_NONE 0 // No machine
#define EM_M32 1 // AT&T WE 32100
#define EM_SPARC 2 // SPARC
#define EM_386 3 // Intel 80386
#define EM_68K 4 // Motorola 68000
#define EM_88K 5 // Motorola 88000
#define EM_860 7 // Intel 80860
#define EM_MIPS 8 //MIPS RS3000 Big-Endian
#define EM_MIPS_RS4_BE 10 // MIPS RS4000 Big-Endian

#define EM_PARISC       15      // Hewlett-Packard PA-RISC

#define EM_VPP500       17      // Fujitsu VPP500
#define EM_SPARC32PLUS  18      // Enhanced instruction set SPARC
#define EM_960  19      // Intel 80960
#define EM_PPC  20      // PowerPC
#define EM_PPC64        21      // 64-bit PowerPC
#define EM_S390 22      // IBM System/390 Processor
#define EM_SPU  23      // IBM SPU/SPC

#define EM_V800 36      // NEC V800
#define EM_FR20 37      // Fujitsu FR20
#define EM_RH32 38      // TRW RH-32
#define EM_RCE  39      // Motorola RCE
#define EM_ARM  40      // Advanced RISC Machines ARM
#define EM_ALPHA        41      // Digital Alpha
#define EM_SH   42      // Hitachi SH
#define EM_SPARCV9      43      // SPARC Version 9
#define EM_TRICORE      44      // Siemens TriCore embedded processor
#define EM_ARC  45      // Argonaut RISC Core, Argonaut Technologies Inc.
#define EM_H8_300       46      // Hitachi H8/300
#define EM_H8_300H      47      // Hitachi H8/300H
#define EM_H8S  48      // Hitachi H8S
#define EM_H8_500       49      // Hitachi H8/500
#define EM_IA_64        50      // Intel IA-64 processor architecture
#define EM_MIPS_X       51      // Stanford MIPS-X
#define EM_COLDFIRE     52      // Motorola ColdFire
#define EM_68HC12       53      // Motorola M68HC12
#define EM_MMA  54      // Fujitsu MMA Multimedia Accelerator
#define EM_PCP  55      // Siemens PCP
#define EM_NCPU 56      // Sony nCPU embedded RISC processor
#define EM_NDR1 57      // Denso NDR1 microprocessor
#define EM_STARCORE     58      // Motorola Star*Core processor
#define EM_ME16 59      // Toyota ME16 processor
#define EM_ST100        60      // STMicroelectronics ST100 processor
#define EM_TINYJ        61      // Advanced Logic Corp. TinyJ embedded processor family
#define EM_X86_64       62      // AMD x86-64 architecture
#define EM_PDSP 63      // Sony DSP Processor
#define EM_PDP10        64      // Digital Equipment Corp. PDP-10
#define EM_PDP11        65      // Digital Equipment Corp. PDP-11
#define EM_FX66 66      // Siemens FX66 microcontroller
#define EM_ST9PLUS      67      // STMicroelectronics ST9+ 8/16 bit microcontroller
#define EM_ST7  68      // STMicroelectronics ST7 8-bit microcontroller
#define EM_68HC16       69      // Motorola MC68HC16 Microcontroller
#define EM_68HC11       70      // Motorola MC68HC11 Microcontroller
#define EM_68HC08       71      // Motorola MC68HC08 Microcontroller
#define EM_68HC05       72      // Motorola MC68HC05 Microcontroller
#define EM_SVX  73      // Silicon Graphics SVx
#define EM_ST19 74      // STMicroelectronics ST19 8-bit microcontroller
#define EM_VAX  75      // Digital VAX
#define EM_CRIS 76      // Axis Communications 32-bit embedded processor
#define EM_JAVELIN      77      // Infineon Technologies 32-bit embedded processor
#define EM_FIREPATH     78      // Element 14 64-bit DSP Processor
#define EM_ZSP  79      // LSI Logic 16-bit DSP Processor
#define EM_MMIX 80      // Donald Knuth's educational 64-bit processor
#define EM_HUANY        81      // Harvard University machine-independent object files
#define EM_PRISM        82      // SiTera Prism
#define EM_AVR  83      // Atmel AVR 8-bit microcontroller
#define EM_FR30 84      // Fujitsu FR30
#define EM_D10V 85      // Mitsubishi D10V
#define EM_D30V 86      // Mitsubishi D30V
#define EM_V850 87      // NEC v850
#define EM_M32R 88      // Mitsubishi M32R
#define EM_MN10300      89      // Matsushita MN10300
#define EM_MN10200      90      // Matsushita MN10200
#define EM_PJ   91      // picoJava
#define EM_OPENRISC     92      // OpenRISC 32-bit embedded processor
#define EM_ARC_COMPACT  93      // ARC International ARCompact processor (old spelling/synonym: EM_ARC_A5)
#define EM_XTENSA       94      // Tensilica Xtensa Architecture
#define EM_VIDEOCORE    95      // Alphamosaic VideoCore processor
#define EM_TMM_GPP      96      // Thompson Multimedia General Purpose Processor
#define EM_NS32K        97      // National Semiconductor 32000 series
#define EM_TPC  98      // Tenor Network TPC processor
#define EM_SNP1K        99      // Trebia SNP 1000 processor
#define EM_ST200        100     // STMicroelectronics (www.st.com) ST200 microcontroller
#define EM_IP2K 101     // Ubicom IP2xxx microcontroller family
#define EM_MAX  102     // MAX Processor
#define EM_CR   103     // National Semiconductor CompactRISC microprocessor
#define EM_F2MC16       104     // Fujitsu F2MC16
#define EM_MSP430       105     // Texas Instruments embedded microcontroller msp430
#define EM_BLACKFIN     106     // Analog Devices Blackfin (DSP) processor
#define EM_SE_C33       107     // S1C33 Family of Seiko Epson processors
#define EM_SEP  108     // Sharp embedded microprocessor
#define EM_ARCA 109     // Arca RISC Microprocessor
#define EM_UNICORE      110     // Microprocessor series from PKU-Unity Ltd. and MPRC of Peking University
#define EM_EXCESS       111     // eXcess: 16/32/64-bit configurable embedded CPU
#define EM_DXP  112     // Icera Semiconductor Inc. Deep Execution Processor
#define EM_ALTERA_NIOS2 113     // Altera Nios II soft-core processor
#define EM_CRX  114     // National Semiconductor CompactRISC CRX microprocessor
#define EM_XGATE        115     // Motorola XGATE embedded processor
#define EM_C166 116     // Infineon C16x/XC16x processor
#define EM_M16C 117     // Renesas M16C series microprocessors
#define EM_DSPIC30F     118     // Microchip Technology dsPIC30F Digital Signal Controller
#define EM_CE   119     // Freescale Communication Engine RISC core
#define EM_M32C 120     // Renesas M32C series microprocessors

#define EM_TSK3000      131     // Altium TSK3000 core
#define EM_RS08 132     // Freescale RS08 embedded processor

#define EM_ECOG2        134     // Cyan Technology eCOG2 microprocessor
#define EM_SCORE7       135     // Sunplus S+core7 RISC processor
#define EM_DSP24        136     // New Japan Radio (NJR) 24-bit DSP Processor
#define EM_VIDEOCORE3   137     // Broadcom VideoCore III processor
#define EM_LATTICEMICO32        138     // RISC processor for Lattice FPGA architecture
#define EM_SE_C17       139     // Seiko Epson C17 family
#define EM_TI_C6000     140     // The Texas Instruments TMS320C6000 DSP family
#define EM_TI_C2000     141     // The Texas Instruments TMS320C2000 DSP family
#define EM_TI_C5500     142     // The Texas Instruments TMS320C55x DSP family

#define EM_MMDSP_PLUS   160     // STMicroelectronics 64bit VLIW Data Signal Processor
#define EM_CYPRESS_M8C  161     // Cypress M8C microprocessor
#define EM_R32C 162     // Renesas R32C series microprocessors
#define EM_TRIMEDIA     163     // NXP Semiconductors TriMedia architecture family
#define EM_QDSP6        164     // QUALCOMM DSP6 Processor
#define EM_8051 165     // Intel 8051 and variants
#define EM_STXP7X       166     // STMicroelectronics STxP7x family of configurable and extensible RISC processors
#define EM_NDS32        167     // Andes Technology compact code size embedded RISC processor family
#define EM_ECOG1        168     // Cyan Technology eCOG1X family
#define EM_ECOG1X       168     // Cyan Technology eCOG1X family
#define EM_MAXQ30       169     // Dallas Semiconductor MAXQ30 Core Micro-controllers
#define EM_XIMO16       170//   New Japan Radio (NJR) 16-bit DSP Processor
#define EM_MANIK        171//   M2000 Reconfigurable RISC Microprocessor
#define EM_CRAYNV2      172     // Cray Inc. NV2 vector architecture
#define EM_RX   173     // Renesas RX family
#define EM_METAG        174     // Imagination Technologies META processor architecture
#define EM_MCST_ELBRUS  175     // MCST Elbrus general purpose hardware architecture
#define EM_ECOG16       176     // Cyan Technology eCOG16 family
#define EM_CR16 177     // National Semiconductor CompactRISC CR16 16-bit microprocessor
#define EM_ETPU 178     // Freescale Extended Time Processing Unit
#define EM_SLE9X        179     // Infineon Technologies SLE9X core

#define EM_AVR32        185     // Atmel Corporation 32-bit microprocessor family
#define EM_STM8 186     // STMicroeletronics STM8 8-bit microcontroller
#define EM_TILE64       187     // Tilera TILE64 multicore architecture family
#define EM_TILEPRO      188     // Tilera TILEPro multicore architecture family
#define EM_MICROBLAZE   189     // Xilinx MicroBlaze 32-bit RISC soft processor core
#define EM_CUDA         190     // NVIDIA CUDA architecture
#define EM_TILEGX       191     // Tilera TILE-Gx multicore architecture family
#define EM_CLOUDSHIELD  192     // CloudShield architecture family

#define EM_RISCV        243

#define EV_NONE  0 // Invalid version
#define EV_CURRENT 1 // Current version

#define ELFOSABI_NONE   0//     No extensions or unspecified
#define ELFOSABI_HPUX   1//     Hewlett-Packard HP-UX
#define ELFOSABI_NETBSD 2//     NetBSD
#define ELFOSABI_LINUX  3       // Linux
#define ELFOSABI_SOLARIS        6       // Sun Solaris
#define ELFOSABI_AIX    7       // AIX
#define ELFOSABI_IRIX   8       // IRIX
#define ELFOSABI_FREEBSD        9       // FreeBSD
#define ELFOSABI_TRU64  10      // Compaq TRU64 UNIX
#define ELFOSABI_MODESTO        11      // Novell Modesto
#define ELFOSABI_OPENBSD        12      // Open BSD
#define ELFOSABI_OPENVMS        13      // Open VMS
#define ELFOSABI_NSK    14      // Hewlett-Packard Non-Stop Kernel
#define ELFOSABI_AROS   15      // Amiga Research OS
#define ELFOSABI_FENIXOS        16      // The FenixOS highly scalable multi-core OS


#define SHN_UNDEF     0
#define SHN_LORESERVE 0xff00
#define SHN_LOPROC    0xff00
#define SHN_HIPROC    0xff1f
#define SHN_ABS       0xfff1
#define SHN_COMMON    0xfff2
#define SHN_HIRESERVE 0xffff

#define SHT_NULL        0
#define SHT_PROGBITS    1
#define SHT_SYMTAB      2
#define SHT_STRTAB      3
#define SHT_RELA        4
#define SHT_HASH        5
#define SHT_DYNAMIC     6
#define SHT_NOTE        7
#define SHT_NOBITS      8
#define SHT_REL 9
#define SHT_SHLIB       10
#define SHT_DYNSYM      11
#define SHT_INIT_ARRAY  14
#define SHT_FINI_ARRAY  15
#define SHT_PREINIT_ARRAY       16
#define SHT_GROUP       17
#define SHT_SYMTAB_SHNDX        18
#define SHT_LOOS        0x60000000
#define SHT_HIOS        0x6fffffff
#define SHT_LOPROC      0x70000000
#define SHT_HIPROC      0x7fffffff
#define SHT_LOUSER      0x80000000
#define SHT_HIUSER      0xffffffff

#define SHF_WRITE       0x1
#define SHF_ALLOC       0x2
#define SHF_EXECINSTR   0x4
#define SHF_MERGE       0x10
#define SHF_STRINGS     0x20
#define SHF_INFO_LINK   0x40
#define SHF_LINK_ORDER  0x80
#define SHF_OS_NONCONFORMING    0x100
#define SHF_GROUP       0x200
#define SHF_TLS 0x400
#define SHF_MASKOS      0x0ff00000
#define SHF_MASKPROC    0xf0000000

#define GRP_COMDAT      0x1
#define GRP_MASKOS      0x0ff00000
#define GRP_MASKPROC    0xf0000000

#define STB_LOCAL  0
#define STB_GLOBAL 1
#define STB_WEAK   2
#define STB_LOPROC 13
#define STB_HIPROC 15

#define STT_NOTYPE  0
#define STT_OBJECT  1
#define STT_FUNC    2
#define STT_SECTION 3
#define STT_FILE    4
#define STT_LOPROC  13
#define STT_HIPROC  15


// Elf header
typedef struct {
  unsigned char e_ident[EI_NIDENT];
  Elf32_Half    e_type;
  Elf32_Half    e_machine;
  Elf32_Word    e_version;
  Elf32_Addr    e_entry;     // Entry address
  Elf32_Off     e_phoff;     // Program header offset
  Elf32_Off     e_shoff;     // Section header offset
  Elf32_Word    e_flags;     // Processor flags
  Elf32_Half    e_ehsize;    // Elf header size in bytes
  Elf32_Half    e_phentsize; // Program header entry size
  Elf32_Half    e_phnum;     // Program header length
  Elf32_Half    e_shentsize; // Section header size
  Elf32_Half    e_shnum;     // Section header table length
  Elf32_Half    e_shstrndx;  // Section header index of string table
} Elf32_Ehdr;

typedef struct {
  unsigned char e_ident[EI_NIDENT];
  Elf64_Half    e_type;
  Elf64_Half    e_machine;
  Elf64_Word    e_version;
  Elf64_Addr    e_entry;
  Elf64_Off     e_phoff;
  Elf64_Off     e_shoff;
  Elf64_Word    e_flags;
  Elf64_Half    e_ehsize;
  Elf64_Half    e_phentsize;
  Elf64_Half    e_phnum;
  Elf64_Half    e_shentsize;
  Elf64_Half    e_shnum;
  Elf64_Half    e_shstrndx;
} Elf64_Ehdr;

// Section header
typedef struct {
  Elf32_Word    sh_name;      // Name e.g. .bss (index in string table)
  Elf32_Word    sh_type;      // Section type
  Elf32_Word    sh_flags;     // Section flags
  Elf32_Addr    sh_addr;      // Load address
  Elf32_Off     sh_offset;    // Offset
  Elf32_Word    sh_size;      // Section size
  Elf32_Word    sh_link;      // Link table index
  Elf32_Word    sh_info;      // Extra information
  Elf32_Word    sh_addralign; // Address align restrictions
  Elf32_Word    sh_entsize;   // Entry size (if section contains table)
} Elf32_Shdr;

typedef struct {
  Elf64_Word    sh_name;
  Elf64_Word    sh_type;
  Elf64_Xword   sh_flags;
  Elf64_Addr    sh_addr;
  Elf64_Off     sh_offset;
  Elf64_Xword   sh_size;
  Elf64_Word    sh_link;
  Elf64_Word    sh_info;
  Elf64_Xword   sh_addralign;
  Elf64_Xword   sh_entsize;
} Elf64_Shdr;

typedef struct {
  Elf32_Word    st_name;  // Symbol name index in string table
  Elf32_Addr    st_value; // Value of symbol
  Elf32_Word    st_size;  // Data object size
  unsigned char st_info;  // Symbol type and binding attributes
  unsigned char st_other; // Other (= 0)
  Elf32_Half    st_shndx; // Section index symbol is relative to
} Elf32_Sym;

typedef struct {
  Elf64_Word    st_name;
  unsigned char st_info;
  unsigned char st_other;
  Elf64_Half    st_shndx;
  Elf64_Addr    st_value;
  Elf64_Xword   st_size;
} Elf64_Sym;


#define PT_NULL    0
#define PT_LOAD    1
#define PT_DYNAMIC 2
#define PT_INTERP  3
#define PT_NOTE    4
#define PT_SHLIB   5
#define PT_PHDR    6
#define PT_TLS     7
#define PT_LOOS    0x60000000
#define PT_HIOS    0x6fffffff
#define PT_LOPROC  0x70000000
#define PT_HIPROC  0x7fffffff

#define PF_X 0x1
#define PF_W 0x2
#define PF_R 0x4
#define PF_MASKPROC 0xf0000000

typedef struct {
  Elf32_Word  p_type;   // Kind of segment
  Elf32_Off   p_offset; // Offset from beginning of file to segment start
  Elf32_Addr  p_vaddr;  // Virtual address of segment
  Elf32_Addr  p_paddr;  // Physical address of segment (when applicable)
  Elf32_Word  p_filesz; // Number of bytes in file image
  Elf32_Word  p_memsz;  // Number of bytes in memory image
  Elf32_Word  p_flags;  // Flags
  Elf32_Word  p_align;  // Alignment
} Elf32_Phdr;

typedef struct {
  Elf64_Word  p_type;
  Elf64_Word  p_flags;
  Elf64_Off   p_offset;
  Elf64_Addr  p_vaddr;
  Elf64_Addr  p_paddr;
  Elf64_Xword p_filesz;
  Elf64_Xword p_memsz;
  Elf64_Xword p_align;
} Elf64_Phdr;

#endif /* __ELF_H__ */

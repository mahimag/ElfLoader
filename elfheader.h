#ifndef ELFHEADER_H
#define ELFHEADER_H

#include <elf.h>

// Format of an ELF executable file
#ifdef __32BIT__

// Define the elf header as a 32 bit header
typedef Elf32_Ehdr Elfhdr;
typedef Elf32_Phdr Phdr;

#else

// Define the elf header as a 64 bit header
typedef Elf64_Ehdr Elfhdr;
typedef Elf64_Phdr Phdr;

#endif  // __32BIT__

#endif // ELFHEADER_H

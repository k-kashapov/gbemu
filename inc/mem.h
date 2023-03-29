#ifndef MEM_H
#define MEM_H

#include "general.h"
#include "emu.h"
#include "clock.h"

word   MEM8  (void *RAM, dword offs);
word  *MEMp8 (void *RAM, dword offs);
dword  MEM16 (void *RAM, dword offs);
dword *MEMp16(void *RAM, dword offs);

void dump_mem(void *RAM, size_t len);

#endif // MEM_H

#ifndef MEM_H
#define MEM_H
#include "general.h"
#include "emu.h"

word *memPtr(void *RAM, dword offs);

void dump_mem(void *RAM, size_t len);

#endif // MEM_H

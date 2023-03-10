#ifndef MEM_H
#define MEM_H
#include "general.h"
#include "emu.h"

__always_inline void *MEM(void *RAM, dword offs)  { return  (word *)RAM + offs; }

void dump_mem(void *RAM, size_t len);

#endif // MEM_H

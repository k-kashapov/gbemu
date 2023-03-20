#ifndef MEM_H
#define MEM_H

#include "general.h"
#include "emu.h"
#include "clock.h"

inline word  MEM8 (void *RAM, dword offs)  { wait(4); return ((word *)RAM)[offs]; }
inline word *MEMp8(void *RAM, dword offs)  { wait(4); return ((word *)RAM) + offs; }

inline dword  MEM16 (void *RAM, dword offs)  { wait(4); return *(dword *)((word *)RAM + offs); }
inline dword *MEMp16(void *RAM, dword offs)  { wait(4); return  (dword *)((word *)RAM + offs); }

void dump_mem(void *RAM, size_t len);

#endif // MEM_H

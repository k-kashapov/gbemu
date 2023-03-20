#ifndef JUMPS_H
#define JUMPS_H

#include "general.h"
#include "cpu.h"
#include "mem.h"

__always_inline void JP(struct CPU *cpu, dword *src) {
    DBG_PRINT("JUMP 0x%x -> 0x%x\n", cpu->PC, *src);
    cpu->PC = *src;
}

#endif // JUMPS_H

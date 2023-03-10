#ifndef LOADS_H
#define LOADS_H

#include "general.h"
#include "cpu.h"
#include "mem.h"
#include <sys/cdefs.h>

// >-------------------<
//      8-bit LOADS
// >-------------------<
inline word *imm8(void *RAM, struct CPU *cpu) {
    return ((word *)RAM) + cpu->PC + 1;
}

inline dword *imm16(void *RAM, struct CPU *cpu) {
    return (dword *)((word *)RAM + cpu->PC + 1);
}

inline void LD_8(word *dst, word *src) {
    *dst = *src;
}

__always_inline void LDD_8(void *RAM, struct CPU *cpu, int to_register) {
    if (to_register) {
        // LDD (A, (HL))
        cpu->A = *MEM(RAM, cpu->HL--);
    } else {
        *MEM(RAM, cpu->HL--) = cpu->A;
    }
}

__always_inline void LDI_8(void *RAM, struct CPU *cpu, int to_register) {
    if (to_register) {
        // LDD (A, (HL))
        cpu->A = *MEM(RAM, cpu->HL++);
    } else {
        *MEM(RAM, cpu->HL++) = cpu->A;
    }
}

#endif // LOADS_H

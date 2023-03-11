#ifndef LOADS_H
#define LOADS_H

// LOAD-STORE MOUDLE

#include "general.h"
#include "cpu.h"
#include "mem.h"
#include <sys/cdefs.h>

// >-------------------<
//      8-bit LOADS
// >-------------------<

// Ptr to word at PC + 1
__always_inline word *imm8(void *RAM, struct CPU *cpu) {
    return ((word *)RAM) + cpu->PC + 1;
}

__always_inline void LD_8(word *dst, word *src) {
    *dst = *src;
}

__always_inline void LDD_8(void *RAM, struct CPU *cpu, int to_register) {
    if (to_register) {
        // LDD (A, (HL))
        cpu->A = *(word *)MEM(RAM, cpu->HL--);
    } else {
        *(word *)MEM(RAM, cpu->HL--) = cpu->A;
    }
}

__always_inline void LDI_8(void *RAM, struct CPU *cpu, int to_register) {
    if (to_register) {
        // LDD (A, (HL))
        cpu->A = *(word *)MEM(RAM, cpu->HL++);
    } else {
        *(word *)MEM(RAM, cpu->HL++) = cpu->A;
    }
}

// >--------------------<
//      16-bit LOADS
// >--------------------<

// Ptr to dword at PC + 1
__always_inline dword *imm16(void *RAM, struct CPU *cpu) {
    return (dword *)((word *)RAM + cpu->PC + 1);
}

__always_inline void LD_16(dword *dst, dword *src) {
    *dst = *src;
}

#define SET_FLAG(FLG, val)  do cpu->flags.FLG = (val); while(0)

__always_inline void LDHL_16(void *RAM, struct CPU *cpu) {
    dword old = cpu->SP;
    dword res = old + *(sword *)imm8(RAM, cpu);
    cpu->HL = *(dword *)MEM(RAM, res);
    SET_FLAG(Z, 0);
    SET_FLAG(N, 0);
    SET_FLAG(H,   (res & 0xF0) != (old & 0xF0));
    SET_FLAG(C, (res & 0xFF00) != (old & 0xFF00));
}

#undef SET_FLAG

// WARNING: Massive bugs expected here

__always_inline void PUSH(void *RAM, struct CPU *cpu, dword *src) {
    *(dword *)MEM(RAM, cpu->SP - 1) = *src;
    cpu->SP -= 2;
}

__always_inline void POP(void *RAM, struct CPU *cpu, dword *dst) {
    *dst = *(word *)MEM(RAM, cpu->SP);
    cpu->SP += 2;
}

#endif // LOADS_H

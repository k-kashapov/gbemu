#ifndef ALU_H
#define ALU_H

#include "cpu.h"
#include "lsm.h"

#define SET_FLAG(FLG, val)  do cpu->flags.FLG = (val); while(0)
#define CCF() wait(4); SET_FLAG(N, 0); SET_FLAG(H, 0); SET_FLAG(C, !cpu->flags.C);
#define SCF() wait(4); SET_FLAG(N, 0); SET_FLAG(H, 0); SET_FLAG(C, 1);
#define CPL() wait(4); SET_FLAG(N, 1); SET_FLAG(H, 1); cpu->A = ~cpu->A;

int ALU8   (struct CPU *cpu, void *RAM, word opcode);
int INCDEC8(struct CPU *cpu, void *RAM, word opcode);

#define INC16(what) wait(8); cpu->what += 1;
#define DEC16(what) wait(8); cpu->what -= 1;

#define ADDSPi()                                                    \
    do {                                                            \
        wait(4);                                                    \
        sword e = (sword)IMM8;                                      \
        wait(8);                                                    \
        dword sum = (dword)((sdword)cpu->SP + e);                   \
        SET_FLAG(Z, 0);                                             \
        SET_FLAG(N, 0);                                             \
        SET_FLAG(H, ((((e & 0xF) + (cpu->SP & 0xF)) & 0x10) == 0x10));\
        SET_FLAG(C,  ((e + (cpu->SP & 0xFF)) > 0xFF));              \
        cpu->SP = sum;                                              \
    } while(0)

#define ADDHL16(src)                                                \
    do {                                                            \
        wait(4);                                                    \
        dword op1 = cpu->H;                                         \
        dword op2 = cpu->src >> 8;                                  \
        wait(4);                                                    \
        SET_FLAG(N, 0);                                             \
        SET_FLAG(H, ((((op1 & 0xF) + (op2 & 0xF)) & 0x10) == 0x10));\
        SET_FLAG(C,   ((op1 + op2) > 0xFF));                        \
        cpu->HL += cpu->src;                                        \
    } while(0)

#endif // ALU_H

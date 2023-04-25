#ifndef ALU_H
#define ALU_H

#include "cpu.h"
#include "lsm.h"

#define SET_FLAG(FLG, val)                  \
    do                                      \
        if (val) {                          \
            cpu->F |= (word)(1 << FLG);     \
        } else {                            \
            cpu->F &= (word)~(1 << FLG);    \
    } while(0)

#define CCF() wait(4); SET_FLAG(NFLG, 0); SET_FLAG(HFLG, 0); SET_FLAG(CFLG, !(cpu->F & (1 << CFLG)));
#define SCF() wait(4); SET_FLAG(NFLG, 0); SET_FLAG(HFLG, 0); SET_FLAG(CFLG, 1);
#define CPL() wait(4); SET_FLAG(NFLG, 1); SET_FLAG(HFLG, 1); cpu->A = ~cpu->A;

int ALU8   (struct CPU *cpu, void *RAM, word opcode);
int INCDEC8(struct CPU *cpu, void *RAM, word opcode);

#define INC16(what) wait(8); cpu->what += 1;
#define DEC16(what) wait(8); cpu->what -= 1;

#define ADDSPi()                                                            \
    do {                                                                    \
        wait(4);                                                            \
        sword e = (sword)IMM8;                                              \
        wait(8);                                                            \
        dword sum = (dword)((sdword)cpu->SP + e);                           \
        SET_FLAG(ZFLG, 0);                                                  \
        SET_FLAG(NFLG, 0);                                                  \
        SET_FLAG(HFLG, ((((e & 0xF) + (cpu->SP & 0xF)) & 0x10) == 0x10));   \
        SET_FLAG(CFLG, (((e + (cpu->SP & 0xFF)) & 0x100) == 0x100));        \
        cpu->SP = sum;                                                      \
    } while(0)

#define ADDHL16(src)                                                    \
    do {                                                                \
        wait(4);                                                        \
        dword op1 = cpu->H;                                             \
        dword op2 = cpu->src >> 8;                                      \
        wait(4);                                                        \
        SET_FLAG(NFLG, 0);                                              \
        SET_FLAG(HFLG, ((((op1 & 0xF) + (op2 & 0xF)) & 0x10) == 0x10)); \
        SET_FLAG(CFLG,  (((op1 + op2) & 0x100) == 0x100));              \
        cpu->HL += cpu->src;                                            \
    } while(0)

// Decimal adjust acumulator
#define DAA()                                               \
    do {                                                    \
        if (!(cpu->F & (1 << NFLG))) {                      \
            if ((cpu->F & (1 << CFLG)) || cpu->A > 0x99) {  \
                cpu->A += 0x60;                             \
                SET_FLAG(CFLG, 1);                          \
            }                                               \
            if ((cpu->F & (1 << HFLG)) || (cpu->A & 0x0F) > 0x09) {\
                cpu->A += 0x06;                             \
            }                                               \
        } else {                                            \
            if ((cpu->F & (1 << CFLG))) cpu->A -= 0x60;     \
            if ((cpu->F & (1 << HFLG))) cpu->A -= 0x06;     \
        }                                                   \
        SET_FLAG(ZFLG, (cpu->A == 0));                      \
        SET_FLAG(HFLG, 0);                                  \
    } while(0)

#define RLA()                                           \
    do {                                                \
        wait(4);                                        \
        dword tmp = (dword)(cpu->A << 1);               \
        cpu->A = (word)(tmp | ((cpu->F >> CFLG) & 1));  \
        cpu->F = 0;                                     \
        SET_FLAG(CFLG, (tmp & 0x100));                  \
    } while(0)

#define RLCA()                                                  \
    do {                                                        \
        wait(4);                                                \
        cpu->F = 0;                                             \
        SET_FLAG(CFLG, (cpu->A >> 7));                          \
        cpu->A = (word)(cpu->A << 1) | (cpu->F & (1 << CFLG));  \
    } while(0)

#define RRA()                                        \
    do {                                             \
        wait(4);                                     \
        word oldC = ((cpu->F >> CFLG) & 1);          \
        cpu->F = 0;                                  \
        SET_FLAG(CFLG, cpu->A & 1);                  \
        cpu->A = (word)((cpu->A >> 1) | (oldC << 7));\
    } while(0)

#define RRCA()                                              \
    do {                                                    \
        wait(4);                                            \
        cpu->F = 0;                                         \
        SET_FLAG(CFLG, cpu->A & 1);                         \
        cpu->A = (word)(cpu->A >> 1) | (word)(cpu->A << 7); \
    } while(0)

#endif // ALU_H

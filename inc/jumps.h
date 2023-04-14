#ifndef JUMPS_H
#define JUMPS_H

#include "general.h"
#include "cpu.h"
#include "mem.h"
#include "lsm.h"

#define JP(to) wait(4); cpu->PC = (to);
#define JPi()  wait(4); JP(IMM16);
#define JPHL() JP(cpu->HL);

// Conditional jmp
#define JPci(cond) \
    do {                    \
        wait(4);            \
        dword dest = IMM16; \
        if (cond) {         \
            JP(dest);       \
        }                   \
    } while(0);

// Relative jmp
#define JR() \
    do {                                                            \
        wait(4);                                                    \
        dword new_pc = (dword)((sdword) cpu->PC + (sword) IMM8 + 1);\
        JP(new_pc);                                                 \
    } while (0)

#define JRc(cond) \
    do {                                                            \
        wait(4);                                                    \
        dword new_pc = (dword)((sdword) cpu->PC + (sword) IMM8 + 1);\
        if (cond) {                                                 \
            JP(new_pc);                                             \
        }                                                           \
    } while (0)

#define CALLi()                 \
    do {                        \
        wait(4);                \
        dword new_pc = IMM16;   \
        PUSH(cpu->PC);          \
        cpu->PC = new_pc;       \
    } while(0)

#define CALLci(cond)            \
    do {                        \
        wait(4);                \
        dword new_pc = IMM16;   \
        if (cond) {             \
            PUSH(cpu->PC);      \
            cpu->PC = new_pc;   \
        }                       \
    } while(0)

#define RET() POPrr(PC); wait(4);

#define RETc(cond)  \
    if (cond) {     \
        POPrr(PC);  \
    } else {        \
        wait(4);    \
    }               \
    wait(4);

// Note: 'i' does not refer to immediate memory access
#define RETI() RET(); cpu->IME = 1;

#define GET_RST_ADDR(op) (dword)((((op) >> 3) & 0x7) << 3)
#define RST(op)                             \
    do {                                    \
        wait(4);                            \
        dword new_pc = GET_RST_ADDR(op);    \
        wait(4);                            \
        cpu->SP -= 2;                       \
        *MEMp16(RAM, cpu->SP) = cpu->PC;    \
        cpu->PC = new_pc;                   \
    } while(0)

#endif // JUMPS_H

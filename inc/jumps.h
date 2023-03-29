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
#define JPci(cond) do wait(4); dword dest = IMM16; if (cond) JP(dest); while(0);

#endif // JUMPS_H

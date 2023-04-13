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

#endif // ALU_H

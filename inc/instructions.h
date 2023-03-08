#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include "cpu.h"

void ALU_A_8  (struct CPU *cpu, const word *src, char op);
void CP_A     (struct CPU *cpu, const word *src);
void INC_DEC_8(struct CPU *cpu,       word *src, char op);
void ALU_16   (struct CPU *cpu,      dword *src, char op);

#endif // INSTRUCTIONS_H

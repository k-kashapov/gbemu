#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include "cpu.h"

void ALU_A_8(struct CPU *cpu, const word* src, uint32_t cycles, char op);
void CP_A   (struct CPU *cpu, const word* src, uint32_t cycles);
void INC_DEC(struct CPU *cpu,       word* src, uint32_t cycles, char op);

#endif // INSTRUCTIONS_H

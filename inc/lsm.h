#ifndef LSM_H
#define LSM_H

// LOAD-STORE MOUDLE

#include "general.h"
#include "cpu.h"
#include "mem.h"

int LD8(struct CPU *cpu, void *RAM, word opcode);

#endif // LSM_H

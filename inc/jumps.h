#ifndef JUMPS_H
#define JUMPS_H

#include "general.h"
#include "cpu.h"
#include "mem.h"
#include "lsm.h"

#define JP() wait(16); cpu->PC = IMM16;

#endif // JUMPS_H

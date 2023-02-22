#include "cpu.h"
#include "general.h"

enum FLAGS {
    C = 1U << 4U, // Carry flag     - last op carried a bit
    H = 1U << 5U, // Half-carry     - last op carried bit from lower half-byte
    N = 1U << 6U, // Substract flag - last op was sub
    Z = 1U << 7U, // Zero flag      - last res = 0 
};

void execOp(struct CPU *cpu, word opcode) {
    (void) cpu;
    DBG_PRINT("executing opcode 0x%02X\n", opcode);
    return;
}

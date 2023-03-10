#include <stdio.h>
#include <sys/types.h>
#include "clock.h"
#include "cpu.h"
#include "mem.h"
#include "instructions.h"
#include "lsm.h"

enum FLAGS {
    BIT_C = 1U << 4U, // Carry flag     - last op carried a bit
    BIT_H = 1U << 5U, // Half-carry     - last op carried bit from lower half-byte
    BIT_N = 1U << 6U, // Substract flag - last op was sub
    BIT_Z = 1U << 7U, // Zero flag      - last res = 0 
};

int execOp(struct CPU *cpu, void *RAM) {
    word opcode = *MEM(RAM, cpu->PC);

    DBG_PRINT("\nExecuting opcode 0x%02X. A: %04X B: %04X C: %04X D: %04X E: %04X F: %04X H: %04X L: %04X PC: %04X SP: %04X",
               opcode, cpu->A, cpu->B, cpu->C, cpu->D, cpu->E, cpu->flags.as_word, cpu->H, cpu->L, cpu->PC, cpu->SP);

    word cycles = 0, op_len = 0;

    switch (opcode) {
        case 0x00: // NOP
            cycles = 4;
            op_len = 1;
            break;
        case 0x10: // STOP
            return STOP;
        
        #include "opcodes.h"

        default:
            wait(4);
            fprintf(stderr, "\nERROR: Unknown opcode: 0x%02x\n", opcode);
            op_len = 1;
            break;
    }

    wait(cycles);
    cpu->PC += op_len;

    return 0;
}

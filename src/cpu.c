#include <stdio.h>
#include <sys/types.h>
#include "clock.h"
#include "cpu.h"
#include "mem.h"
#include "instructions.h"
#include "lsm.h"
#include "jumps.h"

enum FLAGS {
    BIT_C = 1U << 4U, // Carry flag     - last op carried a bit
    BIT_H = 1U << 5U, // Half-carry     - last op carried bit from lower half-byte
    BIT_N = 1U << 6U, // Substract flag - last op was sub
    BIT_Z = 1U << 7U, // Zero flag      - last res = 0 
};

int execOp(struct CPU *cpu, void *RAM) {
    word opcode = MEM8(RAM, cpu->PC);

    DBG_PRINT("Executing opcode 0x%02X. A: %04X B: %04X C: %04X D: %04X E: %04X F: %04X H: %04X L: %04X PC: %04X SP: %04X\n",
               opcode, cpu->A, cpu->B, cpu->C, cpu->D, cpu->E, cpu->flags.as_word, cpu->H, cpu->L, cpu->PC, cpu->SP);
    
    int res = 0;
    cpu->PC++;

    // Check if 8bit load or 8 bit alu
    switch (HI_NIBBLE(opcode) >> 4) {
        case 0x4:
        case 0x5:
        case 0x6:
        case 0x7:
            res = LD8(cpu, RAM, opcode);
            goto finish;

        case 0x8:
        case 0x9:
        case 0xA:
        case 0xB:
            // ALU
            goto finish;

        default:
            break;
    }

    switch (opcode) {
        case 0x00: // NOP
            wait(4);
            break;
        case 0x10: // STOP
            res = STOP;
            break;

        default:
            wait(4);
            fprintf(stderr, "ERROR: Unknown opcode: 0x%02x\n\n", opcode);
            break;
    }

finish:
    return res;
}

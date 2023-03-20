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

#define TOP_NIBBLE(val) ((val) & 0xF0)
#define BOT_NIBBLE(val) ((val) & 0x0F)

int execOp(struct CPU *cpu, void *RAM) {
    word opcode = MEM8(RAM, cpu->PC);

    DBG_PRINT("Executing opcode 0x%02X. A: %04X B: %04X C: %04X D: %04X E: %04X F: %04X H: %04X L: %04X PC: %04X SP: %04X\n",
               opcode, cpu->A, cpu->B, cpu->C, cpu->D, cpu->E, cpu->flags.as_word, cpu->H, cpu->L, cpu->PC, cpu->SP);
    
    cpu->PC++;

    // Check if 8bit load or 8 bit alu
    switch (TOP_NIBBLE(opcode)) {
        case 0x40:
        case 0x50:
        case 0x60:
        case 0x70:
            // LD
            goto finish;

        case 0x80:
        case 0x90:
        case 0xA0:
        case 0xB0:
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
            return STOP;
        case 0x76: // HALT TODO: check
            return HALT;

        default:
            wait(4);
            fprintf(stderr, "ERROR: Unknown opcode: 0x%02x\n\n", opcode);
            break;
    }

finish:
    return 0;
}

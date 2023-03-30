#include <stdio.h>
#include <sys/types.h>
#include "clock.h"
#include "cpu.h"
#include "mem.h"
#include "alu.h"
#include "lsm.h"
#include "jumps.h"

enum FLAGS {
    BIT_C = 1U << 4U, // Carry flag     - last op carried a bit
    BIT_H = 1U << 5U, // Half-carry     - last op carried bit from lower half-byte
    BIT_N = 1U << 6U, // Substract flag - last op was sub
    BIT_Z = 1U << 7U, // Zero flag      - last res = 0 
};

int execOp(struct CPU *cpu, void *RAM) {
    word opcode = ((word *)RAM)[cpu->PC];

    DBG_PRINT("\nExecuting opcode: 0x%02X.   B: %02X   C: %02X   D: %02X   E: %02X   H: %02X   L: %02X   A: %02X   F: %02X   PC: %04X   SP: %04X\n",
               opcode, cpu->B, cpu->C, cpu->D, cpu->E, cpu->H, cpu->L, cpu->A, cpu->flags.as_word, cpu->PC, cpu->SP);
    DBG_PRINT("                  0x%02X\n", ((word *)RAM)[cpu->PC + 1]);
    DBG_PRINT("                  0x%02X\n", ((word *)RAM)[cpu->PC + 2]);
    
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
            ALU8(cpu, RAM, opcode);
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

        // Other 8bit ALU operations
        case 0x02:
            DBG_PRINT("LD (BC), A\n");
            LDmA(BC); break;
        case 0x12:
            DBG_PRINT("LD (DE), A\n");
            LDmA(DE); break;
        case 0x22:
            DBG_PRINT("LD (HL+), A\n");
            LDIHLA(); break;
        case 0x32:
            DBG_PRINT("LD (HL-), A\n");
            LDDHLA(); break;
        case 0x06:
            DBG_PRINT("LD B, imm8\n");
            LDri(B); break;
        case 0x16:
            DBG_PRINT("LD D, imm8\n");
            LDri(D); break;
        case 0x26:
            DBG_PRINT("LD H, imm8\n");
            LDri(H); break;
        case 0x36:
            DBG_PRINT("LD (HL), imm8\n");
            LDHLi(); break;
        case 0x0A:
            DBG_PRINT("LD A, (BC)\n");
            LDAm(BC); break;
        case 0x1A:
            DBG_PRINT("LD A, (DE)\n");
            LDAm(DE); break;
        case 0x2A:
            DBG_PRINT("LD A, (HL+)\n");
            LDIAHL(); break;
        case 0x3A:
            DBG_PRINT("LD A, (HL-)\n");
            LDDAHL(); break;
        case 0x0E:
            DBG_PRINT("LD C, imm8\n");
            LDri(C); break;
        case 0x1E:
            DBG_PRINT("LD E, imm8\n");
            LDri(E); break;
        case 0x2E:
            DBG_PRINT("LD L, imm8\n");
            LDri(L); break;
        case 0x3E:
            DBG_PRINT("LD A, imm8\n");
            LDri(A); break;
        case 0xE0:
            DBG_PRINT("LD (0xFF00 + n), A\n");
            LDHnA(); break;
        case 0xF0:
            DBG_PRINT("LD A, (0xFF00 + n)\n");
            LDHAn(); break;
        case 0xE2:
            DBG_PRINT("LD (0xFF00 + C), A\n");
            LDHCA(); break;
        case 0xF2:
            DBG_PRINT("LD A, (0xFF00 + C)\n");
            LDHAC(); break;
        case 0xEA:
            DBG_PRINT("LD (imm16), A\n");
            LDdA(); break;
        case 0xFA:
            DBG_PRINT("LD A, (imm16)\n");
            LDAd(); break;

        // Jumps
        case 0xC3:
            DBG_PRINT("JUMP 0x%04X -> 0x%04X\n", cpu->PC, *(dword *)((word *)RAM + cpu->PC));
            JPi(); break;

        default:
            wait(4);
            fprintf(stderr, "ERROR: Unknown opcode: 0x%02x\n\n", opcode);
            break;
    }

finish:
    return res;
}

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

#ifdef DBG
void dumpState(struct CPU *cpu, void *RAM, word opcode) {
    DBG_PRINT("\nExecuting opcode: 0x%02X.   B: %02X   C: %02X   D: %02X   E: %02X   H: %02X   L: %02X   A: %02X   F: %02X   PC: %04X   SP: %04X\n",
               opcode, cpu->B, cpu->C, cpu->D, cpu->E, cpu->H, cpu->L, cpu->A, cpu->flags.as_word, cpu->PC, cpu->SP);
    DBG_PRINT("                  0x%02X\n", ((word *)RAM)[cpu->PC + 1]);
    DBG_PRINT("                  0x%02X\n", ((word *)RAM)[cpu->PC + 2]);
}
#endif

int execOp(struct CPU *cpu, void *RAM) {
#ifdef SINGLE_STEP
    getchar();
#endif
    
    word opcode = ((word *)RAM)[cpu->PC];
    
    dumpState(cpu, RAM, opcode);
    
    int res = 0;
    cpu->PC++;

    word hi = HI_NIBBLE(opcode) >> 4;
    // word lo = LO_NIBBLE(opcode);
    
    // All opcodes split into 4 groups for easier decoding
    // REF: https://www.pastraiser.com/cpu/gameboy/gameboy_opcodes.html

    if (hi < 0x4) {
        switch (opcode) {
            case 0x00: // NOP
                DBG_PRINT("NOP\n");
                wait(4);
                break;
            case 0x10: // STOP
                res = STOP;
                DBG_PRINT("STOP\n");
                break;

            // <-----< Other 8 bit lsm operations >----->
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

            // <-----< Other 8-bit ALU ops >------>
            case 0x04: case 0x05:
            case 0x14: case 0x15:
            case 0x24: case 0x25:
            case 0x34: case 0x35:
            case 0x0C: case 0x0D:
            case 0x1C: case 0x1D:
            case 0x2C: case 0x2D:
            case 0x3C: case 0x3D:
                res = INCDEC8(cpu, RAM, opcode);
                break;

            case 0x3F:
                DBG_PRINT("CCF\n");
                CCF(); break;
            case 0x37:
                DBG_PRINT("SCF\n");
                SCF(); break;
            case 0x2F:
                DBG_PRINT("CPL\n");
                CPL(); break;

            // <---< Relative conditional jumps >---->
            case 0x20:
                DBG_PRINT("JR NZ 0x%04X += 0x%02X\n", cpu->PC, *((word *)RAM + cpu->PC));
                JRc(cpu->flags.Z == 0); break;
            case 0x30:
                DBG_PRINT("JR NC 0x%04X += 0x%02X\n", cpu->PC, *((word *)RAM + cpu->PC));
                JRc(cpu->flags.C == 0); break;
            case 0x28:
                DBG_PRINT("JR Z 0x%04X += 0x%02X\n", cpu->PC, *((word *)RAM + cpu->PC));
                JRc(cpu->flags.Z); break;
            case 0x38:
                DBG_PRINT("JR C 0x%04X += 0x%02X\n", cpu->PC, *((word *)RAM + cpu->PC));
                JRc(cpu->flags.C); break;
            case 0x18:
                DBG_PRINT("JR 0x%04X += 0x%02X\n", cpu->PC, *((word *)RAM + cpu->PC));
                JR(); break;

            // <----< 16-bit loads >---->
            case 0x01:
                DBG_PRINT("LD BC, imm16\n");
                LD16ri(BC); break;
            case 0x11:
                DBG_PRINT("LD DE, imm16\n");
                LD16ri(DE); break;
            case 0x21:
                DBG_PRINT("LD HL, imm16\n");
                LD16ri(HL); break;
            case 0x31:
                DBG_PRINT("LD SP, imm16\n");
                LD16ri(SP); break;
            case 0x08:
                DBG_PRINT("LD (imm16), SP");
                LDiSP(); break;

            default:
                wait(4);
                fprintf(stderr, "ERROR: Unknown opcode: 0x%02X\n\n", opcode);
                break;
        }
    } else if (hi >= 0x4 && hi <= 0x7) {
        return LD8(cpu, RAM, opcode);
    } else if (hi >= 0x8 && hi <= 0xB) {
        return ALU8(cpu, RAM, opcode);
    } else {
        switch (opcode) {
            // <---< Immediate ALU8 operations >---->
            case 0xC6: case 0xCE:
            case 0xD6: case 0xDE:
            case 0xE6: case 0xEE:
            case 0xF6: case 0xFE:
                res = ALU8(cpu, RAM, opcode);
                break;

            // <-----< Jumps and calls >----->
            case 0xC3:
                DBG_PRINT("JUMP 0x%04X -> 0x%04X\n", cpu->PC, *(dword *)(uintptr_t)((word *)RAM + cpu->PC));
                JPi(); break;
            case 0xE9:
                DBG_PRINT("JUMP 0x%04X -> 0x%04X\n", cpu->PC, cpu->HL);
                JPHL(); break;
            case 0xCD:
                DBG_PRINT("CALL 0x%04X -> 0x%04X\n", cpu->PC, *(dword *)(uintptr_t)((word *)RAM + cpu->PC));
                CALLi(); break;
            case 0xC9:
                DBG_PRINT("RET 0x%04X -> 0x%04X\n", cpu->PC, *(dword *)(uintptr_t)((word *)RAM + cpu->SP));
                RET(); break;

            // <---< Conditional jumps and calls >---->
            case 0xC2:
                DBG_PRINT("JP NZ: 0x%04X -> 0x%04X\n", cpu->PC, *(dword *)(uintptr_t)((word *)RAM + cpu->PC));
                JPci(cpu->flags.Z == 0); break;
            case 0xD2:
                DBG_PRINT("JP NC: 0x%04X -> 0x%04X\n", cpu->PC, *(dword *)(uintptr_t)((word *)RAM + cpu->PC));
                JPci(cpu->flags.C == 0); break;
            case 0xCA:
                DBG_PRINT("JP Z: 0x%04X -> 0x%04X\n", cpu->PC, *(dword *)(uintptr_t)((word *)RAM + cpu->PC));
                JPci(cpu->flags.Z); break;
            case 0xDA:
                DBG_PRINT("JP C: 0x%04X -> 0x%04X\n", cpu->PC, *(dword *)(uintptr_t)((word *)RAM + cpu->PC));
                JPci(cpu->flags.C); break;

            case 0xC4:
                DBG_PRINT("CALL NZ: 0x%04X -> 0x%04X\n", cpu->PC, *(dword *)(uintptr_t)((word *)RAM + cpu->PC));
                CALLci(cpu->flags.Z == 0); break;
            case 0xD4:
                DBG_PRINT("CALL NC: 0x%04X -> 0x%04X\n", cpu->PC, *(dword *)(uintptr_t)((word *)RAM + cpu->PC));
                CALLci(cpu->flags.C == 0); break;
            case 0xCC:
                DBG_PRINT("CALL Z: 0x%04X -> 0x%04X\n", cpu->PC, *(dword *)(uintptr_t)((word *)RAM + cpu->PC));
                CALLci(cpu->flags.Z); break;
            case 0xDC:
                DBG_PRINT("CALL C: 0x%04X -> 0x%04X\n", cpu->PC, *(dword *)(uintptr_t)((word *)RAM + cpu->PC));
                CALLci(cpu->flags.C); break;

            case 0xC0:
                DBG_PRINT("RET NZ: 0x%04X -> 0x%04X\n", cpu->PC, *(dword *)(uintptr_t)((word *)RAM + cpu->SP));
                RETc(cpu->flags.Z == 0); break;
            case 0xD0:
                DBG_PRINT("RET NC: 0x%04X -> 0x%04X\n", cpu->PC, *(dword *)(uintptr_t)((word *)RAM + cpu->SP));
                RETc(cpu->flags.C == 0); break;
            case 0xC8:
                DBG_PRINT("RET Z: 0x%04X -> 0x%04X\n", cpu->PC, *(dword *)(uintptr_t)((word *)RAM + cpu->SP));
                RETc(cpu->flags.Z); break;
            case 0xD8:
                DBG_PRINT("RET C: 0x%04X -> 0x%04X\n", cpu->PC, *(dword *)(uintptr_t)((word *)RAM + cpu->SP));
                RETc(cpu->flags.C); break;

            case 0xD9:
                DBG_PRINT("RETI\n");
                RETI(); break;

            // <-----< 16-bit addr 8-bit loads >---->
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

            // <----< 16-bit loads >----->
            case 0xC5:
                DBG_PRINT("PUSH BC\n");
                PUSHrr(BC); break;
            case 0xD5:
                DBG_PRINT("PUSH DE\n");
                PUSHrr(DE); break;
            case 0xE5:
                DBG_PRINT("PUSH HL\n");
                PUSHrr(HL); break;
            case 0xF5:
                DBG_PRINT("PUSH AF\n");
                PUSHrr(AF); break;

            case 0xC1:
                DBG_PRINT("POP BC\n");
                POPrr(BC); break;
            case 0xD1:
                DBG_PRINT("POP DE\n");
                POPrr(DE); break;
            case 0xE1:
                DBG_PRINT("POP HL\n");
                POPrr(HL); break;
            case 0xF1:
                DBG_PRINT("POP AF\n");
                POPAF(); break;

            case 0xF8:
                DBG_PRINT("LDHL SP, imm8\n");
                LDHLSP(); break;
            case 0xF9:
                DBG_PRINT("LD SP, HL\n");
                LDSPHL(); break;

            // <----< RESETS >---->
            case 0xC7: case 0xCF:
            case 0xD7: case 0xDF:
            case 0xE7: case 0xEF:
            case 0xF7: case 0xFF:
                DBG_PRINT("RST %02dd\n", GET_RST_ADDR(opcode));
                RST(opcode); break;

            // <----< MISC >----->
            case 0xF3:
                DBG_PRINT("DISABLE INTERRUPTS\n");
                cpu->IME = 0; break;
            case 0xFB:
                DBG_PRINT("ENABLE INTERRUPTS\n");
                cpu->IME = 1; break;

            default:
                wait(4);
                fprintf(stderr, "ERROR: Unknown opcode: 0x%02X\n\n", opcode);
                break;
        }
    }

    return res;
}

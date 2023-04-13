#ifndef LSM_H
#define LSM_H

// LOAD-STORE MOUDLE

#include "general.h"
#include "cpu.h"
#include "mem.h"

// >-------------------<
//      8-bit LOADS
// >-------------------<

// Ptr to a word at PC
__always_inline word imm8(void *RAM, struct CPU *cpu) {
    return MEM8(RAM, cpu->PC++);
}

// Ptr to a dword at PC
__always_inline dword imm16(void *RAM, struct CPU *cpu) {
    dword pc = cpu->PC;
    cpu->PC += 2;
    return MEM16(RAM, pc);
}

#define IMM8  imm8(RAM, cpu)
#define IMM16 imm16(RAM, cpu)

// Memory value at (HL)
#define HL8 MEM8(RAM, cpu->HL)

// Memory ptr to (HL)
#define HL8p MEMp8(RAM, cpu->HL)

#define LD(dst, src) wait(4); (dst) = (src);
#define LDri(dst)    LD(cpu->dst, IMM8);
#define LDHLi()      LD(   *HL8p, IMM8);

// LD A, [(BC), (DE)]
#define LDAm(src) LD(cpu->A, MEM8(RAM, cpu->src));

// LD [(BC), (DE)], A
#define LDmA(dst) LD(*MEMp8(RAM, cpu->dst), cpu->A);

// LD A, (nn)
#define LDAd() LD(cpu->A, MEM8(RAM, IMM16));

// LD (nn), A
#define LDdA() LD(*MEMp8(RAM, IMM16), cpu->A);

// LD A, (0xFF00 + C)
#define LDHAC() LD(cpu->A, MEM8(RAM, 0xFF00 + cpu->C));

// LD (0xFF00 + C), A
#define LDHCA() LD(*MEMp8(RAM, 0xFF00 + cpu->C), cpu->A);

// LD A, (0xFF00 + n)
#define LDHAn() LD(cpu->A, MEM8(RAM, 0xFF00 + IMM8));

// LD (0xFF00 + n), A
#define LDHnA() LD(*MEMp8(RAM, 0xFF00 + IMM8), cpu->A);

// LD A, (HL--)
#define LDDAHL() LD(cpu->A, MEM8(RAM, cpu->HL--));

// LD (HL--), A
#define LDDHLA() LD(*MEMp8(RAM, cpu->HL--), cpu->A);

// LD A, (HL++)
#define LDIAHL() LD(cpu->A, MEM8(RAM, cpu->HL++));

// LD (HL++), A
#define LDIHLA() LD(*MEMp8(RAM, cpu->HL++), cpu->A);

int LD8   (struct CPU *cpu, void *RAM, word opcode);
int LD8rel(struct CPU *cpu, void *RAM, word opcode);

// >--------------------<
//      16-bit LOADS
// >--------------------<

#define PUSH(what)  wait(4); wait(4); cpu->SP -= 2; *MEMp16(RAM, cpu->SP) = what;
#define PUSHrr(reg) PUSH(cpu->reg);

#define POP(what)  wait(4); what = MEM16(RAM, cpu->SP); wait(4); cpu->SP += 2;
#define POPrr(reg) POP(cpu->reg);
#define POPAF()    wait(4); cpu->AF = (MEM16(RAM, cpu->SP) & 0xFFF0); wait(4); cpu->SP += 2;

#define LD16(to, from) wait(4); (to) = (dword)(from);
#define LDSPHL()       wait(4); LD16(cpu->SP, cpu->HL);
#define LD16ri(reg)    wait(4); cpu->reg = IMM16;

// LD (nn), SP
#define LDiSP() LD16(*MEMp16(RAM, IMM16), cpu->SP);

#endif // LSM_H

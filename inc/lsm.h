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
    return MEM8(RAM, cpu->PC);
}

// Ptr to a dword at PC
__always_inline dword imm16(void *RAM, struct CPU *cpu) {
    return MEM16(RAM, cpu->PC);
}

#define IMM8  imm8(RAM, cpu)
#define IMM16 imm16(RAM, cpu)

// Memory value at (HL)
#define HL8 MEM8 (RAM, cpu->HL)

// Memory ptr to (HL)
#define HL8p MEMp8(RAM, cpu->HL)

#define LD(dst, src)   (dst) = (src); wait(4); break
#define LDrr(dst, src) LD(cpu->dst, cpu->src);
#define LDri(dst, src) LD(cpu->dst, IMM8);
#define LDrHL(dst)     LD(cpu->dst, HL8);
#define LDHLr(src)     LD(*HL8p, cpu->dst);
#define LDHLi          LD(*HL8p, IMM8);

// LD A, [(BC), (DE)]
#define LDAm(src) LD(cpu->A, MEM8(RAM, cpu->src));

// LD [(BC), (DE)], A
#define LDmA(dst) LD(*MEMp8(RAM, cpu->src), cpu->A);

// LD A, (nn)
#define LDAd(src) LD(cpu->A, MEM8(RAM, IMM16));

// LD (nn), A
#define LDdA(dst) LD(*MEMp8(RAM, IMM16), cpu->A);

// LD A, (0xFF00 + C)
#define LDHAC LD(cpu->A, MEM8(RAM, 0xFF00 + cpu->C));

// LD (0xFF00 + C), A
#define LDHCA LD(*MEMp8(RAM, 0xFF00 + cpu->C), cpu->A);

// LD A, (0xFF00 + n)
#define LDHAn LD(cpu->A, MEM8(RAM, 0xFF00 + IMM8));

// LD (0xFF00 + n), A
#define LDHnA LD(*MEMp8(RAM, 0xFF00 + IMM8), cpu->A);

// LD A, (HL--)
#define LDDAHL LD(cpu->A, MEM8(RAM, cpu->HL--));

// LD (HL--), A
#define LDDHLA LD(*MEM8(RAM, cpu->HL--), cpu->A);

// LD A, (HL++)
#define LDIAHL LD(cpu->A, MEM8(RAM, cpu->HL++));

// LD (HL++), A
#define LDIHLA LD(*MEM8(RAM, cpu->HL++), cpu->A);

// >--------------------<
//      16-bit LOADS
// >--------------------<

#endif // LSM_H

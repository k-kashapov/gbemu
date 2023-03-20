#include "lsm.h"

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

#define LD(dst, src)   (dst) = (src); wait(4);
#define LDrr(dst, src) LD(*(dst), *(src));
#define LDri(dst)      LD(*(dst),   IMM8);
#define LDrHL(dst)     LD(*(dst),    HL8);
#define LDHLr(src)     LD( *HL8p, *(src));
#define LDHLi          LD( *HL8p,   IMM8);

// LD A, [(BC), (DE)]
#define LDAm(src) LD(cpu->A, MEM8(RAM, cpu->src));

// LD [(BC), (DE)], A
#define LDmA(dst) LD(*MEMp8(RAM, cpu->dst), cpu->A);

// LD A, (nn)
#define LDAd LD(cpu->A, MEM8(RAM, IMM16));

// LD (nn), A
#define LDdA LD(*MEMp8(RAM, IMM16), cpu->A);

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

struct LD8op {
    uint8_t src  : 3;
    uint8_t dst  : 3;
    uint8_t code : 2;
};

// Possible bitfield values for dst and src
enum TARGETS {
    B  = 0b000,
    C  = 0b001,
    D  = 0b010,
    E  = 0b011,
    H  = 0b100,
    L  = 0b101,
    HL = 0b110,
    A  = 0b111,
};

#define REG_PTR(reg) [reg] = &cpu->reg

int LD8(struct CPU *cpu, void *RAM, word opcode) {
    struct LD8op op = *(struct LD8op *)&opcode;
    
    word *regs[8] = {
        REG_PTR(B),
        REG_PTR(C),
        REG_PTR(D),
        REG_PTR(E),
        REG_PTR(H),
        REG_PTR(L),
        REG_PTR(A),
    };

    if (op.dst == HL) {
        if (op.src == HL) {
            return HALT;
        }

        word *src = regs[op.src];
        DBG_PRINT("LDHLr 0x%x\n", op.src);
        LDHLr(src);
        return 0;
    } else if(op.src == HL) {
        word *dst = regs[op.dst];
        DBG_PRINT("LDrHL 0x%x\n", op.dst);
        LDrHL(dst);
        return 0;
    }

    word *dst = regs[op.dst];
    word *src = regs[op.src];

    DBG_PRINT("LDrr 0x%x, 0x%x\n", op.dst, op.src);
    LDrr(dst, src);

    return 0;
}

// >--------------------<
//      16-bit LOADS
// >--------------------<

// TODO: implement

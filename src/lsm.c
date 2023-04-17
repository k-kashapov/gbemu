#include "lsm.h"

// >-------------------<
//      8-bit LOADS
// >-------------------<

#define LDrr(dst, src) LD(*(dst), *(src));
#define LDrHL(dst)     LD(*(dst),    HL8);
#define LDHLr(src)     LD( *HL8p, *(src));

// Possible bitfield values for dst and src
enum TARGETS {
    B  = 0x0,
    C  = 0x1,
    D  = 0x2,
    E  = 0x3,
    H  = 0x4,
    L  = 0x5,
    HL = 0x6,
    A  = 0x7,
};

#define GET_DST(op) (((op) & 0x38) >> 3U)
#define GET_SRC(op) ((op) & 0x07)

#define GET_REGISTER(tgt) (cpu->REGISTERS + (tgt ^ 1U))

#ifdef DBG
    static const char *tgtNames = "BCDEHLmA";
#endif

int LD8(struct CPU *cpu, void *RAM, word opcode) {
    if (GET_DST(opcode) == HL) {
        if (GET_SRC(opcode) == HL) {
            return HALT;
        }

        word *src = GET_REGISTER(GET_SRC(opcode));
        DBG_PRINT("LDHLr %c\n", tgtNames[GET_SRC(opcode)]);
        LDHLr(src);
        return 0;
    } else if(GET_SRC(opcode) == HL) {
        word *dst = GET_REGISTER(GET_DST(opcode));
        DBG_PRINT("LDrHL %c\n", tgtNames[GET_DST(opcode)]);
        LDrHL(dst);
        return 0;
    }

    word *dst = GET_REGISTER(GET_DST(opcode));
    word *src = GET_REGISTER(GET_SRC(opcode));

    DBG_PRINT("LDrr %c, %c\n", tgtNames[GET_DST(opcode)], tgtNames[GET_SRC(opcode)]);
    LDrr(dst, src);

    return 0;
}

word imm8(void *RAM, struct CPU *cpu) {
    return MEM8(RAM, cpu->PC++);
}

dword imm16(void *RAM, struct CPU *cpu) {
    dword pc = cpu->PC;
    cpu->PC += 2;
    return MEM16(RAM, pc);
}


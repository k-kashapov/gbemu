#include "lsm.h"

// >-------------------<
//      8-bit LOADS
// >-------------------<

#define LDrr(dst, src) LD(*(dst), *(src));
#define LDrHL(dst)     LD(*(dst),    HL8);
#define LDHLr(src)     LD( *HL8p, *(src));

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

// Need to do this due to little endianness
#define GET_TGT(op, tgt) (op.tgt ^ 1U)

int LD8(struct CPU *cpu, void *RAM, word opcode) {
    struct LD8op op = *(struct LD8op *)&opcode;

    if (op.dst == HL) {
        if (op.src == HL) {
            return HALT;
        }

        word *src = cpu->REGISTERS + GET_TGT(op, src);
        DBG_PRINT("LDHLr 0x%x\n", op.src);
        LDHLr(src);
        return 0;
    } else if(op.src == HL) {
        word *dst = cpu->REGISTERS + GET_TGT(op, dst);
        DBG_PRINT("LDrHL 0x%x\n", op.dst);
        LDrHL(dst);
        return 0;
    }

    word *dst = cpu->REGISTERS + GET_TGT(op, dst);
    word *src = cpu->REGISTERS + GET_TGT(op, src);

    DBG_PRINT("LDrr 0x%x, 0x%x\n", op.dst, op.src);
    LDrr(dst, src);

    return 0;
}


// >--------------------<
//      16-bit LOADS
// >--------------------<

// TODO: implement

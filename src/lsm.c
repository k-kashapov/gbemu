#include "lsm.h"

// >-------------------<
//      8-bit LOADS
// >-------------------<

#define LDrr(dst, src) LD(*(dst), *(src));
#define LDrHL(dst)     LD(*(dst),    HL8);
#define LDHLr(src)     LD( *HL8p, *(src));

// TODO: Use MACROS instead of bitfields
struct LD8op {
    unsigned int src  : 3;
    unsigned int dst  : 3;
    unsigned int code : 2;
};

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

// Need to do this due to little endianness
#define GET_TGT(op, tgt) (op.tgt ^ 1U)

int LD8(struct CPU *cpu, void *RAM, word opcode) {
    struct LD8op op = *(struct LD8op *)&opcode;

    if (op.dst == HL) {
        if (op.src == HL) {
            return HALT;
        }

        word *src = cpu->REGISTERS + GET_TGT(op, src);
        DBG_PRINT("LDHLr %d\n", op.src);
        LDHLr(src);
        return 0;
    } else if(op.src == HL) {
        word *dst = cpu->REGISTERS + GET_TGT(op, dst);
        DBG_PRINT("LDrHL %d\n", op.dst);
        LDrHL(dst);
        return 0;
    }

    word *dst = cpu->REGISTERS + GET_TGT(op, dst);
    word *src = cpu->REGISTERS + GET_TGT(op, src);

    DBG_PRINT("LDrr %d, %d\n", op.dst, op.src);
    LDrr(dst, src);

    return 0;
}


// >--------------------<
//      16-bit LOADS
// >--------------------<

// TODO: implement

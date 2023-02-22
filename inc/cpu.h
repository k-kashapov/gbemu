#ifndef CPU_H
#define CPU_H

#include "general.h"
#include <sys/cdefs.h>

/* Registers that can be read as single or double word */

#define DWORDREG(h, l)                                  \
    union {                                             \
        struct { word h, l; } __attribute__ ((packed)); \
        dword h##l;                                     \
    }

struct CPU {    
    /* REGISTERS */
    word  A;

    union {
        struct {
            word RSV : 4;
            word C   : 1;
            word H   : 1;
            word N   : 1;
            word Z   : 1;
        } __attribute__ ((packed));

        word as_word;
    } flags;

    DWORDREG(B, C);
    DWORDREG(D, E);
    DWORDREG(H, L);

    dword PC, SP;

    word IME; // Interrupt master enable flag
};

void execOp(struct CPU *cpu, word opcode);

#undef DWORDREG

#endif // CPU_H
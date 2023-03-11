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
    union {
        struct {
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
        };

        dword AF;
    };

    DWORDREG(B, C);
    DWORDREG(D, E);
    DWORDREG(H, L);

    dword PC, SP;

    word IME; // Interrupt master enable flag
};

enum EXEC_RET {
    DONE =  0,
    STOP =  1,
    HALT =  2,
    ERR  = -1,
};

int execOp(struct CPU *cpu, void *RAM);

#undef DWORDREG

#endif // CPU_H
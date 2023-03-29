#ifndef CPU_H
#define CPU_H

#include "general.h"
#include <sys/cdefs.h>

/* Registers that can be read as single or double word */

#define DWORDREG(h, l)                                  \
    union {                                             \
        struct { word l, h; } __attribute__ ((packed)); \
        dword h##l;                                     \
    }

struct CPU {    
    /* REGISTERS */
    union {
        // Registers as an array of words
        word REGISTERS[8];

        // Registers as structures
        struct {
            DWORDREG(B, C);
            DWORDREG(D, E);
            DWORDREG(H, L);
            word A;
            union {
                struct {
                    word RSV : 4;
                    word C   : 1;
                    word H   : 1;
                    word N   : 1;
                    word Z   : 1;
                };
                word as_word;
            } flags;
        };
    } __attribute__ ((packed));
    
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

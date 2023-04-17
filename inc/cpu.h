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

            // This monstrous structure allows us to access
            // registers A and F in various ways. (double word, 2 words, single bit)
            union {
                struct {
                    word A;
                    word F;
                };

                dword AF;
            };
        };
    } __attribute__ ((packed));
    
    dword PC, SP;

    word IME; // Interrupt master enable flag
};

#undef DWORDREG

// Bits of F register
#define CFLG 4U
#define HFLG 5U
#define NFLG 6U
#define ZFLG 7U

enum EXEC_RET {
    DONE =  0,
    STOP =  1,
    HALT =  2,
    ERR  = -1,
};

int execOp(struct CPU *cpu, void *RAM);
void dumpState(struct CPU *cpu, void *RAM, word opcode);

#endif // CPU_H

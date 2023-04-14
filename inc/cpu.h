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
                    union {
                        struct {
                            // TODO: replace with bit operations as compiler can
                            //       change the order of bitfields in a struct
                            word RSV : 4;
                            word C   : 1;
                            word H   : 1;
                            word N   : 1;
                            word Z   : 1;
                        };
                        word as_word;
                    } flags;
                };

                dword AF;
            };
        };
    } __attribute__ ((packed));
    
    dword PC, SP;

    word IME; // Interrupt master enable flag
};

#undef DWORDREG

enum EXEC_RET {
    DONE =  0,
    STOP =  1,
    HALT =  2,
    ERR  = -1,
};

int execOp(struct CPU *cpu, void *RAM);
void dumpState(struct CPU *cpu, void *RAM, word opcode);

#endif // CPU_H

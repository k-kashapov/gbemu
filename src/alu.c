#include <stdio.h>
#include "cpu.h"
#include "clock.h"
#include "general.h"

#define SET_FLAG(FLG, val)  do cpu->flags.FLG = (val); while(0)
#define SET_Z_FLG(res)      SET_FLAG(Z, res == 0)
#define SET_H_FLG(old, res) SET_FLAG(H, (res & 0xF0) != (old & 0xF0))
#define SET_C_FLG(res)      SET_FLAG(C, res > 0xFF)

// >-----------------<
//      ADC 8-bit
// >-----------------<

#define OP_AUTO_FLAGS(op, action, N_FLG)    \
    case (op):                              \
        SET_FLAG(N, N_FLG);                 \
        res = action;                       \
        SET_H_FLG(res, old);                \
        SET_C_FLG(res);                     \
        break;

#define OP_KNOWN_FLAGS(op, action, N_FLG, H_FLG, C_FLG) \
    case (op):                                          \
        SET_FLAG(N, N_FLG);                             \
        SET_FLAG(H, H_FLG);                             \
        SET_FLAG(C, C_FLG);                             \
        res = action;                                   \
        break;

void ALU_A_8(struct CPU *cpu, const word* src, uint32_t cycles, char op) {
    word  old = cpu->A;
    dword res;

    switch (op) {
        OP_AUTO_FLAGS ('+', old + (dword)*src,                 0);       // ADD
        OP_AUTO_FLAGS ('a', old + (dword)*src + (dword)cpu->C, 0);       // ADC
        OP_AUTO_FLAGS ('-', old - (dword)*src,                 1);       // SUB
        OP_AUTO_FLAGS ('s', old - (dword)*src - (dword)cpu->C, 1);       // SBC
        OP_KNOWN_FLAGS('&', old & (dword)*src,                 0, 1, 0); // AND
        OP_KNOWN_FLAGS('|', old | (dword)*src,                 0, 0, 0); // OR
        OP_KNOWN_FLAGS('^', old ^ (dword)*src,                 0, 0, 0); // XOR
    }

    SET_Z_FLG(res);
    cpu->A = (word)res;

    wait(cycles);
}

void CP_A(struct CPU *cpu, const word* src, uint32_t cycles) {
    word  old = cpu->A;
    dword res = (dword)old - (dword)*src;

    SET_Z_FLG(res);
    SET_FLAG (N, 1);
    SET_H_FLG(res, old);
    SET_C_FLG(res);

    wait(cycles);
}

void INC_DEC(struct CPU *cpu, word* src, uint32_t cycles, char op) {
    word  old = *src;
    dword res;

    switch (op) {
        // INC
        case 'i':
            res = old + 1;
            SET_FLAG(N, 0);
            break;

        // DEC
        case 'd':
            res = old - 1;
            SET_FLAG(N, 1);
            break;

        default:
            fprintf(stderr, "ERROR: Invalid operation sent to ALU: |%c|(%d)\n", op, op);
            return;
    }

    *src = (word) res;

    SET_Z_FLG(res);
    SET_H_FLG(old, res);

    wait(cycles);
}

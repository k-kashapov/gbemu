/*
 * WARNING: Current instuction decode sequence is written really poorly.
 *          Needs refactoring. May be done in the future.
 */

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

void ALU_A_8(struct CPU *cpu, const word* src, char op) {
    word  old = cpu->A;
    dword res = old;

    switch (op) {
        OP_AUTO_FLAGS ('+', old + (dword)*src,                 0);       // ADD
        OP_AUTO_FLAGS ('a', old + (dword)*src + (dword)cpu->C, 0);       // ADC
        OP_AUTO_FLAGS ('-', old - (dword)*src,                 1);       // SUB
        OP_AUTO_FLAGS ('s', old - (dword)*src - (dword)cpu->C, 1);       // SBC
        OP_KNOWN_FLAGS('&', old & (dword)*src,                 0, 1, 0); // AND
        OP_KNOWN_FLAGS('|', old | (dword)*src,                 0, 0, 0); // OR
        OP_KNOWN_FLAGS('^', old ^ (dword)*src,                 0, 0, 0); // XOR
        default:
            fprintf(stderr, "ERROR: Invalid operation sent to ALU: |%c|(%d)\n", op, op);
            return;
    }

    SET_Z_FLG(res);
    cpu->A = (word)res;
}

void CP_A(struct CPU *cpu, const word* src) {
    word  old = cpu->A;
    dword res = (dword)old - (dword)*src;

    SET_Z_FLG(res);
    SET_FLAG (N, 1);
    SET_H_FLG(res, old);
    SET_C_FLG(res);
}

void INC_DEC_8(struct CPU *cpu, word* src, char op) {
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
}

// >-----------------<
//      ADC 16-bit
// >-----------------<

void ALU_16(struct CPU *cpu, dword *src, char op) {
    dword old, res;
    
    switch (op) {
        case 'H':
            old = cpu->HL;
            res = old + *src;
            SET_FLAG(N, 0);
            SET_H_FLG(old, res);
            SET_C_FLG(res);
            cpu->HL = res;
            break;

        case 'S':
            old = cpu->SP;
            res = old + (word)*src;
            SET_FLAG(Z, 0);
            SET_FLAG(N, 0);
            SET_H_FLG(old, res);
            SET_C_FLG(res);
            cpu->SP = res;
            break;

        case 'i':
            *src += 1;
            break;

        case 'd':
            *src -= 1;
            break;

        default:
            break;
    }
}

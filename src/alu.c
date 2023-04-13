#include <stdio.h>
#include "alu.h"
#include "clock.h"

#define SET_FLAG(FLG, val)  do cpu->flags.FLG = (val); while(0)
#define SET_Z_FLG(res)      SET_FLAG(Z, res == 0)
#define SET_C_FLG_ADD(res)  SET_FLAG(C, res > 0xFF)
#define SET_C_FLG_SUB(res)  SET_FLAG(C, op1 > op2)

// >-----------------<
//      ALU 8-bit
// >-----------------<

/* 
 * Note: HL suffix = memory reference at addr = cpu->HL
 *       i  suffix = memory reference at cpu->PC
 *       r  suffix = register value
 */

// <-----< GENERAL ALU OPERATIONS >----->

#define ADD(to, from)   wait(4); SET_FLAG(N, 0); op1 = to; op2 = (word)(from); res = (op1 += op2);
#define ADDr(from)      ADD(cpu->A, *from); // May change to ptr in future
#define ADDHL()         ADD(cpu->A, HL8);
#define ADDi()          ADD(cpu->A, IMM8);
#define ADCr(from)      ADD(cpu->A, *from + cpu->flags.C);
#define ADCHL()         ADD(cpu->A, HL8 + cpu->flags.C);
#define ADCi()          ADD(cpu->A, IMM8 + cpu->flags.C);

#define SUB(from, what) wait(4); SET_FLAG(N, 1); op1 = from; op2 = (word)(what); res = ((from) -= op2);
#define SUBr(what)      SUB(cpu->A, *what); // May change to ptr in future
#define SUBHL()         SUB(cpu->A, HL8);
#define SUBi()          SUB(cpu->A, IMM8);
#define SBCr(from)      SUB(cpu->A, *from + cpu->flags.C);
#define SBCHL()         SUB(cpu->A, HL8 + cpu->flags.C);
#define SBCi()          SUB(cpu->A, IMM8 + cpu->flags.C);

#define CP(what)        wait(4); SET_FLAG(N, 1); op1 = cpu->A; op2 = (word)(what); res = (cpu->A - op2);
#define CPr(what)       CP(*what);
#define CPHL()          CP(HL8);
#define CPi()           CP(IMM8);

#define INC(what)       wait(4); SET_FLAG(N, 0); op1 = what; op2 = 1; res = ((what) += 1);
#define INCr(what)      INC(*what);
#define INCHL()         INC(*HL8p);

#define DEC(what)       wait(4); SET_FLAG(N, 1); op1 = what; op2 = 1; res = ((what) -= 1);
#define DECr(what)      DEC(*what);
#define DECHL()         DEC(*HL8p);

// <-----< BIT OPERATIONS >----->

#define LOGIC(op, with) wait(4); SET_FLAG(N, 0); SET_FLAG(C, 0); res = (cpu->A op##= (with));

#define AND(with)   LOGIC(&, (with)); SET_FLAG(H, 1);
#define ANDr(with)  AND(*with);
#define ANDHL()     AND(HL8);
#define ANDi()      AND(IMM8);

#define OR(with)    LOGIC(|, (with)); SET_FLAG(H, 0);
#define ORr(with)   OR(*with);
#define ORHL()      OR(HL8);
#define ORi()       OR(IMM8);

#define XOR(with)   LOGIC(^, (with)); SET_FLAG(H, 0);
#define XORr(with)  XOR(*with);
#define XORHL()     XOR(HL8);
#define XORi()      XOR(IMM8);

// <-----< MISC >------>

#define DAA() wait(4); SET_FLAG(H, 0); ?? // TODO: implement

// <=====< Functions >=====>

// Bit fields of alu 8 opcode
#define GET_ISIMM(op) (((op) & 0xC0) >> 6U)
#define GET_TYPE(op)  (((op) & 0x38) >> 3U)
#define GET_SRC(op)   ((op)  & 0x07)

#define GET_REGISTER(tgt) (cpu->REGISTERS + (tgt ^ 1U))

// Possible bitfield values for dst and src
enum SRCS {
    B  = 0x0, C  = 0x1,
    D  = 0x2, E  = 0x3,
    H  = 0x4, L  = 0x5,
    HL = 0x6,
    A  = 0x7,
};

enum TYPES {
    ADD = 0x0, ADC = 0x1,
    SUB = 0x2, SBC = 0x3,
    AND = 0x4, XOR = 0x5, OR  = 0x6,
    CP  = 0x7,
};

// Is not immediate
#define ISNIM 0x2

// Is immediate (reads value at addr PC)
#define ISIMM 0x3

#ifdef DBG
    static const char *tgtNames = "BCDEHLmA";
#endif

#define CASE_OP(op)                                 \
    case op:                                        \
        DBG_PRINT (                                 \
            "%s" #op " %c\n",                       \
            GET_ISIMM(opcode) == ISIMM ?"IMM8":"",  \
            tgtNames[GET_SRC(opcode)]               \
        );                                          \
        if (GET_SRC(opcode) == HL) {                \
            if (GET_TYPE(opcode) == ISIMM) {        \
                op##i();                            \
            } else {                                \
                op##HL();                           \
            }                                       \
        } else {                                    \
            op##r(GET_REGISTER(GET_SRC(opcode)));   \
        }

int ALU8(struct CPU *cpu, void *RAM, word opcode) {
    dword res = 0;
    word op1 = 0, op2 = 0;

    // Note: known flags are set inside the corresponding MACRO

    switch (GET_TYPE(opcode)) {
        CASE_OP(ADD);
        SET_FLAG(H, (((op1 & 0xF) + (op2 & 0xF)) & 0x10) == 0x10);
        SET_C_FLG_ADD(res);
        break;
        CASE_OP(ADC);
        SET_FLAG(H, (((op1 & 0xF) + (op2 & 0xF)) & 0x10) == 0x10);
        SET_C_FLG_ADD(res);
        break;
        CASE_OP(SUB);
        SET_FLAG(H, ((op1 & 0xF) < (op2 & 0xF)));
        SET_C_FLG_SUB(res);
        break;
        CASE_OP(SBC);
        SET_FLAG(H, ((op1 & 0xF) < (op2 & 0xF)));
        SET_C_FLG_SUB(res);
        break;
        CASE_OP(AND);
        break;
        CASE_OP(XOR);
        break;
        CASE_OP(OR);
        break;
        CASE_OP(CP);
        SET_FLAG(H, ((op1 & 0xF) < (op2 & 0xF)));
        SET_C_FLG_SUB(res);
        break;
    default:
      fprintf(stderr, "Unknown ALU8 cmd: %d\n", GET_TYPE(opcode));
      return -1;
    }

    DBG_PRINT("res = %x, op1 = %x, op2 = %x\n", res, op1, op2);
    SET_Z_FLG(res);

    return 0;
}
#undef GET_SRC
#undef GET_TYPE
#undef GET_ISIMM


// Bit fields of INC and DEC opcodes
#define GET_TYPE(op) (op & 0x7)
#define GET_TGT(op)  (((op) & 0x38) >> 3U)

#define TYPE_INC 0x4
#define TYPE_DEC 0x5

int INCDEC8(struct CPU *cpu, void *RAM, word opcode) {
    word tgt = GET_TGT(opcode);
    dword res = 0;
    word op1 = 0, op2 = 0;

    if (GET_TYPE(opcode) == TYPE_INC) {
        DBG_PRINT("INC %c", tgtNames[tgt]);
        if (tgt == HL) {
            INCHL();
        } else {
            INCr(GET_REGISTER(tgt));
        }

        SET_FLAG(H, (((op1 & 0xF) + (op2 & 0xF)) & 0x10) == 0x10);

    } else {
        DBG_PRINT("DEC %c", tgtNames[tgt]);
        if (tgt == HL) {
            DECHL();
        } else {
            DECr(GET_REGISTER(tgt));
        }

        SET_FLAG(H, ((op1 & 0xF) < (op2 & 0xF)));
    }

    SET_Z_FLG(res);

    return 0;
}

// >-----------------<
//      ALU 16-bit
// >-----------------<

// TODO: implement

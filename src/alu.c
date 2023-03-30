#include <stdio.h>
#include "alu.h"
#include "clock.h"

#define GET_FLAG(FLG) cpu->flags.FLG

#define SET_FLAG(FLG, val)  do cpu->flags.FLG = (val); while(0)
#define SET_Z_FLG(res)      SET_FLAG(Z, res == 0)

// FIXME: incorrect!!!!
#define SET_H_FLG(old, res) SET_FLAG(H, (res & 0xF0) != (old & 0xF0); 1)
#define SET_C_FLG(res)      SET_FLAG(C, res > 0xFF)

// >-----------------<
//      ALU 8-bit
// >-----------------<

/* Note: HL suffix = memory reference at addr = cpu->HL
 *       i  suffix = memory reference at cpu->PC
 *       r  suffix = register value
 */

// <-----< GENERAL ALU OPERATIONS >----->

#define ADD(to, from) wait(4); SET_FLAG(N, 0); old = to; res = ((to) += (word)(from));
#define ADDr(from)    ADD(cpu->A, *from); // May change to ptr in future
#define ADDHL()       ADD(cpu->A, HL8);
#define ADDi()        ADD(cpu->A, IMM8);
#define ADCr(from)    ADD(cpu->A, *from + cpu->flags.C);
#define ADCHL()       ADD(cpu->A, HL8 + cpu->flags.C);
#define ADCi()        ADD(cpu->A, IMM8 + cpu->flags.C);

#define SUB(from, what) wait(4); SET_FLAG(N, 1); old = from; res = ((from) -= (word)(what));
#define SUBr(what)      SUB(cpu->A, *what); // May change to ptr in future
#define SUBHL()         SUB(cpu->A, HL8);
#define SUBi()          SUB(cpu->A, IMM8);
#define SBCr(from)      SUB(cpu->A, *from + cpu->flags.C);
#define SBCHL()         SUB(cpu->A, HL8 + cpu->flags.C);
#define SBCi()          SUB(cpu->A, IMM8 + cpu->flags.C);

#define CPr(what) wait(4); SET_FLAG(N, 1); old = cpu->A; res = (cpu->A - *what);
#define CPHL()    wait(4); SET_FLAG(N, 1); old = cpu->A; res = (cpu->A - HL8);
#define CPi()     wait(4); SET_FLAG(N, 1); old = cpu->A; res = (cpu->A - IMM8);

#define INC(what)  wait(4); SET_FLAG(N, 0); old = what; res = ((what) + 1);
#define INCr(what) INC(*what);
#define INCHL()    INC(HL8);

#define DEC(what)  wait(4); SET_FLAG(N, 1); old = what; res = ((what) - 1);
#define DECr(what) DEC(*what);
#define DECHL()    DEC(HL8);

// <-----< BIT OPERATIONS >----->

#define LOGIC(op, with) wait(4); SET_FLAG(N, 0); SET_FLAG(C, 0); old = cpu->A; res = (cpu->A op##= (with));

#define AND(with)  LOGIC(&, (with));
#define ANDr(with) AND(*with);
#define ANDHL()    AND(HL8);
#define ANDi()     AND(IMM8);

#define OR(with)  LOGIC(|, (with));
#define ORr(with) OR(*with);
#define ORHL()    OR(HL8);
#define ORi()     OR(IMM8);

#define XOR(with)  LOGIC(^, (with));
#define XORr(with) XOR(*with);
#define XORHL()    XOR(HL8);
#define XORi()     XOR(IMM8);

// <-----< MISC >------>

#define CCF() wait(4); SET_FLAG(N, 0); SET_FLAG(H, 0); SET_FLAG(C, !GET_FLAG(C));
#define SCF() wait(4); SET_FLAG(N, 0); SET_FLAG(H, 0); SET_FLAG(C, 1);

#define DAA() wait(4); SET_FLAG(H, 0); ?? // TODO: implement
#define CPL() wait(4); SET_FLAG(N, 1); SET_FLAG(H, 1); cpu->A = ~cpu->A;

// <=====< Functions >=====>

// Bit fields of alu 8 opcode
#define GET_ISIMM(op) (((op) & 0xC0) >> 6U)
#define GET_TYPE(op)  (((op) & 0x38) >> 3U)
#define GET_SRC(op)   ((op)  & 0x07)

#define GET_REGISTER(tgt) (cpu->REGISTERS + (tgt ^ 1U))

// Possible bitfield values for dst and src
enum SRCS {
    B  = 0x0,
    C  = 0x1,
    D  = 0x2,
    E  = 0x3,
    H  = 0x4,
    L  = 0x5,
    HL = 0x6,
    A  = 0x7,
};

enum TYPES {
    ADD = 0x0,
    ADC = 0x1,
    SUB = 0x2,
    SBC = 0x3,
    AND = 0x4,
    XOR = 0x5,
    OR  = 0x6,
    CP  = 0x7,
};

#define ISNIM 0x2
#define ISIMM 0x3

#ifdef DBG
    static const char *tgtNames = "BCDEHLmA";
#endif

#define CASE_OP(op)                                 \
    case op:                                        \
        DBG_PRINT (                                 \
            "%s" #op " %c\n",                       \
            GET_ISIMM(opcode) == ISIMM ? "IMM8" : "", \
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
    dword res = 0, old = 0;

    switch (GET_TYPE(opcode)) {
        CASE_OP(ADD);
        // SET_H_FLG(res, old);
        SET_C_FLG(res);
        break;
        CASE_OP(ADC);
        break;
        CASE_OP(SUB);
        break;
        CASE_OP(SBC);
        break;
        CASE_OP(AND);
        break;
        CASE_OP(XOR);
        break;
        CASE_OP(OR);
        break;
        CASE_OP(CP);
        break;
    default:
      fprintf(stderr, "Unknown ALU8 cmd: %d\n", GET_TYPE(opcode));
      return -1;
    }

    DBG_PRINT("res = %x, old = %x\n", res, old);
    SET_Z_FLG(res);

    return 0;
}

// >-----------------<
//      ALU 16-bit
// >-----------------<

// TODO: implement

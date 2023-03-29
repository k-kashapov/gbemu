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

#define ADD(to, from) wait(4); SET_FLAG(N, 0); old = to; res = ((to) += (from));
#define ADDr(from)    ADD(cpu->A, cpu->from); // May change to ptr in future
#define ADDHL()       ADD(cpu->A, HL8);
#define ADDi()        ADD(cpu->A, IMM8);
#define ADCr(from)    ADD(cpu->A, cpu->from + cpu->flags.C);
#define ADCHL()       ADD(cpu->A, HL8 + cpu->flags.C);
#define ADCi()        ADD(cpu->A, IMM8 + cpu->flags.C);

#define SUB(from, what) wait(4); SET_FLAG(N, 1); old = from; res = ((from) -= (what));
#define SUBr(what)      SUB(cpu->A, cpu->what); // May change to ptr in future
#define SUBHL()         SUB(cpu->A, HL8);
#define SUBi()          SUB(cpu->A, IMM8);
#define SBCr(from)      SUB(cpu->A, cpu->from + cpu->flags.C);
#define SBCHL()         SUB(cpu->A, HL8 + cpu->flags.C);
#define SBCi()          SUB(cpu->A, IMM8 + cpu->flags.C);

#define CP(what) wait(4); SET_FLAG(N, 1); old = cpu->A; res = (cpu->A - cpu->what);
#define CPHL()   wait(4); SET_FLAG(N, 1); old = cpu->A; res = (cpu->A - HL8);
#define CPi()    wait(4); SET_FLAG(N, 1); old = cpu->A; res = (cpu->A - IMM8);

#define INC(what)  wait(4); SET_FLAG(N, 0); old = what; res = ((what) + 1);
#define INCr(what) INC(cpu->what);
#define INCHL()    INC(HL8);

#define DEC(what)  wait(4); SET_FLAG(N, 1); old = what; res = ((what) - 1);
#define DECr(what) DEC(cpu->what);
#define DECHL()    DEC(HL8);

// <-----< BIT OPERATIONS >----->

#define LOGIC(op, with) wait(4); SET_FLAG(N, 0); SET_FLAG(C, 0); old = cpu->A; res = (cpu->A op##= (with));

#define AND(with)  LOGIC(&, (with));
#define ANDr(with) AND(cpu->with);
#define ANDHL()    AND(HL8);
#define ANDi()     AND(IMM8);

#define OR(with)  LOGIC(|, (with));
#define ORr(with) OR(cpu->with);
#define ORHL()    OR(HL8);
#define ORi()     OR(IMM8);

#define XOR(with)  LOGIC(^, (with));
#define XORr(with) XOR(cpu->with);
#define XORHL()    XOR(HL8);
#define XORi()     XOR(IMM8);

// <-----< MISC >------>

#define CCF() wait(4); SET_FLAG(N, 0); SET_FLAG(H, 0); SET_FLAG(C, !GET_FLAG(C));
#define SCF() wait(4); SET_FLAG(N, 0); SET_FLAG(H, 0); SET_FLAG(C, 1);

#define DAA() wait(4); SET_FLAG(H, 0); ?? // TODO: implement

// >-----------------<
//      ALU 16-bit
// >-----------------<

// TODO: implement

#ifndef EMU_H
#define EMU_H

#include "general.h"

#define CPU_FREQ 4194304 // Hz

enum STATES {
    INVAL = 0,
    RDY   = 1,
};

struct Emu {
    word       *RAM;
    enum STATES state;
};

int  initEmu(struct Emu *tgt);
int  getFile(struct Emu *emu, const char name[static 1]);
int  runEmu (struct Emu *emu);
void freeEmu(struct Emu *tgt);

#endif // EMU_H
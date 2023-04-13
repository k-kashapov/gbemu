#ifndef EMU_H
#define EMU_H

#include "cpu.h"
#include "general.h"

enum STATES {
    INVAL = 0,
    RDY   = 1,
};

struct Emu {
    word       *RAM;
    struct CPU  cpu;
    enum STATES state;
};

int  initEmu(struct Emu *tgt);
int  getFile(struct Emu *emu, const char name[static 1]);
int  runEmu (struct Emu *emu);
void freeEmu(struct Emu *tgt);

#endif // EMU_H

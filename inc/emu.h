#ifndef EMU_H
#define EMU_H

#include "general.h"

enum STATES {
    INVAL = 0,
    RDY   = 1,
};

struct Emu {
    word       *RAM;
    enum STATES state;
};

int  initEmu(struct Emu *tgt);
void freeEmu(struct Emu *tgt);
int  getFile(struct Emu *emu, const char name[static 1]);

#endif // EMU_H
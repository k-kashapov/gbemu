#include <malloc.h>
#include <stdio.h>
#include "emu.h"
#include "file.h"

int initEmu(struct Emu *tgt){
    word *mem = (word *)calloc(0x10000, 1);
    if (!mem) {
        perror("ERROR: could not allocate memory");
        return MEM_ALLOC_ERR;
    }

    tgt->RAM   = mem;
    tgt->state = RDY;

    return OK;
}

int getFile(struct Emu *emu, const char name[static 1]) {
    return readFile(emu->RAM, name);
}

void freeEmu(struct Emu *tgt) {
    if (!tgt) return;

    if (tgt->RAM) {
        free(tgt->RAM);
        tgt->RAM = NULL;
    }

    tgt->state = INVAL;
}

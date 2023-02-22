#include <malloc.h>
#include <stdint.h>
#include <stdio.h>
#include "emu.h"
#include "file.h"
#include "general.h"
#include "memlayout.h"

#define RAM_POISON 0xC0DE

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
    int res = readFile(emu->RAM, name);
    if (res <= 0) {
        fprintf(stderr, "ERROR reading file!\n");
        return FILE_OPEN_ERR;
    }

    DBG_PRINT("game name = %.16s\n", emu->RAM + GAME_NAME);

    if (emu->RAM[IS_GBC] == 0x80) {
        fprintf(stderr, "ERROR: GameBoy Color games unsupported!\n");
        return UNSUPPORTED;
    }

    if (emu->RAM[CART_TYPE] != 0) {
        fprintf(stderr, 
                "ERROR: Cartridge modification unsupported: 0x%02x!\n",
                emu->RAM[CART_TYPE]);
        return UNSUPPORTED;
    }

    return OK;
}

void freeEmu(struct Emu *tgt) {
    if (!tgt) return;

    if (tgt->RAM != (word *) RAM_POISON) {
        free(tgt->RAM);
        tgt->RAM = (word *) RAM_POISON;
    }

    tgt->state = INVAL;
}

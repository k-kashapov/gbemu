#include <malloc.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "emu.h"
#include "file.h"
#include "general.h"
#include "memlayout.h"
#include "mem.h"

#define RAM_POISON 0xC0DE

int initEmu(struct Emu *tgt) {
    word *mem = (word *)calloc(MEM_SIZE, 1);
    if (!mem) {
        perror("ERROR: could not allocate memory");
        return MEM_ALLOC_ERR;
    }

    struct CPU new_cpu = {};
    tgt->cpu   = new_cpu;
    tgt->RAM   = mem;
    tgt->state = RDY;

    return OK;
}

int getFile(struct Emu *emu, const char name[static 1]) {
    int res = readFile(emu->RAM, name, MEM_SIZE);
    if (res <= 0) {
        fprintf(stderr, "ERROR reading file!\n");
        return FILE_OPEN_ERR;
    }

    DBG_PRINT("game name = %.16s\n", emu->RAM + GAME_NAME);
    DBG_PRINT("region    = %s\n",    emu->RAM[REGION] ? "WEST" : "JP");

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

    const word logo[GAME_NAME - N_LOGO] = {
        0xCE, 0xED, 0x66, 0x66, 0xCC, 0x0D, 0x00, 0x0B, 0x03, 0x73, 0x00, 0x83, 0x00, 0x0C, 0x00, 0x0D,
        0x00, 0x08, 0x11, 0x1F, 0x88, 0x89, 0x00, 0x0E, 0xDC, 0xCC, 0x6E, 0xE6, 0xDD, 0xDD, 0xD9, 0x99,
        0xBB, 0xBB, 0x67, 0x63, 0x6E, 0x0E, 0xEC, 0xCC, 0xDD, 0xDC, 0x99, 0x9F, 0xBB, 0xB9, 0x33, 0x3E
    };

    if (memcmp(emu->RAM + N_LOGO, logo, GAME_NAME - N_LOGO)) {
        fprintf(stderr, "ERROR: N logo invalid!");
        return UNSUPPORTED;
    }

    return OK;
}

int runEmu(struct Emu *emu) {
    // DEBUG!!!
    emu->cpu.PC = 0x100;
    emu->cpu.A  = 0xAD;
    emu->cpu.B  = 0xC0;
    emu->cpu.C  = 0x70;
    emu->cpu.D  = 0xAB;
    emu->cpu.SP = 0xFFFE;

    int res = 0;

    while (!res) {
        res = execOp(&emu->cpu, emu->RAM);
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

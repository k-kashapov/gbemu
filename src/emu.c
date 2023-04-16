#include <malloc.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#ifdef DBG
#include <signal.h>
#endif

#include "emu.h"
#include "file.h"
#include "general.h"
#include "memlayout.h"
#include "mem.h"

#define RAM_POISON 0xC0DE

#ifdef DBG
static int      ForcedFinish = 0;
static unsigned Breakpoint   = 0x100;

static void sigint_hdlr(int param) {
    (void) param;
    
    fprintf(stderr, "\rWelcome to debug interface.\n");

    while (1) {
        fprintf(stderr, "\r-> ");
        int inpt = getchar();
        if (inpt == '\n') continue;
        switch (inpt) {
            case 'q':
                ForcedFinish = 1;
                return;
            case 'c':
                return;
            case 'b':
                {
                    char str[16];
                    int res = scanf("%s", str);
                    if (res < 1) {
                        fprintf(stderr, "\rInvalid breakpoint option\n");
                    } else {
                        unsigned PC = 0;
                        res = sscanf(str, " %x ", &PC);
                        if (res < 1) {
                            fprintf(stderr, "\rInvalid breakpoint option\n");
                        } else {
                            fprintf(stderr, "Setting breakpoint at 0x%x\n", PC);
                            Breakpoint = PC;
                        }
                    }
                } continue;
            case 'h':
                fprintf(stderr, 
                    "Commands:\n"
                    "h        - show this message;\n"
                    "c        - continue emulation;\n"
                    "q        - stop the emulation;\n"
                    "b 0xXXXX - set breakpoint at PC = 0xXXXX. Only one breakpoint is currently supported;\n"
                );
                continue;
            default:
                fprintf(stderr, "\rUnknown command: %c\n", inpt);
        }
    }
}
#endif // DBG

#ifdef PROXYIO
word ProxySerialBuf[16] = {0};
int  SentLen = -1; // How many bytes to print
#endif // PROXYIO

int initEmu(struct Emu *tgt) {
    word *mem = (word *)malloc(MEM_SIZE);
    if (!mem) {
        perror("ERROR: could not allocate memory");
        return MEM_ALLOC_ERR;
    }

    struct CPU new_cpu = {0};
    tgt->cpu   = new_cpu;
    tgt->RAM   = mem;
    tgt->state = RDY;

#ifdef DBG
    struct sigaction act = {0};
    act.sa_handler  = sigint_hdlr;

    int res = sigaction(SIGINT, &act, NULL);
    if (res < 0) {
        perror("sigaction");
        return res;
    }
#endif

    return OK;
}

int getFile(struct Emu *emu, const char name[static 1]) {
    int res = readFile(emu->RAM, name, MEM_SIZE);
    if (res <= 0) {
        fprintf(stderr, "ERROR reading file!\n");
        return FILE_OPEN_ERR;
    }

#ifdef CHECK_HEADER
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
#endif

    return OK;
}

int runEmu(struct Emu *emu) {
#ifndef CHECK_HEADER
    emu->cpu.PC  = 0x0;
#else
    emu->cpu.PC  = 0x100;
#endif // CHECK_HEADER

    emu->cpu.SP  = 0xFFFE;
    emu->cpu.IME = 1;

    int res = 0;

#ifdef SINGLE_STEP
    DBG_PRINT("Press ENTER to single step\n");
#endif

    while (!res) {
#ifdef DBG
        if (Breakpoint == emu->cpu.PC) {
            DBG_PRINT("\nBREAKPOINT at 0x%x:", Breakpoint);
            dumpState(&emu->cpu, emu->RAM, ((word *)emu->RAM)[emu->cpu.PC]);
            sigint_hdlr(0);
        }

        if (ForcedFinish) break;
#endif // DBG

#ifdef PROXYIO
        if (SentLen > 0) {
            putc(ProxySerialBuf[0], stdout);
            SentLen = 0;
        }
#endif // PROXYIO

        res = execOp(&emu->cpu, emu->RAM);
        // TODO: implement HALT and STOP
    }

    DBG_PRINT("Quitting...\n");

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

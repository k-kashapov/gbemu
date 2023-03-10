#include <stdio.h>
#include <stdlib.h>
#include "emu.h"
#include "general.h"
#include "memlayout.h"
#include "file.h"

void usage(void) {
    printf("USAGE: z80.elf [FILE].gb\n");
}

int main(int argc, const char *argv[static argc + 1]) {
    if (argc < 2) {
        usage();
        return 0;
    } else {
        struct Emu emu = {};
        initEmu(&emu);

        int err = getFile(&emu, argv[1]);

        if (err) {
            freeEmu(&emu);
            return EXIT_FAILURE;
        }

        err = runEmu(&emu);

        freeEmu(&emu);
    }

    return EXIT_SUCCESS;
}

#include <stdio.h>

void usage(void) {
    printf("USAGE: z80.elf [FILE].gb\n");
}

int main(int argc, const char *argv[static argc + 1]) {
    if (argc < 2) {
        usage();
        return 0;
    } else {
        FILE *rom = fopen(argv[1], "rb");
        if (!rom) {
            fprintf(stderr, "Unable to open file: %s\n", argv[1]);
            return -1;
        }

        if (rom) {
            fclose(rom);
        }
    }

    return 0;
}

#include "mem.h"
#include "general.h"

word MEM8 (void *RAM, dword offs) {
    wait(4); 
    return ((word *)RAM)[offs];
}

word *MEMp8(void *RAM, dword offs) {
    wait(4);
    return ((word *)RAM) + offs;
}

dword MEM16 (void *RAM, dword offs) {
    wait(8);
    return *(dword *)((word *)RAM + offs);
}

dword *MEMp16(void *RAM, dword offs) { 
    wait(8);
    return (dword *)((word *)RAM + offs);
}

void dump_mem(void *RAM, size_t len) {
    char *as_char = (char *)RAM;

    for (size_t y = 0; y * 10 < len; y++) {
        for (size_t x = 0; y * 10 + x < len; x++) {
            printf("|%c| (%d) ", as_char[x + 10 * y], as_char[x + 10 * y]);
        } 
        putchar('\n');
    }
}

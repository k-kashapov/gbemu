#include "mem.h"
#include "general.h"

#ifdef PROXYIO
#define SB 0xFF01          // Serial transfer data port
extern word ProxySerialBuf[16]; // Buffer for serial output
extern int  SentLen;
#endif // PROXYIO

word MEM8 (void *RAM, dword offs) {
    wait(4);

#ifdef PROXYIO
    if (offs == SB) {
        char res = getchar();
        while (res == '\n') {
            res = getchar();
        }
        return (word)res[0];
    } else
#endif // PROXYIO

    return ((word *)RAM)[offs];
}

word *MEMp8(void *RAM, dword offs) {
    wait(4);

#ifdef PROXYIO
    if (offs == SB) {
        SentLen = 1;
        return ProxySerialBuf;
    } else
#endif // PROXYIO

    return ((word *)RAM) + offs;
}

dword MEM16 (void *RAM, dword offs) {
    wait(8);

#ifdef PROXYIO
    if (offs == SB) {
        fprintf(stderr, "Cannot read 16-bit values from serial port!\n");
    } else
#endif // PROXYIO

    return *(dword *)(uintptr_t)((word *)RAM + offs);
}

dword *MEMp16(void *RAM, dword offs) { 
    wait(8);

#ifdef PROXYIO
    if (offs == SB) {
        fprintf(stderr, "Cannot write 16-bit values into serial port!\n");
    } else
#endif // PROXYIO

    return (dword *)(uintptr_t)((word *)RAM + offs);
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

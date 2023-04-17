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
        int res = getchar();
        while (res == '\n') {
            res = getchar();
        }
        return (word)res;
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
        return 0;
    } else
#endif // PROXYIO

    return *(dword *)(uintptr_t)((word *)RAM + offs);
}

dword *MEMp16(void *RAM, dword offs) { 
    wait(8);

#ifdef PROXYIO
    if (offs == SB) {
        fprintf(stderr, "Cannot write 16-bit values into serial port!\n");
    }
#endif // PROXYIO

    return (dword *)(uintptr_t)((word *)RAM + offs);
}

void dump_mem(void *RAM, size_t len) {
    unsigned char *as_char = (unsigned char *)RAM;

    for (size_t y = 0; y * 8 < len; y++) {
        for (size_t x = 0; y * 8 + x < len && x < 8; x++) {
            printf("0x%.2X ", as_char[x + 8 * y]);
        } 
        putchar('\n');
    }
}

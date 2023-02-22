#include <unistd.h>
#include "mem.h"

word memRead(void *buff, size_t pos) {
    sleep(1);
    return ((word *)buff)[pos];
}

dword dmemRead(void *buff, size_t pos) {
    sleep(1);
    return ((dword *)buff)[pos];
}

void memWrite(void *buff, size_t pos, word val) {
    sleep(1);
    ((word *)buff)[pos] = val;
}

void dmemWrite(void *buff, size_t pos, dword val) {
    sleep(1);
    ((dword *)buff)[pos] = val;
}

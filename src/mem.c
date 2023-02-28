#include <unistd.h>
#include "mem.h"

word memRead(void *buff, size_t pos) {
    usleep(300000);
    return ((word *)buff)[pos];
}

dword dmemRead(void *buff, size_t pos) {
    usleep(300000);
    return ((dword *)buff)[pos];
}

void memWrite(void *buff, size_t pos, word val) {
    usleep(300000);
    ((word *)buff)[pos] = val;
}

void dmemWrite(void *buff, size_t pos, dword val) {
    usleep(300000);
    ((dword *)buff)[pos] = val;
}

#ifndef GENERAL_H
#define GENERAL_H

#include <stdint.h>

#define DBG_PRINT(...) fprintf(stderr, __VA_ARGS__)

enum ERR_CODES {
    OK            = 0,
    MEM_ALLOC_ERR = -1,
    FILE_OPEN_ERR = -2,
    UNSUPPORTED   = -3,
};

// Machine words on z80
typedef uint8_t  word;
typedef uint16_t dword;

#endif // GENERAL_H

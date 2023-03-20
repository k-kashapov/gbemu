#ifndef GENERAL_H
#define GENERAL_H

#include <stdint.h>
#include <stdio.h>

#define DBG_PRINT(...) fprintf(stderr, __VA_ARGS__)

enum ERR_CODES {
    OK            = 0,
    MEM_ALLOC_ERR = -1,
    FILE_OPEN_ERR = -2,
    UNSUPPORTED   = -3,
};

// Machine words on z80

// unsigned word
typedef uint8_t word;

// signed word
typedef int8_t sword;

// unsigned double word
typedef uint16_t dword;

// signed double word
typedef int16_t sdword;

#define HI_NIBBLE(val) ((val) & 0xF0)
#define LO_NIBBLE(val) ((val) & 0x0F)

#endif // GENERAL_H

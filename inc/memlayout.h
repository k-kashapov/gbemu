#ifndef MEMLAYOUT_H
#define MEMLAYOUT_H

// More detailed at http://gameboy.mongenel.com/dmg/asmmemmap.html

/*
         Interrupt Enable Register
    FFFF --------------------------- INT_ENBL_R
         Internal RAM
    FF80 --------------------------- INTER_RAMH
         Empty but unusable for I/O
    FF4C --------------------------- RSRV_2
         I/O ports
    FF00 --------------------------- IO_PORTS
         Empty but unusable for I/O
    FEA0 --------------------------- RSRV_1
         Sprite Attrib Memory (OAM)
    FE00 --------------------------- SPRITE_ATT
         Echo of 8kB Internal RAM
    E000 --------------------------- INTER_ECHO
         8kB Internal RAM
    C000 --------------------------- INTER_RAML
         8kB switchable RAM bank
    A000 --------------------------- RAM_BANKSW
         8kB Video RAM
    8000 --------------------------- VIDEO_RAM ----*
         16kB switchable ROM bank                  |
    4000 --------------------------- ROM_BANKSW    |= 32kB Cartrige
         16kB ROM bank #0                          |
    0000 --------------------------- ROM_BANK0 ----*
*/

#define ROM_BANK0  0x0000
#define ROM_BANKSW 0x4000
#define VIDEO_RAM  0x8000
#define RAM_BANKSW 0xA000
#define INTER_RAML 0xC000
#define INTER_ECHO 0xE000
#define SPRITE_ATT 0xFE00
#define RSRV_1     0xFEA0
#define IO_PORTS   0xFF00
#define RSRV_2     0xFF4C
#define INTER_RAMH 0xFF80
#define INT_ENBL_R 0xFFFF

#define MEM_SIZE   0x10000

#define ENTRY_POINT 0x0100

// Title information offsets
#define N_LOGO    0x0104

#define GAME_NAME 0x0134
#define IS_GBC    0x0143 // GBC not supported
#define CART_TYPE 0x0147 // Other than 00 are unsupported
#define ROM_SIZE  0x0148
#define RAM_SIZE  0x0149
#define REGION    0x014A


#endif // MEMLAYOUT_H

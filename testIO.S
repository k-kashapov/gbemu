SECTION "Text", ROM0
    LD B, "\n"
loop:
    LD A, [$FF01]
    INC A
    LD [$FF01], A
    CP "0" + 1
    LD A, B
    LD [$FF01], A
    JR NZ, loop

    LD A, "F"
    LD [$FF01], A
    LD A, B
    LD [$FF01], A
STOP

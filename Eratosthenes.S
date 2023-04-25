SECTION "Text", ROM0
    JP Start

; Number representation in hex
HEX: 
    db "0123456789ABCDEF_+()"

; <---------< Clean Up >---------->
; Fill memory range with zeroes
; Expects:
;   HL - memory start
;   B  - size to be filled
; Used registers:
;   A = 0
; Returns: None
CleanUp:
    XOR A            ; Set A = 0
CleanLoop:
    LD [HLI], A      ; *(HL++) = 0
    DEC B            ; Decrement length
    JR NZ, CleanLoop ; Jump back if B != 0
    RET

; <---------< Next Prime >---------->
; Returns next prime number after the
; one stored in BC. 
; Changes the memory in range [HL, HL + 255]
; Expects:
;   BC - Current prime
;   HL - Byte corresponding to the BC
;   
; Used registers:
;   A - tmp storage
;   E - bit iterator
;   D - bit iterator
;   BC & HL changed
; Returns:
;   None

NextPrime:
    LD A, C
    AND 7      ; A = BC & 0b111 - bit number
    LD E, A    ; E = A

    LD A, 8
    SUB E      ; Number of leftover bits
    LD D, A    ; Save it to D

    LD A, [HL]
.RoateBefore:  ; Rotate Byte until we find the current checked bit
    RRCA
    DEC E
    JR NZ, .RoateBefore

.BitLoop:
    RRCA
    JR NC, .Found ; Bit = 0 - found our prime number
    INC BC        ; BC are not the droids we're looking for
    DEC D         ; Decrease D from 7 to 0
    JR NZ, .BitLoop ; Iterate until all bits in byte are checked
    ; If D == 0
    INC HL        ; Start checking the next byte
    LD D, 8
    LD A, [HL]
    JR .BitLoop

.Found:
    RLCA
    INC A         ; Set the found bit
    ; Rotate A until it's back to normal
.Rotation:
    RRCA
    DEC D
    JR NZ, .Rotation

    LD [HL], A  ; Save changed bit
    RET         ; Return found prime in BC

; <----< Fill Divisable >---->
; Fills bits that correspond to every number divisable by the BC
; Expects:
;   BC - number, not changed
;   HL - saved
; Used registers:
;   A, D, E
; Returns:
;   None
FillDiv:
    PUSH HL ; Save HL
    PUSH BC ; Save BC
    PUSH BC ; Save for DE reuse

    ; HL = $C000 + BC >> 3
    LD A, C ; A = C
    AND ~7  ; A = C & 0b11111000
    RRCA    ; A >>= 3
    RRCA
    RRCA
    LD E, A ; Save it to E

    LD A, B
    AND 7   ; A = E & 0b0111
    RRCA    ; A <<= 5
    RRCA
    RRCA
    OR E    ; A = 3 bits from B | 5 bits from C
    LD E, A

    LD A, B ; A = B >> 3
    AND ~7
    RRCA
    RRCA
    RRCA

    LD D, A
    LD HL, $C000
    ADD HL, DE

.FillLoop:
    POP DE
    PUSH DE
    LD A, E
    AND 7
    LD E, A      ; E = C & 0b111 - bit number
    LD D, 8      ; D = 8         - will equal leftover bits number
    
    LD A, [HL]   ; Load byte for this number

.RoateBefore:    ; Rotate until find the needed bit
        RRCA
        DEC D
        DEC E
        JP NZ, .RoateBefore

    OR 1     ; Set the corresponding bit

.RoateAfter:  ; Rotate until it's back in place
        RRCA
        DEC D
        JP NZ, .RoateAfter
    
    LD [HL], A   ; Save changed bit
    
    POP DE       ; DE = old DE value
    LD A, E      ; DE += BC
    ADD C
    LD E, A
    LD A, D
    ADC B
    LD D, A
    PUSH DE

    ; HL = $C000 + DE >> 3
    LD A, E ; A = C
    AND ~7  ; A = C & 0b11111000
    RRCA    ; A >>= 3
    RRCA
    RRCA
    LD E, A ; Save it to E

    LD A, D
    AND 7   ; A = E & 0b0111
    RRCA    ; A <<= 5
    RRCA
    RRCA
    OR E    ; A = 3 bits from B | 5 bits from C
    LD E, A

    LD A, D ; A = B >> 3
    AND ~7
    RRCA
    RRCA
    RRCA

    LD D, A
    LD HL, $C000
    ADD HL, DE

    LD A, L
    CP $30
    JR NZ, .FillLoop

    POP DE
    POP BC
    POP HL
    RET

; <-----< Print A >------>
; Prints sinlge lower nibble stored in A in hex to the serial port
; Expects:
;   A - nibble of number
; Used registers:
;   A
;   D - tmp storage
;   E - tmp storage
; Returns:
;   None
PrintNibble:
    LD D, 0
    LD E, A
    LD HL, HEX
    ADD HL, DE
    LD A, [HL]
    LD [$FF01], A
    RET

; <-----< Print number >------>
; Prints number stored in B:C to the serial port
; Expects:
;   B - HI byte of number
;   C - LO byte of number
; Used registers:
;   A
;   D - tmp storage
;   E - tmp storage
; Returns:
;   A = '\n'
PrintBC:
    PUSH HL
    LD A, B
    RRCA
    RRCA
    RRCA
    RRCA
    AND $0F
    CALL PrintNibble

    LD A, B
    AND $0F
    CALL PrintNibble

    LD A, C
    RRCA
    RRCA
    RRCA
    RRCA
    AND $0F
    CALL PrintNibble

    LD A, C
    AND $0F
    CALL PrintNibble

    LD A, "\n"
    LD [$FF01], A
    POP HL
    RET

; <======< Start >=======>
; Calculate and print first prime numbers
; that are <= 255
; Expects: None
; Used registers: A, B, C, D
; Returns: None
Start:
    LD HL, $C000 ; Internal RAM start
    LD B,  $5    ; Fill with 255 zeroes
    CALL CleanUp

    LD BC, $0002   ; "Previous prime"
    LD HL, $C000   ; Ptr to sieve start

.PrimeLoop:
    CALL NextPrime ; Find next prime
    CALL PrintBC
    CALL FillDiv
    LD A, L
    CP $30
    JR NZ, .PrimeLoop

; DEBUG LOOP
;    XOR A
;Loop:
;    INC A
;    CALL PrintA
;    CP 9
;    JR NZ, Loop

STOP



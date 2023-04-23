SECTION "Text", ROM0
    JP Start

; Number representation in hex
HEX: 
    db "0123456789ABCDEF"

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
;   D - Curr bit
; Used registers:
;   A - tmp storage
; Returns:

NextPrime:
    LD A, [HL]
BitLoop:
    AND 1
    ; Plan:
    ;   E = *(HL)
    ;   A = E
    ;   RRCA          // C flag = lowest bit
    ;   JR NC Found   // Bit = 0 - found our prime number
    ;   INC BC        // BC was not the prime we're looking for
    ;   DEC D         // Decrease D from 7 to 0
    ;   JR NZ BitLoop // Iterate until all bits in byte are checked
    ;   // If D == 0
    ;   INC HL            // Start checking the next byte
    ;   LD D, 7 (maybe 8) // Reset checked bits num
    ;   JR BitLoop
    ; Found:
    ;   OR 1             // Set the found bit
    ;   while (D-- != 0) // Rotate A until it's back to normal
    ;       RRCA
    ;   *(HL) = A        // Save changed bit
    ;   RET              // Return found prime in BC

    ; Next up we need to fill bits that correspond to every number divisable by the BC
    ; Fill:
    ;   
    ;
    ;
    ;
    ;
    ;
    ;

FillDivisable:
    INC [HL]             ; Mark as sieved
    LD A, L              ; Add D to L, which means:
    ADD D                ; goto next number divisible by this prime
    LD L, A              ;
    JR NC, FillDivisable ; If no overflow occured, jump back

    LD A, D ; Return the found prime in A
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

    LD BC, $0001   ; "Previous prime"
    LD HL, $C000   ; Ptr to sieve start
    LD D,  7       ; Bit number
    CALL NextPrime ; Find next prime

    LD BC, $FFFF
    CALL PrintBC

; DEBUG LOOP
;    XOR A
;Loop:
;    INC A
;    CALL PrintA
;    CP 9
;    JR NZ, Loop

STOP



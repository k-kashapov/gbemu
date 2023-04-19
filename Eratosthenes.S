SECTION "Text", ROM0
    JP Start

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
; one stored in register. 
; Changes the memory in range [HL, HL + 255]
; Expects:
;   B  - previous prime
;   HL - pointer to the last prime of the sieve of Eratosthenes
; Used registers:
;   HL - iterator
;   D  - new prime storage
;   BC - iteration step
; Returns:
;   A  - found prime
;   HL - somewhere far away (255 * New Prime)
NextPrime:
    LD D, B ; Load Save previous prime to D

FindPrime:
    INC D
    INC HL
    LD A, [HL] ; Check if current number is prime
    CP 0        ; 
    JR NZ, FindPrime

    ; Found next prime number. It is now stored in D.
    ; And HL points to the zero filled byte. A = 0

FillDivisable:
    INC [HL]             ; Mark as sieved
    LD A, L              ; Add D to L, which means:
    ADD D                ; goto next number divisible by this prime
    LD L, A              ;
    JR NC, FillDivisable ; If no overflow occured, jump back

    LD A, D ; Return the found prime in A
    RET

; <-----< Print num A >------>
; Prints number stored in A to the serial port
; Expects:
;   A - number
; Used registers:
;   A - "0" added
;   B - tmp storage
; Returns:
;   None
PrintA:
    LD B, A
    ADD "0"
    LD [$FF01], A
    LD A, "\n"
    LD [$FF01], A
    LD A, B

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

    LD B, 1        ; "Previous prime"
    LD HL, $C001   ; Ptr to "previous prime" in sieve
    CALL NextPrime ; Find next prime
    CALL PrintA    ; Print it out (if it's 0-9)

    LD B, A        ; "Previous prime"
    LD H, $C0      ; Ptr to "previous prime" in sieve
    LD L, A        ; HL = 0xC0YY, where YY = last sieved prime
    CALL NextPrime ; Find next prime
    CALL PrintA    ; Print it out (if it's 0-9)

    LD B, A        ; "Previous prime"
    LD H, $C0      ; Ptr to "previous prime" in sieve
    LD L, A        ; HL = 0xC0YY, where YY = last sieved prime
    CALL NextPrime ; Find next prime
    CALL PrintA    ; Print it out (if it's 0-9)

    LD B, A        ; "Previous prime"
    LD H, $C0      ; Ptr to "previous prime" in sieve
    LD L, A        ; HL = 0xC0YY, where YY = last sieved prime
    CALL NextPrime ; Find next prime
    CALL PrintA    ; Print it out (if it's 0-9)

    LD B, A        ; "Previous prime"
    LD H, $C0      ; Ptr to "previous prime" in sieve
    LD L, A        ; HL = 0xC0YY, where YY = last sieved prime
    CALL NextPrime ; Find next prime
    CALL PrintA    ; Print it out (if it's 0-9)

    LD B, A        ; "Previous prime"
    LD H, $C0      ; Ptr to "previous prime" in sieve
    LD L, A        ; HL = 0xC0YY, where YY = last sieved prime
    CALL NextPrime ; Find next prime
    CALL PrintA    ; Print it out (if it's 0-9)

    LD B, A        ; "Previous prime"
    LD H, $C0      ; Ptr to "previous prime" in sieve
    LD L, A        ; HL = 0xC0YY, where YY = last sieved prime
    CALL NextPrime ; Find next prime
    CALL PrintA    ; Print it out (if it's 0-9)

; DEBUG LOOP
;    XOR A
;Loop:
;    INC A
;    CALL PrintA
;    CP 9
;    JR NZ, Loop

STOP



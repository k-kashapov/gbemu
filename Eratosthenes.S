SECTION "Text", ROM0
    JP Start

; Fill memory range with zeroes
; Expects:
;   HL - memory start
;   B  - size to be filled
; Used registers:
;   A = 0
; Returns: None
CleanUp:
    XOR A          ; Set A = 0
    LD [HLI], A    ; *(HL++) = 0
    DEC B          ; Decrement length
    JR NZ, CleanUp ; Jump back if B != 0
    RET

; Returns next prime number after the
; one stored in register. 
; Changes the memory in range [HL, HL + 255]
; Expects:
;   B  - previous prime
;   HL - pointer to the last prime of the sieve of Eratosthenes
; Used registers:
;   HL - iterator
;   D  - 
;   BC - 
NextPrime:
    
FindPrime:
    LD A, [HLI]
    CP B
    JR NZ, FindPrime

    



; Calculate and print first prime numbers
; that are <= 255
; Expects: None
; Used registers: A, B, C, D
; Returns: None
Start:
    LD HL, $C000 ; Internal RAM start
    LD B,  $FF   ; Fill with 255 zeroes
    CALL CleanUp



STOP

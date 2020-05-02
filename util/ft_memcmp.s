BITS 64
DEFAULT REL

%include "platform.inc"

SECTION .text
GLOBAL  LINKER_PREFIX(ft_memcmp)

; Parametrs accepting by (64 C Call Convention)
; $RDI - m1 address
; $RSI - m2 address
; $RDX - size

; $AL - return difference
LINKER_PREFIX(ft_memcmp):
    cld
    push    rbx

    ; set rax to 0
    xor     eax, eax
    xor     ebx, ebx
    ; special case for zero size
    test    rdx, rdx
    jz      .epilogue
    ; $rdi and $rsi already set
    ; move size to counter register
    mov     rcx, rdx
    repe    cmpsb

    ; after cmpsb, rdi and rsi point to the next byte after last comapred
    mov     al, BYTE [rdi - 1]
    mov     bl, BYTE [rsi - 1]
    sub     eax, ebx

.epilogue:
    pop     rbx
    ret
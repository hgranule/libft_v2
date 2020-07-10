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
    push    rbx

    xor     rax, rax
    xor     rcx, rcx

; Alignment of address at $RDI for
; using alignment mov operation for xmm registers
.align_loop:
    test    rdx, rdx
    jz      .epilogue
    test    rdi, 0xf
    jz      .main_loop_pre
    movzx   rax, BYTE [rdi]
    movzx   rbx, BYTE [rsi]
    sub     rax, rbx
    jne     .epilogue
    add     rdi, 1
    add     rsi, 1
    sub     rdx, 1
    jmp     .align_loop

.main_loop_pre:
    xor     rbx, rbx
.main_loop:
    ; Checking 16 bytes by one iteration
    movdqa  xmm0, OWORD [rdi + rcx]
    movdqu  xmm1, OWORD [rsi + rcx]
    pcmpeqb xmm0, xmm1
    ; If we meet difference, one of bytes at xmm0 will be 0x00,
    ; so we using mask of highest bits and if it is nor 0xffff
    ; we found difference
    pmovmskb ebx, xmm0
    cmp     ebx, 0xffff
    jne     .compare_diff_byte
    add     rcx, 0x10
    cmp     rcx, rdx
    jb      .main_loop

.epilogue_streq:
    xor     rax, rax
.epilogue:
    pop     rbx
    ret

.compare_diff_byte:
    not     ebx
    bsf     ebx, ebx
    add     rcx, rbx

    ; check if differ-bytes located above the border of comparing
    cmp     rcx, rdx 
    jae     .epilogue_streq

    movzx   rax, BYTE [rdi + rcx]
    movzx   rbx, BYTE [rsi + rcx]
    sub     rax, rbx
    jmp     .epilogue

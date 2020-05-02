BITS 64
DEFAULT REL

%include "platform.inc"

SECTION .text
GLOBAL  LINKER_PREFIX(ft_memset)


; $RDI - address of memory area
; $SIL - filler byte
; $RDX - size of area
LINKER_PREFIX(ft_memset):
    push    rbx
    ; memset returns it's first argument
    xor     rbx, rbx
    mov     bl, sil
    mov     rax, rdi

.alignment_loop:
    cmp     rdx, 0x10
    jl      .fill_remains
    test    rdi, 0xf
    jz      .main_loop
    mov     BYTE [rdi], bl
    add     rdi, 1
    sub     rdx, 1
    jmp     .alignment_loop

.main_loop:
    ; Fill $XMM0 with filler-byte
    mov     bh, bl
    movq    xmm0, rbx
    pshufd  xmm0, xmm0, 0x00
    pshuflw xmm0, xmm0, 0x00
    pshufhw xmm0, xmm0, 0x00

.main_loop_bg:
    cmp     rdx, 0x10
    jl      .fill_remains
    movupd  OWORD [rdi], xmm0
    add     rdi, 0x10
    sub     rdx, 0x10
    jmp     .main_loop_bg

.fill_remains:
    test    rdx, rdx
    jz      .epilogue
    mov     BYTE [rdi], bl
    add     rdi, 1
    sub     rdx, 1
    jmp     .fill_remains

.epilogue:
    pop     rbx
    ret

BITS 64
DEFAULT REL

%include "platform.inc"

SECTION .text
GLOBAL  LINKER_PREFIX(ft_memchr)

; $RDI - address of memory area
; $SIL - goal byte
; $RDX - here located size of memory area
LINKER_PREFIX(ft_memchr):
    push    rbx
    xor     rbx, rbx
    ; $RBX - now is goal-byte located here in low byte
    mov     bl, sil
    xor     rax, rax

.alignment_loop:
    ; Align our address in $RDI by 16 for xmm registers magic
    ; And check lenght remains and goal-byte while padding
    cmp     rdx, 0x10
    jl      .check_remains
    test    rdi, 0xf
    jz      .main_loop
    cmp     BYTE [rdi], bl
    je      .hit
    add     rdi, 1
    sub     rdx, 1
    jmp     .alignment_loop

.main_loop:
    ; Fill $XMM0 with search bytes
    mov     bh,bl
    movq    xmm0, rbx
    pshufd  xmm0, xmm0, 0x00
    pshuflw xmm0, xmm0, 0x00
    pshufhw xmm0, xmm0, 0x00

.main_loop_bg:
    ; Comparing all 16 bytes in parallel with filled mask at $XMM0
    cmp     rdx, 0x10
    jl      .check_remains
    movupd  xmm1, xmm0
    pcmpeqb xmm1, OWORD [rdi]
    pmovmskb esi, xmm1
    test    esi, esi
    jnz     .inject_byte
    add     rdi, 0x10
    sub     rdx, 0x10
    jmp     .main_loop_bg

.inject_byte:
    ; Searching for index of null-byte and adding it to address in $RAX
    xor     rdx, rdx
    bsf     edx, esi
    add     rdi, rdx
    jmp     .hit

.check_remains:
    test    rdx, rdx
    jz      .epilogue
    cmp     BYTE [rdi], bl
    je      .hit
    add     rdi, 1
    sub     rdx, 1
    jmp     .check_remains

.hit:
    mov     rax, rdi

.epilogue:
    pop     rbx
    ret

BITS 64
DEFAULT REL

%include "libasm.inc"
%include "platform.inc"

SECTION .text
GLOBAL  LINKER_PREFIX(ft_strlen)


LINKER_PREFIX(ft_strlen):
    stack_push_8
    mov     rax, rdi

.alignment_loop:
    ; Align our address in RAX by 16 for xmm registers magic
    ; And check null-bytes while padding ofc!
    test    rax, 0xf
    jz      .main_loop
    cmp     BYTE [rax], 0x0
    je      .finish
    add     rax, 1
    jmp     .alignment_loop

.main_loop:
    ; Getting 16 bytes from address in $RAX, and comparing to zerofilled xmm0
    ; If some null-byte appears at 16 bytes, xmm0 would contain 0xff byte at null-byte position
    pxor    xmm0, xmm0
    pcmpeqb xmm0, OWORD [rax]
    pmovmskb esi, xmm0
    test    esi, esi
    jnz     .inject_byte
    add     rax, 0x10
    jmp     .main_loop

.inject_byte:
    ; Searching for index of null-byte and adding it to address in $RAX
    xor     rdx, rdx
    bsf     edx, esi
    add     rax, rdx

.finish:
    ; Getting length by substituting nullbyte address from begin address
    sub     rax, rdi
    stack_pull_8
    ret

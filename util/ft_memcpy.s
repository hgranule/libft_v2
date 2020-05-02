BITS 64
DEFAULT REL

%include "libasm.inc"
%include "platform.inc"

SECTION .text
GLOBAL  LINKER_PREFIX(ft_memcpy)

; Parametrs accepting by (64 C Call Convention)
; $RDI - dst address
; $RSI - src address
; $RDX - size

; $RAX - return of dst address
LINKER_PREFIX(ft_memcpy):
    stack_push_8
    ; save original destionation address for return
    mov     rax, rdi

    ; if addresses equal, then ret!
    test    rdi, rsi
    je      .epilogue

    cld
    ; destination address already located at $RDI (64 bit C call convention)
    ; source address already located at $RSI (64 bit C call convention)
    ; move size of copy to $RCX from $RDX for rep
    mov     rcx, rdx
    rep     movsb

.epilogue:
    stack_pull_8
    ret
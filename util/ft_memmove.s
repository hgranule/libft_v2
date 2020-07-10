BITS 64
DEFAULT REL

%include "libasm.inc"
%include "platform.inc"

SECTION .text
GLOBAL  LINKER_PREFIX(ft_memmove)

; Parametrs accepting by (64 C Call Convention)
; $RDI - dst address
; $RSI - src address
; $RDX - size

; $RAX - return of dst address
LINKER_PREFIX(ft_memmove):
    stack_push_8
    ; save original destionation address for return
    mov     rax, rdi

    cmp    rdi, rsi
    ; if addresses equal, then ret!
    je      .epilogue
    ; if destination address located above source, then jump to backward copy
    ja      .backward_copy
    ; if destination address located below source, we do forward copy

.forward_copy:
    ; setting direction flag to forward order
    cld
    ; setting counter register
    mov     rcx, rdx
    rep     movsb

.epilogue:
    stack_pull_8
    ret

.backward_copy:
    ; setting direction flag to backward order
    std
    ; setting counter register for movs
    mov     rcx, rdx
    sub     rdx, 1
    ; destination and source addresses moved to last bytes
    add     rdi, rdx
    add     rsi, rdx
    rep     movsb
    jmp     .epilogue

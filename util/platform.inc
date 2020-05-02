%ifndef PLATFORM_INC

    %ifidn __OUTPUT_FORMAT__, elf64
        %define SYS_WRITE 0x1
        %define SYS_READ 0x0

        %define LINKER_PREFIX(sym) sym

        %ifndef LIBC_ERR_FUNC
            %define LIBC_ERR_FUNC __errno_location
        %endif

        ; argument is __error_location() symbol
        %macro SYSCALL_ERROR_HANDLER 1

                test eax, eax
                jns .skip_err

                mov     ebx, eax
                neg     ebx
                call    %1
                mov     DWORD [rax], ebx
                mov     rax, -0x1
            
            .skip_err:

        %endmacro

    %elifidn __OUTPUT_FORMAT__, macho64
        %define SYS_WRITE 0x2000004
        %define SYS_READ 0x2000003

        %define LINKER_PREFIX(sym) _%+sym

        %ifndef LIBC_ERR_FUNC
            %define LIBC_ERR_FUNC ___error
        %endif

        ; argument is __error() symbol
        %macro SYSCALL_ERROR_HANDLER 1

                jnc     .skip_err

                mov     ebx, eax
                call    %1
                mov     DWORD [rax], ebx
                mov     rax, -0x1
            
            .skip_err:

        %endmacro

    %else
        %error "Unsupported output format for syscalls, please contact with developers"
    %endif

%endif
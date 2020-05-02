%ifndef LIBASM_INC
    %define LIBASM_INC

    %define stack_push_8 sub rsp, 8
    %define stack_pull_8 add rsp, 8

%endif
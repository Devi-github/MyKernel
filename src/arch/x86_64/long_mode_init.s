global long_mode_start
section .text
bits 64


long_mode_start:
    mov ax, 0
    mov ss, ax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov rsp, long_stack_top ; Move stackptr to rsp

    extern _cmain
    call _cmain

    hlt

section .rodata
CONST_FLT: dq 1.035

section .bss
long_stack_bottom:
    resb 4096
long_stack_top:

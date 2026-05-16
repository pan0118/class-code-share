    .section .text.entry
    .globl _start


_start:
    # 设置栈指针
    la sp, _stack_top
    call main


    # 填充栈空间
    .section .bss
    .align 4
_stack_bottom:
    .space 4096
_stack_top:




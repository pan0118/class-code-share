OUTPUT_ARCH(riscv)
ENTRY(_start)
BASE_ADDRESS = 0x80200000;

SECTIONS
{
    . = BASE_ADDRESS;

    .text :
    {
        _text = .;
        *(.text.entry)
        *(.text*)
        _etext = .;
    }

    .rodata :
    {
        _rodata = .;
        *(.rodata*)
        _erodata = .;
    }

    .data :
    {
        _data = .;
        *(.data*)
        _edata = .;
    }

    .bss :
    {
        *(.bss)
        _stack_bottom = .;
        . += 4096;  # 栈大小为 4KB
        _stack_top = .;
    }
}
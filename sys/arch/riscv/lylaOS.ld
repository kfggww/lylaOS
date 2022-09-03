OUTPUT_FORMAT("elf64-littleriscv", "elf64-littleriscv",
              "elf64-littleriscv")
OUTPUT_ARCH(riscv)
ENTRY(entry)
SECTIONS
{
    . = 0x80200000;
    .text : {*(.text.entry_point)}
    .text : {*(.text .text.*)}
    .text : {*(.trampoline)}
    . = ALIGN(4096);
    PROVIDE(__etext = .);
    PROVIDE(_etext = .);
    PROVIDE(etext = .);
    .rodata : {*(.rodata .rodata.*)}
    .data : {*(.data .data.*)}
    .bss : {*(.bss .bss.*)}
    . = ALIGN(4096);
    PROVIDE(__edata = .);
    PROVIDE(_edata = .);
    PROVIDE(edata = .);
}
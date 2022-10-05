OUTPUT_FORMAT("elf64-littleriscv", "elf64-littleriscv",
	      "elf64-littleriscv")
OUTPUT_ARCH(riscv)
ENTRY(_start)
SECTIONS {
    . = 0x80200000;
    .text : {
        *(.text.entry)
    }
    .text : {
        *(.text .text.*)
    }
    PROVIDE(__etext = .);
    .data : {
        *(.data .data.*)
    }
    .bss : {
        *(.bss .bss.*)
        *(.init.kstack)
    }
    . = ALIGN(0x1000);
    PROVIDE(__edata = .);
}
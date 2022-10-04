#define INIT_KSTACK_SIZE 1024
#define MAX_NCPU 1

.section .text.entry
.global _start
_start:
    la sp, _kstack
    li t0, INIT_KSTACK_SIZE
    add sp, sp, t0
    tail start_kernel

loop_forever:
    wfi
    j loop_forever

.section .bss.kstack
_kstack:
.zero INIT_KSTACK_SIZE * MAX_NCPU
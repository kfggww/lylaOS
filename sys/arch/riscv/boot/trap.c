#include <riscv.h>
#include <types.h>

void kernelvec();

void trapinit()
{
    csr_write(stvec, (uint64)kernelvec);
    uint64 stvec = csr_read(stvec);
    if (stvec != (uint64)kernelvec) {
        stvec = *(int *)0;
    }
}
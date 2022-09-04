#ifndef _ASM_H_
#define _ASM_H_

#include "types.h"

static inline void write_satp(uint64 satp)
{
    asm volatile("csrw satp, %0\n" ::"r"(satp) :);
}

static inline void write_stvec(uint64 stvec)
{
    asm volatile("csrw stvec, %0\n" ::"r"(stvec) :);
}

static inline void write_sepc(uint64 sepc)
{
    asm volatile("csrw sepc, %0\n" ::"r"(sepc) :);
}

static inline void write_sscratch(uint64 sscratch)
{
    asm volatile("csrw sscratch, %0\n" ::"r"(sscratch) :);
}

#endif
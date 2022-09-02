#ifndef _ASM_H_
#define _ASM_H_

#include "types.h"

static inline void write_satp(uint64 satp)
{
    asm volatile("csrw satp, %0\n" ::"r"(satp) :);
}

#endif
#ifndef _RISCV_H_
#define _RISCV_H_
#include <asm/types.h>

#define PTE_V (1 << 0)
#define PTE_R (1 << 1)
#define PTE_W (1 << 2)
#define PTE_X (1 << 3)
#define PTE_U (1 << 4)
#define PTE_G (1 << 5)
#define PTE_A (1 << 6)
#define PTE_D (1 << 7)

#define SV39 (8UL << 60)

#define SV39_VPN(va, level) ((((uint64)(va)) >> (12 + level * 9)) & 0x1FF)

#define SV39_MKPTE(pa, flags)                                                  \
    ((((((uint64)(pa)) >> 12) & 0xFFFFFFFFFFF) << 10) | (flags))

#define SV39_PTE2PA(pte) (((((uint64)(pte)) >> 10) & 0xFFFFFFFFFFF) << 12)

#define SV39_MKSATP(rtpgtbl)                                                   \
    (SV39 | ((((uint64)(rtpgtbl)) >> 12) & 0xFFFFFFFFFFF))

#define RISCV_CSR(csr) #csr

#define csr_read(csr)                                                          \
    ({                                                                         \
        uint64 __val = 0;                                                      \
        asm volatile("csrr %0, " RISCV_CSR(csr) : "=r"(__val)::);              \
        __val;                                                                 \
    })

#define csr_write(csr, val)                                                    \
    asm volatile("csrw " RISCV_CSR(csr) ", %0" ::"r"((val)) :);

#endif
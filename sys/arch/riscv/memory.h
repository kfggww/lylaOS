#ifndef _MEMORY_H_
#define _MEMORY_H_

#include "mem.h"
#include "types.h"

typedef uint64 pte_t;
typedef uint64 *pagetable_t;

/*Page table entry flags.*/
#define PTE_V    (1 << 0)
#define PTE_R    (1 << 1)
#define PTE_W    (1 << 2)
#define PTE_X    (1 << 3)
#define PTE_U    (1 << 4)
#define PTE_G    (1 << 5)
#define PTE_A    (1 << 6)
#define PTE_D    (1 << 7)
#define PTE_RSW0 (1 << 8)
#define PTE_RSW1 (1 << 9)

/*Macros to manipulate page table entry.*/
#define VPN(level, va)    (((va) >> (12 + (level)*9)) & 0x1FF)
#define PTE2PA(pa)        ((((pa) >> 10) & 0xFFFFFFFFFFF) << 12)
#define PA2PTE(pa, flags) (((((pa) >> 12) & 0xFFFFFFFFFFF) << 10) | (flags))
#define SATP_SV39_MODE    (8L << 60)
#define MKSATP(mode, pgtable)                                                  \
    ((mode) | ((((uint64)pgtable) >> 12) & 0xFFFFFFFFFFF))

/*Get page frames range.*/
void pgframe_range(uint64 *pf_start, uint64 *pf_end);

/*Get memory layout of the kernel on RISCV-V platform.*/
mem_map_t *mem_layout();

/*Enable MMU on RISC-V.*/
void arch_enable_mmu(pagetable_t root_pg_table);

/*Create one page map on root_pg_table.*/
void arch_create_mem_map(pagetable_t root_pg_table, uint64 va, uint64 pa,
                         uint32 flags);

#endif
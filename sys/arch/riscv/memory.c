#include "memory.h"
#include "asm.h"
#include "param.h"

extern void trampoline();
extern uint8 __etext;
extern uint8 __edata;
static mem_map_t kmem_layout[KMEM_MAP_NO];

void pgframe_range(uint64 *pf_start, uint64 *pf_end)
{
    *pf_start = (uint64)&__edata;
    *pf_end = PHY_MEM_END;
}

mem_map_t *mem_layout()
{
    kmem_layout[0].name = "text_mapping";
    kmem_layout[0].va = KERN_BASE;
    kmem_layout[0].pa = KERN_BASE;
    kmem_layout[0].size = ((uint64)&__etext - KERN_BASE);
    kmem_layout[0].flags = PTE_R | PTE_X;

    kmem_layout[1].name = "data_mapping";
    kmem_layout[1].va = (uint64)&__etext;
    kmem_layout[1].pa = (uint64)&__etext;
    kmem_layout[1].size = KERN_LIMIT - (uint64)&__etext;
    kmem_layout[1].flags = PTE_R | PTE_W;

    kmem_layout[2].name = "trampoline_mapping";
    kmem_layout[2].va = TRAMPOLINE;
    kmem_layout[2].pa = (uint64)trampoline;
    kmem_layout[2].size = PGSIZE;
    kmem_layout[2].flags = PTE_R | PTE_X;

    return kmem_layout;
}

void arch_enable_mmu(pagetable_t root_pg_table)
{
    uint64 satp = MKSATP(SATP_SV39_MODE, root_pg_table);
    write_satp(satp);
}

void arch_create_mem_map(pagetable_t root_pg_table, uint64 va, uint64 pa,
                         uint32 flags)
{
    int32 level = 2;
    int32 vpn = 0;
    uint64 pf = 0;
    pte_t *pte = 0;

    while (level > 0) {
        vpn = VPN(level, va);
        pte = &root_pg_table[vpn];

        if (*pte == 0) {
            pf = alloc_pgframe();
            *pte = PA2PTE(pf, PTE_V);
        }

        root_pg_table = (pagetable_t)PTE2PA(*pte);
        level -= 1;
    }

    vpn = VPN(0, va);
    pte = &root_pg_table[vpn];
    if (*pte != 0) {
        // TODO: panic
    }

    *pte = PA2PTE(pa, flags | PTE_V);
}
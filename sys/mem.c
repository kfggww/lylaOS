#include "mem.h"
#include "memory.h"
#include "param.h"

struct pageframe {
    struct pageframe *next;
    struct pageframe *prev;
};

static struct pageframe kpf_list_head;
pagetable_t kpg_table;

static uint32 pgframe_list_empty()
{
    if ((kpf_list_head.next == 0 && kpf_list_head.prev == 0) ||
        (kpf_list_head.next == kpf_list_head.prev &&
         kpf_list_head.next == &kpf_list_head)) {
        return 1;
    }
    return 0;
}

uint64 alloc_pgframe()
{
    if (pgframe_list_empty()) {
        return 0;
    }

    struct pageframe *pf = kpf_list_head.next;
    struct pageframe *pf1 = pf->next;

    pf1->prev = &kpf_list_head;
    kpf_list_head.next = pf1;

    pf->next = 0;
    pf->prev = 0;

    return (uint64)pf;
}

void free_pgframe(uint64 pgfrm)
{
    if (pgfrm % PGSIZE) {
        /*TODO: panic here*/
        return;
    }

    struct pageframe *pf = (struct pageframe *)pgfrm;
    struct pageframe *pf1 = kpf_list_head.prev;
    pf1->next = pf;
    pf->next = &kpf_list_head;

    kpf_list_head.prev = pf;
    pf->prev = pf1;
}

void create_mem_map(pagetable_t pgtable, uint64 va, uint64 pa, uint64 size,
                    uint32 flags)
{
    uint64 va_start = va;
    uint64 pa_start = pa;

    while (size > 0) {
        arch_create_mem_map(pgtable, va_start, pa_start, flags);
        size -= PGSIZE;
        va_start += PGSIZE;
        pa_start += PGSIZE;
    }
}

void remove_mem_map(pagetable_t pgtable, uint64 va, uint64 pa, uint64 size);

uint64 search_mem_map(pagetable_t pgtable, uint64 va);

/**
 * @brief Init physical memory of the system.
 *
 * Just using a bidirectional circular linked list to manage the page frames
 * which are free now.
 *
 */
static void init_phys_mem()
{
    uint64 pf_start = 0;
    uint64 pf_end = 0;
    pgframe_range(&pf_start, &pf_end);

    struct pageframe *last_pf = &kpf_list_head;
    struct pageframe *cur_pf = 0;
    uint64 addr = pf_start;

    while (addr < pf_end) {
        cur_pf = (struct pageframe *)addr;
        last_pf->next = cur_pf;
        cur_pf->prev = last_pf;

        last_pf = cur_pf;
        addr += PGSIZE;
    }

    cur_pf = (struct pageframe *)(addr - PGSIZE);
    cur_pf->next = &kpf_list_head;
    kpf_list_head.prev = cur_pf;
}

/**
 * @brief Init virtual memory space of the kernel.
 *
 * Allocate a page frame as the root pagetable of the kernel, then make some
 * necessary memory maps so that we can turn on MMU later.
 *
 */
static void init_virt_mem()
{
    kpg_table = (pagetable_t)alloc_pgframe();

    mem_map_t *mappings = mem_layout();
    mem_map_t map = mappings[0];
    int32 i = 0;

    while (map.size != 0) {
        create_mem_map(kpg_table, map.va, map.pa, map.size, map.flags);
        i += 1;
        map = mappings[i];
    }
}

/**
 * @brief Enable hardware MMU.
 *
 */
static void enable_mmu()
{
    arch_enable_mmu(kpg_table);
}

void mem_init()
{
    init_phys_mem();
    init_virt_mem();
    enable_mmu();
}
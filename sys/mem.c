#include "mem.h"
#include "memory.h"
#include "param.h"

struct pageframe {
    struct pageframe *next;
    struct pageframe *prev;
};

static struct pageframe kpf_list_head = {.next = 0, .prev = 0};

static uint32 pf_list_empty()
{
    if ((kpf_list_head.next == 0 && kpf_list_head.prev == 0) ||
        (kpf_list_head.next == kpf_list_head.prev &&
         kpf_list_head.next == &kpf_list_head)) {
        return 1;
    }
    return 0;
}

static void init_pgframes()
{
    uint64 pf_start = 0;
    uint64 pf_end = 0;
    pgframes_range(&pf_start, &pf_end);

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

static uint64 alloc_pgframe()
{
    if (pf_list_empty()) {
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

void create_mem_map(uint64 pgtable, uint64 va, uint64 pa, uint64 size);

void remove_mem_map(uint64 pgtable, uint64 va, uint64 pa, uint64 size);

uint64 search_mem_map(uint64 pgtable, uint64 va);

void mem_init()
{
    init_pgframes();
}
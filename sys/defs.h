#ifndef _DEFS_H_
#define _DEFS_H_

#include "memory.h"
#include "types.h"

/*mem.c*/
void mem_init();
uint64 alloc_pgframe();
void free_pgframe(uint64 pgfrm);
void create_mem_map(pagetable_t pgtable, uint64 va, uint64 pa, uint64 size,
                    uint32 flags);

/*proc.c*/
struct proc *create_init_proc();
void sched();

#endif
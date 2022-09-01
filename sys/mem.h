#ifndef _MEM_H_
#define _MEM_H_

#include "types.h"

void mem_init();

void create_mem_map(uint64 pgtable, uint64 va, uint64 pa, uint64 size);
void remove_mem_map(uint64 pgtable, uint64 va, uint64 pa, uint64 size);
uint64 search_mem_map(uint64 pgtable, uint64 va);

#endif
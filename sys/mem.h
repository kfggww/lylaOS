#ifndef _MEM_H_
#define _MEM_H_

#include "types.h"

/*Discribe the mapping between vm and pm, used by all the platforms that the
 * kernel supports.*/
typedef struct {
    uint64 va;
    uint64 pa;
    uint32 size;
    uint32 flags;
    uint8 *name;
} mem_map_t;

uint64 alloc_pgframe();
void free_pgframe(uint64 pgfrm);

#endif
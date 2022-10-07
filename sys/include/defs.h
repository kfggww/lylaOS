#ifndef _DEFS_H_
#define _DEFS_H_
#include <types.h>

/*memory module interface*/
void kpminit();
void kvminit();

void *pm_alloc();
int32 pm_free(void *pa);

int32 vm_map(void *pgtbl, void *va, void *pa, size_t sz, uint32 flags);
int32 vm_unmap(void *pgtbl, void *va, size_t sz);
void *vm_map_get(void *pgtbl, void *va);

/*trap handler*/
void trapinit();

#endif
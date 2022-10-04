#ifndef _ARCH_GENERIC_H_
#define _ARCH_GENERIC_H_
#include <types.h>

/*Memory module of a specific architecture*/
void arch_kpminit();
void arch_kvminit();

void *arch_pm_alloc();
int32 arch_pm_free(void *pa);

int arch_vm_map(void *pgtbl, void *va, void *pa, size_t sz, uint32 flags);
int arch_vm_unmap(void *pgtbl, void *va, size_t sz);
void *arch_vm_map_get(void *pgtbl, void *va);

#endif
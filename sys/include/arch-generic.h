#ifndef _ARCH_GENERIC_H_
#define _ARCH_GENERIC_H_
#include <types.h>

/*memory module of a specific architecture*/
void arch_kpminit();
void *arch_kvminit();

void *arch_pm_alloc();
int32 arch_pm_free(void *pa);

int32 arch_vm_map(void *pgtbl, void *va, void *pa, ssize_t sz, uint32 flags);
int32 arch_vm_unmap(void *pgtbl, void *va, size_t sz);
void *arch_vm_map_get(void *pgtbl, void *va);
uint32 arch_cvt_vmflags(uint32 flags);

#endif
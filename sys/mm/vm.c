#include <arch-generic.h>

void *kpgtable;

void kvminit()
{
    kpgtable = arch_kvminit();
}

int32 vm_map(void *pgtbl, void *va, void *pa, size_t sz, uint32 flags)
{
    flags = arch_cvt_vmflags(flags);
    return 0;
}

int32 vm_unmap(void *pgtbl, void *va, size_t sz)
{
    return 0;
}

void *vm_map_get(void *pgtbl, void *va)
{
    return 0;
}

void memset(void *s, int32 c, size_t n)
{
    for (int i = 0; i < n / sizeof(int32); ++i) {
        ((int32 *)s)[i] = c;
    }
}
#include <arch-generic.h>

void kpminit()
{
    arch_kpminit();
}

void *pm_alloc()
{
    return arch_pm_alloc();
}

int32 pm_free(void *pa)
{
    return arch_pm_free(pa);
}
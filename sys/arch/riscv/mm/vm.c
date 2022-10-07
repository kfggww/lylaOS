#include <arch-generic.h>
#include <kernel.h>
#include <riscv.h>
#include <soc.h>

void *arch_kvminit()
{
    struct __kvm_map {
        void *va;
        void *pa;
        size_t sz;
        uint32 flags;
    } kvm_maps[] = {{.va = (void *)KERN_BASE,
                     .pa = (void *)KERN_BASE,
                     .sz = PAGESIZE,
                     .flags = PTE_V | PTE_R | PTE_X}};

    void *rt_pgtbl = arch_pm_alloc();

    for (int i = 0; i < sizeof(kvm_maps) / sizeof(struct __kvm_map); ++i) {
        if (arch_vm_map(rt_pgtbl, kvm_maps[i].va, kvm_maps[i].pa,
                        kvm_maps[i].sz, kvm_maps[i].flags)) {
            panic("kvminit panic!\n");
        }
    }

    return rt_pgtbl;
}

int32 arch_vm_map(void *pgtble, void *va, void *pa, size_t sz, uint32 flags)
{
    return 0;
}

uint32 arch_cvt_vmflags(uint32 flags)
{
    return flags;
}
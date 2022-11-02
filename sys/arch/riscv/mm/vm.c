#include <arch-generic.h>
#include <kernel.h>
#include <riscv/riscv.h>
#include <riscv/soc.h>

uint64 *walk_pgtbl(uint64 *pgtble, void *va, uint32 flags, int32 create);

void *arch_kvminit()
{
    /*prepare kernel mappings*/
    extern int32 __etext;

    struct __kvm_map {
        void *va;
        void *pa;
        size_t sz;
        uint32 flags;
    } kvm_maps[] = {{.va = (void *)KERN_BASE,
                     .pa = (void *)KERN_BASE,
                     .sz = (size_t)&__etext - KERN_BASE,
                     .flags = PTE_V | PTE_R | PTE_X},
                    {
                        .va = &__etext,
                        .pa = &__etext,
                        .sz = DRAM_LIMIT - (size_t)&__etext,
                        .flags = PTE_R | PTE_W,
                    }};

    void *rt_pgtbl = arch_pm_alloc();

    /*map va to pa in kernel root pagtable*/
    for (int i = 0; i < sizeof(kvm_maps) / sizeof(struct __kvm_map); ++i) {
        if (arch_vm_map(rt_pgtbl, kvm_maps[i].va, kvm_maps[i].pa,
                        kvm_maps[i].sz, kvm_maps[i].flags)) {
            panic("kvminit panic!\n");
        }
    }

    /*enable mmu*/
    uint64 satp_val = SV39_MKSATP(rt_pgtbl);
    csr_write(satp, satp_val);

    /*return kernel pagetable*/
    return rt_pgtbl;
}

int32 arch_vm_map(void *pgtble, void *va, void *pa, ssize_t sz, uint32 flags)
{
    va = (void *)ROUND_UP_PGSZ(va);
    pa = (void *)ROUND_UP_PGSZ(pa);
    sz = (ssize_t)ROUND_DOWN_PGSZ(sz);

    while (sz > 0) {
        uint64 *pte = walk_pgtbl((uint64 *)pgtble, va, flags, 1);
        if (pte == 0 || *pte & PTE_V) {
            return -1;
        }
        *pte = SV39_MKPTE(pa, flags | PTE_V);
        sz -= PAGESIZE;
        va = (void *)((uint64)va + PAGESIZE);
        pa = (void *)((uint64)pa + PAGESIZE);
    }

    return 0;
}

uint32 arch_cvt_vmflags(uint32 flags)
{
    return flags;
}

uint64 *walk_pgtbl(uint64 *pgtble, void *va, uint32 flags, int32 create)
{
    uint64 *pte = 0;
    int32 vpn = 0;

    int level = 2;
    while (level >= 0) {
        vpn = SV39_VPN(va, level);
        pte = &pgtble[vpn];

        if (*pte == 0 || !((*pte) & PTE_V)) {
            if (!create)
                return 0;
            else {
                if (level > 0) {
                    pgtble = (uint64 *)arch_pm_alloc();
                    *pte = SV39_MKPTE(pgtble, PTE_V);
                } else {
                    return pte;
                }
            }
        } else {
            pgtble = (uint64 *)SV39_PTE2PA(*pte);
        }

        level -= 1;
    }

    return pte;
}
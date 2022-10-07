#include <kernel.h>
#include <list.h>
#include <soc.h>
#include <types.h>

struct pgframe {
    struct list_head list;
};

static struct pgframe pgfrms;

extern int32 __etext;
extern int32 __edata;

void arch_kpminit()
{
    INIT_LIST_HEAD(pgfrms.list);

    uint64 pos = (uint64)&__edata;
    while (pos < DRAM_LIMIT) {
        struct pgframe *pgf = (struct pgframe *)pos;
        list_add(&pgf->list, &pgfrms.list);
        pos += PAGESIZE;
    }
}

void *arch_pm_alloc()
{
    struct list_head *node = list_del_prev(&pgfrms.list);
    if (node == 0)
        return 0;
    void *pgfrm = container_of(node, struct pgframe, list);
    memset(pgfrm, 0, PAGESIZE);
    return pgfrm;
}

int32 arch_pm_free(void *pa)
{
    if (((size_t)pa) % PAGESIZE)
        return -1;
    list_add(&((struct pgframe *)pa)->list, &pgfrms.list);
    return 0;
}
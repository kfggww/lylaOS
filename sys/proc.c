#include "proc.h"
#include "defs.h"
#include "memory.h"
#include "param.h"

extern void trampoline();
extern void usertrap();
extern void userret();
extern void swtch(struct context *ctx0, struct context *ctx1);
extern pagetable_t kpg_table;

static struct proc proc[NPROC];
static uint64 pid;
static uint16 init_code[] = {
    0x7179, 0xf422, 0x1800, 0x87aa, 0x3823, 0xfcb4, 0x2e23, 0xfcf4, 0x4785,
    0x2423, 0xfef4, 0x2623, 0xfe04, 0xa801, 0x2703, 0xfec4, 0x2783, 0xfe84,
    0x9fb9, 0x2623, 0xfef4, 0x2783, 0xfe84, 0x871b, 0x0007, 0x0793, 0x0640,
    0xd3e3, 0xfee7, 0x4781, 0x853e, 0x7422, 0x6145, 0x8082};
static struct context sched_ctx;
struct proc *current;

static struct proc *alloc_proc()
{
    int32 found = -1;
    for (int i = 0; i < NPROC; ++i) {
        if (proc[i].state == SUNUSED) {
            proc[i].state = SUSED;
            found = i;
            break;
        }
    }

    if (found == -1) {
        // TODO: panic
    }

    return &proc[found];
}

static void init_proc(struct proc *p)
{
    p->pid = pid;
    pid += 1;

    /*init trapframe of current proc*/
    p->trapframe = (struct trapframe *)alloc_pgframe();
    p->trapframe->ra = UVM_TEXT;
    p->trapframe->sp = UVM_STACK + UVM_STACK_SIZE;
    p->trapframe->epc = UVM_TEXT;
    p->trapframe->kern_stack = alloc_pgframe() + PGSIZE;
    p->trapframe->kern_satp = MKSATP(SATP_SV39_MODE, kpg_table);
    p->trapframe->user_trap = (uint64)usertrap;

    /*init user proc virtual memmory*/
    p->pg_table = (pagetable_t)alloc_pgframe();
    uint64 pa = alloc_pgframe();
    for (int i = 0; i < sizeof(init_code) / sizeof(uint16); i++) {
        ((uint16 *)pa)[i] = init_code[i];
    }
    create_mem_map(p->pg_table, UVM_TEXT, pa, UVM_TEXT_SIZE,
                   PTE_R | PTE_X | PTE_U);
    pa = alloc_pgframe();
    create_mem_map(p->pg_table, UVM_STACK, pa, UVM_STACK_SIZE,
                   PTE_R | PTE_W | PTE_U);
    create_mem_map(p->pg_table, TRAPFRAME, (uint64)p->trapframe, PGSIZE,
                   PTE_R | PTE_W);
    create_mem_map(p->pg_table, TRAMPOLINE, (uint64)trampoline, PGSIZE,
                   PTE_R | PTE_X);

    /*init user proc context*/
    p->context.ra = (uint64)userret;
    p->context.sp = p->trapframe->kern_stack;

    p->state = SREADY;
}

struct proc *create_init_proc()
{
    struct proc *p = alloc_proc();
    init_proc(p);
}

void sched()
{
    while (1) {
        int32 found = -1;
        for (int i = 0; i < NPROC; i++) {
            if (proc[i].state == SREADY) {
                current = &proc[i];
                proc[i].state = SRUNING;
                swtch(&sched_ctx, &proc[i].context);
            }
        }
    }
}
#include "asm.h"
#include "memory.h"
#include "param.h"
#include "proc.h"
#include "types.h"

extern void uservec();
extern void uservec_ret();
extern void kernelvec();
extern struct proc *current;

void usertrap()
{
    /*switch 'stvec' to kernelvec*/
    uint64 stvec = (uint64)kernelvec;
    write_stvec(stvec);

    /*TODOs: handle different kinds of traps*/
}

void userret()
{
    /*set register sepc*/
    write_sepc(current->trapframe->epc);

    /*switch back stvec register to uservec*/
    write_stvec(TRAMPOLINE);

    /*set sscratch to trapframe*/
    write_sscratch(TRAPFRAME);

    /*call uservec_ret in the trampoline section*/
    uint64 satp = MKSATP(SATP_SV39_MODE, current->pg_table);
    void (*fn)(uint64, uint64) =
        (void (*)(uint64, uint64))(TRAMPOLINE + (uint64)uservec_ret - (uint64)uservec);
    fn(satp, TRAPFRAME);
}

void kerneltrap()
{
}
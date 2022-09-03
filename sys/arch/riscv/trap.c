#include "asm.h"
#include "types.h"

extern void kernelvec();

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
    int a = 10;
    int b = 20;
    int c = a + b;

    /*switch back stvec register to uservec*/

    /*call uservec_ret in the trampoline section*/
}

void kerneltrap()
{
}
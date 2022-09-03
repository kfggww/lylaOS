#ifndef _PROC_H_
#define _PROC_H_

#include "memory.h"
#include "types.h"

struct trapframe {
    uint64 ra;         /*0*/
    uint64 sp;         /*8*/
    uint64 gp;         /*16*/
    uint64 tp;         /*24*/
    uint64 t0;         /*32*/
    uint64 t1;         /*40*/
    uint64 t2;         /*48*/
    uint64 s0;         /*56*/
    uint64 s1;         /*64*/
    uint64 a0;         /*72*/
    uint64 a1;         /*80*/
    uint64 a2;         /*88*/
    uint64 a3;         /*96*/
    uint64 a4;         /*104*/
    uint64 a5;         /*112*/
    uint64 a6;         /*120*/
    uint64 a7;         /*128*/
    uint64 s2;         /*136*/
    uint64 s3;         /*144*/
    uint64 s4;         /*152*/
    uint64 s5;         /*160*/
    uint64 s6;         /*168*/
    uint64 s7;         /*176*/
    uint64 s8;         /*184*/
    uint64 s9;         /*192*/
    uint64 s10;        /*200*/
    uint64 s11;        /*208*/
    uint64 t3;         /*216*/
    uint64 t4;         /*224*/
    uint64 t5;         /*232*/
    uint64 t6;         /*240*/
    uint64 epc;        /*248*/
    uint64 kern_stack; /*256*/
    uint64 kern_satp;  /*264*/
    uint64 user_trap;  /*272*/
};

struct context {
    uint64 ra;
    uint64 sp;
    uint64 s0;
    uint64 s1;
    uint64 s2;
    uint64 s3;
    uint64 s4;
    uint64 s5;
    uint64 s6;
    uint64 s7;
    uint64 s8;
    uint64 s9;
    uint64 s10;
    uint64 s11;
};

enum proc_state { SUNUSED, SUSED, SREADY, SRUNING, SSLEEP, SZOMBIE };

struct proc {
    uint32 pid;
    enum proc_state state;
    struct trapframe *trapframe;
    struct context context;
    pagetable_t pg_table;
};

#endif
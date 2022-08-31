#ifndef _PROC_H_
#define _PROC_H_

#include "types.h"

enum proc_state { SREADY, SRUNING, SSLEEP, SZOMBIE };

struct proc {
    uint32 p_pid;
    enum proc_state p_state;
};

#endif
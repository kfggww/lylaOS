#ifndef _PARAMS_H_
#define _PARAMS_H_

#define KSTACK_SIZE    1024
#define PGSIZE         4096
#define PHY_MEM_START  0x80000000
#define PHY_MEM_SIZE   (128 * 1024 * 1024)
#define PHY_MEM_END    (PHY_MEM_START + PHY_MEM_SIZE)
#define KERN_BASE      0x80200000
#define KERN_LIMIT     PHY_MEM_END
#define KMEM_MAP_NO    6
#define NPROC          64
#define TRAMPOLINE     0xBFFFF000
#define TRAPFRAME      (TRAMPOLINE - PGSIZE)
#define UVM_STACK      (TRAPFRAME - PGSIZE)
#define UVM_TEXT       0x10000000
#define UVM_STACK_SIZE 4096
#define UVM_TEXT_SIZE  4096

#endif
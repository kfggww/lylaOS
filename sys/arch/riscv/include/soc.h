#ifndef _SOC_H_
#define _SOC_H_

// memory layout
#define DRAM_BASE       0x80000000UL
#define DRAM_SIZE       (128UL * 1024UL * 1024UL)
#define DRAM_LIMIT      (DRAM_BASE + DRAM_SIZE)
#define PAGESIZE        4096
#define KERN_BASE       0x80200000UL
#define TRAMPOLINE_BASE 0xfffff000UL
#define TRAMPOLINE_SIZE PAGESIZE

#endif
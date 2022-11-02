#ifndef _KERNEL_H_
#define _KERNEL_H_

#include <asm/types.h>

#define container_of(ptr, type, member)                                        \
    ((type *)(((size_t)ptr) - (size_t)(&((type *)0)->member)))

void panic(const char *fmt, ...);

void memset(void *s, int32 c, size_t n);

#endif
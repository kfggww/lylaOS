#include <defs.h>

void __attribute__((noreturn)) start_kernel()
{
    kpminit();
    kvminit();
    __builtin_unreachable();
}
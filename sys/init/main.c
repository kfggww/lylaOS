#include <defs.h>

void __attribute__((noreturn)) start_kernel()
{
    trapinit();
    kpminit();
    kvminit();
    __builtin_unreachable();
}
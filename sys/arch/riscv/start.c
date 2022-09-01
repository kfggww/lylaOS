#include "param.h"
#include "types.h"

uint8 kern_stack[KSTACK_SIZE];

void start_kernel();

void __attribute__((noreturn)) start()
{
    int a = 10;
    int b = 20;
    int c = a + b;
    start_kernel();
    __builtin_unreachable();
}
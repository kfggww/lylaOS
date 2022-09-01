#include "params.h"
#include "types.h"

uint8 kern_stack[KSTACK_SIZE];

void start_kernel();

void start()
{
    start_kernel();
}
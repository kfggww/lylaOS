#include "memory.h"
#include "param.h"

extern char __edata;

void pgframes_range(uint64 *pf_start, uint64 *pf_end)
{
    *pf_start = (uint64)&__edata;
    *pf_end = PHY_MEM_END;
}
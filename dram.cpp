#include "dram.h"
#include "iport.h"
#include "dport.h"

dram::dram(uint32_t iportStart, uint32_t iportEnd, uint32_t dportStart, uint32_t dportEnd)
{
    ip = new iport(this, iportStart, iportEnd);
    dp = new dport(this, dportStart, dportEnd);
}
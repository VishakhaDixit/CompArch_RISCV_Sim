#ifndef __MEMBUS_H__
#define __MEMBUS_H__

#include "globals.h"

class Mesi
{
    private:
        Globals *gb;
        void updateCurCacheState(uint8_t cpu_id, uint32_t addr, cache_state st);
        
    public:
        Mesi(Globals *g);

        void process(operation_type opType, uint8_t cpu_id, uint32_t addr, uint32_t *clk);
};

#endif //__MEMBUS_H__
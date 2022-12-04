#include "mesi.h"

Mesi::Mesi(Globals *g) 
{
    gb = g;
}

void Mesi::process(operation_type opType, uint8_t cpu_id, uint32_t addr, uint32_t *clk)
{
    cache_state cs = gb->getUpdtCacheState(cpu_id, addr);
    cache_state new_cs;

    if(opType == Read)
    {
        switch (cs)
        {
        case invalid:
            //Check for first time main memory access.
            if(gb->curCacheState.empty())   
            {
                new_cs = exclusive;
                gb->supplier_map[addr] = cpu_id;
                *clk += 4;
            }
            else 
            {
                for(auto & [key, value] : gb->curCacheState)
                {
                    if((key != cpu_id) && (value.addr == addr))
                    {
                        if((gb->getUpdtCacheState(key, addr)) != invalid)
                        {
                            new_cs = shared;
                            updateCurCacheState(key, addr, shared);
                        }
                    }
                    else
                    {
                        new_cs = exclusive;
                    }
                }
                *clk += 1;
            }

            updateCurCacheState(cpu_id, addr, new_cs);
            break;
        
        default:
            break;
        }
    }
    else if(opType == Write)
    {
        new_cs = modified;
        gb->supplier_map[addr] = cpu_id;
        *clk += 3;

        for(auto & [key, value] : gb->curCacheState)
        {
            if((key != cpu_id) && (value.addr == addr))
            {
                updateCurCacheState(key, addr, invalid);
            }
        }

        updateCurCacheState(cpu_id, addr, new_cs);
    }
}

void Mesi::updateCurCacheState(uint8_t cpu_id, uint32_t addr, cache_state st)
{
    // If there exits an entry for given tag then update it's status.
    for(auto & [key, value] : gb->curCacheState)
    {
        if((key == cpu_id) && (value.addr == addr))
        {
            gb->curCacheState[cpu_id].state = st;
            return;
        }
    }

    // Else make a new global entry.
    gb->curCacheState[cpu_id].addr = addr;
    gb->curCacheState[cpu_id].state = st;
}
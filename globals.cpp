#include "globals.h"

cache_state Globals::getUpdtCacheState(uint8_t cpu_id, uint32_t addr)
{
    {
        // cache state for any addr will be invalid initially.
        cache_state curState = invalid;
        
        // If there exits a status update for given tag then return it's state.
        for(auto & [key, value] : curCacheState)
        {
            if((key == cpu_id) && (value.addr == addr))
            {
                curState = curCacheState[cpu_id].state;
                break;
            }
        }

        // Else return invalid.
        return curState;
    }
}

string Globals::convToStr(cache_state s)
{
    switch (s)
    {
    case exclusive:
        return "exclusive";

    case shared:
        return "shared";
    
    case modified:
        return "modified";        
    }

    return "invalid";
}
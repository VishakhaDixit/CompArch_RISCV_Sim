#include "cache.h"
#include <cassert>
#include <cstring>
#include <iostream>
#include <cstdlib>
#include <cmath>

Cache::Cache(size_t size, size_t _line, associativity_type a)
{
    assoc = a;
    cache_size = size;
    line_size = _line;

    if (assoc == none)
    {
        int num_sets = size / line_size;
        
        for (int i = 0; i < num_sets; i++)
        {
            lineData *table = new lineData();
            table->index = 0;
            table->tag = 0;
            table->valid_bit = false;
            table->lru_count = 0;   // lru bits not needed
            maps.push_back(table);
        }
    }
}

Cache::~Cache()
{

}

bool Cache::isHit(uint32_t addr)
{
    uint32_t line_idx;
    uint32_t line_tag;
    uint32_t set;

    if(assoc == none)
    {
        line_idx = addr % cache_size;
        line_tag = addr / cache_size;
        set = line_idx >> (int)std::log2(line_size);
        if ((maps[set]->valid_bit) && (maps[set]->tag == line_tag)) 
        {
            return true;
        } 
    }

    // Make entry in the cache if it's a miss
    maps[set]->index = line_idx;
    maps[set]->tag = line_tag;
    maps[set]->valid_bit = 1;

    return false;
}

void Cache::process(uint32_t addr)
{
    if(this->isHit(addr))
    {
        hit_num++;
    }
    else
    {
        miss_num++;
    }
}


uint8_t Cache::getData(uint32_t addr)
{
    return 0;
}

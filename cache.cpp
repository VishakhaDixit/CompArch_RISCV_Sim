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
            lineData* table = new lineData();
            table->index = 0;
            table->tag = 0;
            table->valid_bit = false;
            table->lru_count = 0;
            //mru bits not needed
            maps.push_back(table);
        }
    }
}

bool Cache::isHit(uint32_t addr)
{
    
}
#include "cache.h"
#include <cassert>
#include <cstring>
#include <iostream>
#include <cstdlib>
#include <cmath>

Cache::Cache(size_t size, size_t _line, associativity_type a, arbiter *arbC)
{
    assoc = a;
    cache_size = size;
    line_size = _line;
    set_size = 0;
    arb = arbC;

    uint32_t num_lines;

    num_lines = size / line_size;
    
    for (int i = 0; i < num_lines; i++)
    {
        lineData *table = new lineData();
        table->tag = 0;
        table->valid_bit = false;
        table->lru_count = 0;   // lru bits initialized to 0
        table->set_num = 0;
        maps.push_back(table);
    }
}

Cache::~Cache()
{
    delete this;
}


void Cache::updateCacheLine(uint32_t set, uint32_t set_size, uint32_t tag)
{
    // Update Cache Entry
    if(assoc == none) 
    {
        maps[set]->tag = tag;
        maps[set]->valid_bit = 1;
    }
    else if(assoc == two_way || assoc == four_way)
    {
        uint32_t stCacheAddr = (this->set_size * set);
        pair<uint32_t, uint32_t> min_cnt;
        min_cnt.first = stCacheAddr;
        min_cnt.second = maps[stCacheAddr]->lru_count;

        for(uint32_t i = stCacheAddr; i < (stCacheAddr + this->set_size); i++)
        {
            if(maps[i]->lru_count < min_cnt.second)
            {
                min_cnt.first = i;
                min_cnt.second = maps[i]->lru_count;
            }
        }

        maps[min_cnt.first]->valid_bit = 1;
        maps[min_cnt.first]->tag = tag;
        maps[min_cnt.first]->lru_count++;
    }
}

bool Cache::isHit(uint32_t addr)
{
    uint32_t line_idx;
    uint32_t line_tag;
    uint32_t line_num;
    uint8_t set_num;
    uint32_t total_lines;
    uint8_t idx_bits;
    uint32_t set_size;

    if(assoc == none)
    {
        line_idx = addr % cache_size;
        line_tag = addr / cache_size;
        line_num = line_idx >> (int)std::log2(line_size);
        if ((maps[line_num]->valid_bit) && (maps[line_num]->tag == line_tag)) 
        {
            return true;
        }
            
        updateCacheLine(line_num, 0, line_tag);
    }
    else if(assoc == two_way)
    {
        total_lines = cache_size / line_size;
        idx_bits = log2(total_lines);
        this->set_size = total_lines / 2;

        line_tag = addr / cache_size;
        set_num = (addr >> idx_bits) & 0x1;

        uint32_t stCacheAddr = (this->set_size * set_num);

        for(uint32_t i = stCacheAddr; i < (stCacheAddr + this->set_size); i++)
        {
            if ((maps[i]->valid_bit) && (maps[i]->tag == line_tag)) 
            {
                return true;
            } 
        }

        updateCacheLine(set_num, set_size, line_tag);
    }    
    else if(assoc == four_way)
    {
        total_lines = cache_size / line_size;
        idx_bits = log2(total_lines);
        this->set_size = total_lines / 4;

        line_tag = addr / cache_size;
        set_num = (addr >> idx_bits) & 0x3;

        uint32_t stCacheAddr = (this->set_size * set_num);

        for(uint32_t i = stCacheAddr; i < (stCacheAddr + this->set_size); i++)
        {
            if ((maps[i]->valid_bit) && (maps[i]->tag == line_tag)) 
            {
                return true;
            } 
        }

        updateCacheLine(set_num, set_size, line_tag);
    }

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

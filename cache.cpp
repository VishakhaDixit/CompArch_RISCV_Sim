/**************************
 *
 * @file    cache.cpp
 *
 * @brief   This file contains definitions for Cache class APIs.
 *
 * @date    Nov 11, 2022
 *
 * @author  Vishakha Dixit
 *
 **************************/

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
        table->state = invalid;
        maps.push_back(table);
    }

    hit_num = 0;
    miss_num = 0;
}

Cache::~Cache()
{
    delete this;
}


void Cache::updateCache(uint32_t addr, uint32_t val)
{
    uint32_t line_idx;
    uint32_t tag;
    uint8_t set;
    uint32_t total_lines;
    uint8_t idx_bits;

    // Update Cache Entry
    if(assoc == none) 
    {
        line_idx = addr % cache_size;
        tag = addr / cache_size;
        set = line_idx >> (int)std::log2(line_size);

        maps[set]->tag = tag;
        maps[set]->valid_bit = 1;
        maps[set]->data = val;

        return;
    }
    else if(assoc == two_way)
    {
        total_lines = cache_size / line_size;
        idx_bits = log2(total_lines);
        this->set_size = total_lines / 2;

        tag = addr / cache_size;
        set= (addr >> idx_bits) & 0x1;
    }
    else if(assoc == four_way)
    {
        total_lines = cache_size / line_size;
        idx_bits = log2(total_lines);
        this->set_size = total_lines / 4;

        tag = addr / cache_size;
        set= (addr >> idx_bits) & 0x3;
    }
    
    uint32_t stCacheAddr = (this->set_size * set);
    pair<uint32_t, uint32_t> min_cnt;
    min_cnt.first = stCacheAddr;
    min_cnt.second = maps[stCacheAddr]->lru_count;

    for(uint32_t i = stCacheAddr; i < (stCacheAddr + this->set_size); i++)
    {
        if(maps[i]->tag == tag)
        {
            min_cnt.first = i;
            break;
        }
        else if(maps[i]->lru_count < min_cnt.second)
        {
            min_cnt.first = i;
            min_cnt.second = maps[i]->lru_count;
        }
    }

    maps[min_cnt.first]->valid_bit = 1;
    maps[min_cnt.first]->tag = tag;
    maps[min_cnt.first]->lru_count++;
    maps[min_cnt.first]->set_num = set;
    maps[min_cnt.first]->data = val;

    return;
}

bool Cache::isHit(uint32_t addr)
{
    uint32_t line_idx;
    uint32_t line_tag;
    uint32_t line_num;
    uint8_t set_num;
    uint32_t total_lines;
    uint8_t idx_bits;

    if(assoc == none)
    {
        line_idx = addr % cache_size;
        line_tag = addr / cache_size;
        line_num = line_idx >> (int)std::log2(line_size);
        if ((maps[line_num]->valid_bit) && (maps[line_num]->tag == line_tag)) 
        {
            return true;
        }
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
    }

    return false;
}

bool Cache::isArbBusy()
{
    return arb->getBusyFlag();
}

void Cache::processArbMesi(operation_type op, uint8_t cpu_id, uint32_t addr, uint32_t *clk)
{
    arb->processMESI(op, cpu_id, addr, clk);
}

void Cache::setArbBusy(bool flag)
{
    arb->setBusyFlag(flag);
}

bool Cache::getData(uint32_t addr, uint32_t *data_buf)
{
    if(isHit(addr))
    {
        if(assoc == none)
        {
            uint32_t line_idx = addr % cache_size;
            uint32_t line_num = line_idx >> (int)std::log2(line_size);
            *data_buf = (maps[line_num]->data);
            hit_num++;
            return true;
        }
        else if(assoc == two_way)
        {
            uint32_t total_lines = cache_size / line_size;
            uint32_t idx_bits = log2(total_lines);
            this->set_size = total_lines / 2;

            uint32_t tag = addr / cache_size;
            uint8_t set= (addr >> idx_bits) & 0x1;

            uint32_t stCacheAddr = (this->set_size * set);

            for(uint32_t i = stCacheAddr; i < (stCacheAddr + this->set_size); i++)
            {
                if((maps[i]->valid_bit) && maps[i]->tag == tag)
                {
                    *data_buf = (maps[i]->data);
                    maps[i]->lru_count++;
                    hit_num++;
                    return true;
                }
            }
        }
    }

    miss_num++;
    return false;
}

uint32_t Cache::getInsFromRAM(uint32_t addr)
{
    uint32_t insVal = arb->getInstruction(addr);
    updateCache(addr, insVal);

    return insVal;
}

uint32_t Cache::getDataFromRAM(uint32_t addr)
{
    uint32_t dataVal = arb->getData(addr);
    updateCache(addr, dataVal);

    return dataVal;
}

void Cache::setDataToRAM(uint32_t addr, uint32_t dataVal)
{
    updateCache(addr, dataVal);
    arb->setData(addr, dataVal);
}
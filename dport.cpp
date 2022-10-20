/**************************
 *
 * @file    dram.c
 *
 * @brief   This file contains dram class for DRAM
 *
 * @date    Oct 14, 2022
 *
 * @author  Vishakha Dixit
 *
 **************************/

#include "dport.h"

uint32_t dport::getData(uint32_t addr)
{
    uint32_t data;
    if ((addr >= startAddr) && (addr < endAddr))
    {
         data = (p_dram -> memory[addr] << 24)     | 
                (p_dram -> memory[addr + 1] << 16) | 
                (p_dram -> memory[addr + 2] << 8) | 
                (p_dram -> memory[addr + 3]);
    }
    else
    {
        //throw error
    }
    return data;
}

void dport::setData(uint32_t addr, uint32_t data)
{
    if ((addr >= startAddr) && (addr < endAddr))
    {
        p_dram -> memory[addr]     = (uint8_t)((data & 0xFF000000) >> 24);
        p_dram -> memory[addr + 1] = (uint8_t)((data & 0x00FF0000) >> 16);
        p_dram -> memory[addr + 2] = (uint8_t)((data & 0x0000FF00) >> 8);
        p_dram -> memory[addr + 3] = (uint8_t)(data & 0x000000FF);
    }
    else
    {
        //throw error
    }
}
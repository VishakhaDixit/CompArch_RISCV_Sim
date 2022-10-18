/**************************
 *
 * @file    dram.h
 *
 * @brief   This file contains dram class for DRAM
 *
 * @date    Oct 14, 2022
 *
 * @author  Vishakha Dixit
 *
 **************************/

#ifndef __DPORT_H__
#define __DPORT_H__

#include <stdint.h>
#include "dram.h"

class dport
{
    private:
        uint32_t startAddr;
        uint32_t endAddr;
        dram *p_dram;
    public:
        dport(dram* p_d, uint32_t dportStart, uint32_t dportEnd)
        {
            startAddr = dportStart;
            endAddr = dportEnd;
            p_dram = p_d;
        };
        uint32_t getData(uint32_t addr);
        void    setData(uint32_t addr, uint32_t data);
};

#endif
/**************************
 *
 * @file    iport.h
 *
 * @brief   This file contains dram class for DRAM
 *
 * @date    Oct 14, 2022
 *
 * @author  Vishakha Dixit
 *
 **************************/

#ifndef __IPORT_H__
#define __IPORT_H__

#include <stdint.h>
#include "dram.h"

class iport
{
    private:
        //PC should be part of CPU
        uint32_t startAddr;
        uint32_t endAddr;
        dram * p_dram;
    public:
        iport(dram* p_d, uint32_t iportStart, uint32_t iportEnd)
        {
            startAddr = iportStart;
            endAddr = iportEnd;
            p_dram = p_d;
        };
        uint32_t getInstruction(uint32_t progCount);
        
};

#endif //__IPORT_H__
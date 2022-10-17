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

class iport
{
    private:
        //PC should be part of CPU
        uint32_t startAddr;
        uint32_t endAddr;
    public:
        uint32_t getInstruction(uint32_t progCount);
        
};

#endif //__IPORT_H__
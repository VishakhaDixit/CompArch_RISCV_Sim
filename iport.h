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

#ifndef __IPORT_H__
#define __IPORT_H__

#include <stdint.h>

class iport
{
    private:
        uint32_t instCount = 0;
        uint32_t startAddr;
        uint32_t endAddr;
    public:
        uint8_t getNextInstruction();
        
};

#endif
/**************************
 *
 * @file    iport.c
 *
 * @brief   This file contains dram class for DRAM
 *
 * @date    Oct 14, 2022
 *
 * @author  Vishakha Dixit
 *
 **************************/

#include "iport.h"
#include <stdint.h>

uint32_t iport::getInstruction(uint32_t progCount)
{
    uint32_t instr;
    if(progCount < this->endAddr && progCount > this->startAddr)
    {

        instr = (p_dram -> memory[progCount] << 31)     | 
                (p_dram -> memory[progCount + 2] << 23) | 
                (p_dram -> memory[progCount + 3] << 15) | 
                (p_dram -> memory[progCount + 4]);
    }
    else
    {
        //throw error
    }

    return instr;
}
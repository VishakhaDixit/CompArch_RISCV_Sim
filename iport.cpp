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
#include <stdio.h>

uint32_t iport::getInstruction(uint32_t progCount)
{
    uint32_t instr;
    if(progCount < endAddr && progCount >= startAddr)
    {

        instr = (p_dram -> memory[progCount] << 24)     | 
                (p_dram -> memory[progCount + 1] << 16) | 
                (p_dram -> memory[progCount + 2] << 8) | 
                (p_dram -> memory[progCount + 3]);
    }
    else
    {
        //throw error
    }

    return instr;
}
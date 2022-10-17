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
    if(progCount < this.endAddr && progCount > this.startAddr)
    {

        instr = (memory[progCount] << 32) | (memory[progCount + 2] << 24) | (memory[progCount + 3] << 16) | (memory[progCount + 4])
    }
    else
    {
        //throw error
    }

    return instr;
}
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

#ifndef __DRAM_H__
#define __DRAM_H__

#include <stdint.h>
#include "iport.h"
#include "dport.h"

class dram 
{
    private:
        uint8_t memory[0x1400]; //DRAM memory
        iport ip;
        dport dp;

    public:
        iport *getInstPort();
        dport *getDataPort();
};


#endif //__DRAM_H__
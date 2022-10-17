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
#include <array>
#include "iport.h"
#include "dport.h"

class dram 
{
    private:
        std::array<uint8_t, 0x1400> memory; //DRAM memory
        iport ip;
        dport dp;

    public:
        iport *getInstPort();
        dport *getDataPort();
};


#endif //__DRAM_H__
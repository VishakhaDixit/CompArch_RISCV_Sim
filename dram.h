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

class iport;
class dport;
class dram
{
    friend iport;
    friend dport;
    protected:
        std::array<uint8_t, 0x1400> memory; //DRAM memory

    private:
        iport *ip;
        dport *dp;

    public:
        dram(uint32_t iportStart, uint32_t iportEnd, uint32_t dportStart, uint32_t dportEnd);
        iport *getInstPort();
        dport *getDataPort();
        void  initDram(uint32_t startAddr, std::array<uint8_t, 0x1400> initData);
        void  printDram();//For Demo
};


#endif //__DRAM_H__
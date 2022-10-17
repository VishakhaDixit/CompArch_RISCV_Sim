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

class dport
{
    private:
        uint32_t startAddr;
        uint32_t endAddr;
    public:
        uint32_t getData(uint32_t addr);
        void    setData(uint32_t addr, uint32_t data);
};

#endif
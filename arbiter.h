/**************************
 *
 * @file    arbiter.h
 *
 * @brief   This file contains arbiter class for DRAM access management.
 *
 * @date    Oct 29, 2022
 *
 * @author  Vishakha Dixit
 *
 **************************/

#ifndef __ARBITER_H__
#define __ARBITER_H__

#include <stdint.h>
#include <array>
#include "dram.h"
#include "mesi.h"

class arbiter
{
    private:
    dram* ram;
    bool isBusy;
    Mesi *mesi_proto;

    public:
        arbiter(dram* dr, Globals *g) : mesi_proto(new Mesi(g)){
            ram = dr;
            isBusy = false;
        };
        uint32_t getInstruction(uint32_t progCoun);
        uint32_t getData(uint32_t addr);
        void setData(uint32_t addr, uint32_t data);
        bool getBusyFlag(void);
        void setBusyFlag(bool flag);

        void processMESI(operation_type op, uint8_t cpu_id, uint32_t addr, uint32_t *clk);
};

#endif //__ARBITER_H__
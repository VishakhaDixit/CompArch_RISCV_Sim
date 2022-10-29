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

#include <stdint.h>
#include <array>
#include "dram.h"

class arbiter
{
    private:
    dram* ram;
    uint8_t cpu_id;

    public:
        arbiter(dram* dr){
            ram = dr;
        };
        uint32_t getInstruction(uint32_t progCoun);
        uint32_t getData(uint32_t addr);
        void setData(uint32_t addr, uint32_t data);
        bool getBusyFlag(void);
        void setBusyFlag(bool flag);
};
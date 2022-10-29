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
        bool getInstruction(uint8_t cpu_id, uint32_t progCoun, uint32_t& instr);
        bool getData(uint8_t cpu_id, uint32_t addr, uint32_t& data);
        bool setData(uint8_t cpu_id, uint32_t addr, uint32_t data);
};
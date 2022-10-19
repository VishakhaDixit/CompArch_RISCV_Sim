#include <iostream>
#include "dram.h"
#include "iport.h"
#include "dport.h"

dram::dram(uint32_t iportStart, uint32_t iportEnd, uint32_t dportStart, uint32_t dportEnd)
{
    ip = new iport(this, iportStart, iportEnd);
    dp = new dport(this, dportStart, dportEnd);
}

iport *dram::getInstPort()
{
    return ip;
}

dport *dram::getDataPort()
{
    return dp;
}

void dram::initDram(uint32_t startAddr, std::array<uint8_t, 0x1400> initData)
{
    std::copy(std::begin(initData), std::end(initData), std::begin(memory));
}

void dram::printDram()
{
    std::cout << "==============DRAM Dump==============" << "\n\n";
    std::cout << std::to_string(memory[0]) << "  ";
    std::cout << std::to_string(memory[1]) << "  ";
    std::cout << std::to_string(memory[2]) << "  ";
    std::cout << std::to_string(memory[3]) << "  ";
    for (uint32_t i = 4; i < 0x1400; i++)
    {
        if ((i % 4 == 0) && (i  != 0))
        {
            std::cout<< "\n";
        }
        std::cout << std::to_string(memory[i]) << "  ";
    }
}
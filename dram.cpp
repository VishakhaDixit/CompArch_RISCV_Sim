#include <iostream>
#include <sstream>
#include <iomanip>
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

void dram::printDram(uint32_t startAddr, uint32_t endAddr)
{
    std::cout << "==============DRAM Dump from " << std::hex << startAddr << " to " << std::hex << endAddr <<  "==============" << "\n\n";

    for (uint32_t i = startAddr; i < endAddr; i+=4)
    {
        std::stringstream ss;

        ss << std::hex << std::setfill('0');

        for (int j = 0; j < 4; j++) {
            ss << "0x" << std::hex << std::setw(2) << static_cast<int>(memory[i + j]) << "  ";
        }

        std::cout << ss.str() << "\n";
    }
}
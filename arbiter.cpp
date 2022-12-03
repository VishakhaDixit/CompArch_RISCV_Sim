#include "arbiter.h"
#include "iport.h"
#include "dport.h"

uint32_t arbiter::getInstruction(uint32_t progCoun)
{
    return ram->getInstPort()->getInstruction(progCoun);
}

uint32_t arbiter::getData(uint32_t addr)
{
    return ram->getDataPort()->getData(addr);
}

void arbiter::setData(uint32_t addr, uint32_t data)
{
    ram->getDataPort()->setData(addr, data);
}

bool arbiter::getBusyFlag()
{
    return isBusy;
}

void arbiter::setBusyFlag(bool flag)
{
    isBusy = flag;
}

void arbiter::processMESI(operation_type op, uint8_t cpu_id, uint32_t addr, uint32_t *clk)
{
    mesi_proto->process(op, cpu_id, addr, clk);
}

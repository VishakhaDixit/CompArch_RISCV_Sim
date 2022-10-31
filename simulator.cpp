/**************************
 *
 * @file    simulator.cpp
 *
 * @brief   This file contains definitions for Simulator class APIs.
 *
 * @date    Sept 17, 2022
 *
 * @author  Vishakha Dixit
 *
 **************************/

#include "simulator.h"
#include "iport.h"

/**************************
 * @brief       This function intializes the simulator.
 *
 * @param [in]  NULL
 *
 * @return      NULL
 **************************/
void Simulator::initSim()
{
    //Initialize Event List for first clk tick
    sys->schedule(te, getCurTick(), 0x00, "ClkGen");

    //Generate Pipeline by linking together the stages
    f->setNextStage(d);
    d->setNextStage(e);
    e->setNextStage(s);
    s->setNextStage(NULL);
}

/**************************
 * @brief       This function executes an clk event by sending an instruction from insQ to the fetch unit.
 *
 * @param [in]  NULL
 *
 * @return      NULL
 **************************/
void Simulator::process()
{
    if(!(f->isBusy()))
    {
        if (sys->flushFlag == true)
        {
            sys->flushFlag = false;
        }

        // Check if arbiter is busy
        if(!arb->getBusyFlag())
        {
            arb->setBusyFlag(true);
            uint32_t pc = getPc();

            //Fetch current instruction 
            uint32_t binInst = arb->getInstruction(pc);
            inst *i = new inst(binInst);

            sys->cpu_cpi[cpu_id] += 2;

            f->recvInst(i);

            //Increment pc 
            pc = pc + 4;
            setPc(pc);
        }
    }
        
    sys->schedule(te, sys->getCurTick()+1, 0x00, "ClkGen");
}
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

/**************************
 * @brief       This function initializes the Instruction queue with ins to be executed.
 *
 * @param [in]  NULL
 *
 * @return      NULL
 **************************/
void Simulator::initInsQ()
{
    for(uint32_t val : instructions)
    {
        inst *i = new inst(val);
        insQ.push_back(i);
    }
}

/**************************
 * @brief       This function intializes the simulator.
 *
 * @param [in]  NULL
 *
 * @return      NULL
 **************************/
void Simulator::initSim()
{
    //Init instructions in insQ
    if(insQ.size() == 0)
    {
        initInsQ();
    }
    
    //Initialize registers x1 & x2
    sys->regMap["x1"] = 20;
    sys->regMap["x2"] = 0;

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
        //Fetch current instruction from front of the instruction queue
        inst *i = insQ[0];
        f->recvInst(i);

        //Pop currently fetched instruction from the queue
        insQ.erase(insQ.begin());
        //Schedule next instruction at the end of insQ
        insQ.push_back(i);
    }
        
    sys->schedule(te, sys->getCurTick()+1, 0x00, "ClkGen");
}
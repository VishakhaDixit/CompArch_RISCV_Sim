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

        uint32_t pc = getPc();
        uint32_t data_buf = 0;

        //Get Instruction from Cache on Hit
        if(iCache->getData(pc, &data_buf))
        {
            uint32_t binInst = data_buf;
            inst *i = new inst(binInst);

            sys->cpu_sim_ticks_per_ins[cpu_id] += 3;
            sys->totalSimTicks += 3;
            sys->totalInsExecuted[cpu_id]++;
            sys->cpu_clk_ticks_per_ins[cpu_id]++;

            f->recvInst(i);

            //Increment pc 
            pc = pc + 4;
            setPc(pc);           
        }
        // On Cache miss
        else
        {
            //Get data from RAM is arbiter is not busy
            if(!iCache->isArbBusy())
            {
                iCache->setArbBusy(true);

                uint32_t binInst = iCache->getInsFromRAM(pc);
                inst *i = new inst(binInst);

                sys->cpu_sim_ticks_per_ins[cpu_id] += 100;
                sys->totalSimTicks += 100;
                sys->totalInsExecuted[cpu_id]++;
                sys->cpu_clk_ticks_per_ins[cpu_id] += 10;

                f->recvInst(i);

                //Increment pc 
                pc = pc + 4;
                setPc(pc); 
            }
        }
    }
        
    sys->schedule(te, sys->getCurTick()+1, 0x00, "ClkGen");
}
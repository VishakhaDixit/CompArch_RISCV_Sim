#include "simulator.h"

void Simulator::initInsQ()
{
    for(string val : instructions)
    {
        inst *i = new inst();
        i->setInst(val);
        i->setCst(i->getStallTime(val));
        insQ.push_back(i);
    }
}

void Simulator::initSim()
{
    //Init instructions in insQ
    if(insQ.size() == 0)
    {
        initInsQ();
    }
    //Initialize Event List for first clk tick
    sys->schedule(te, getCurTick());

    //Generate Pipeline by linking together the stages
    f->setNextStage(d);
    d->setNextStage(e);
    e->setNextStage(s);
    s->setNextStage(NULL);
}

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
        
    sys->schedule(te, sys->getCurTick()+1);
}
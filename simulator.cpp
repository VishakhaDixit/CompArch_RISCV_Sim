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
        int clk = sys->getCurTick()%5;
        f->recvInst(insQ[clk]);
        sys->schedule(te, sys->getCurTick()+1);
    }
}
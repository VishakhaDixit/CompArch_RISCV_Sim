/**************************
 *
 * @file    pipeline.cpp
 *
 * @brief   This file contains definitions for APIs related to fetch, decode, execute, & store classes.
 *
 * @date    Sept 17, 2022
 *
 * @author  Vishakha Dixit
 *
 **************************/
#include <iostream>
#include "pipeline.h"

using namespace std;

void fetch::recvInst(inst *i)
{
    cout << " Fetch: " << i->getInst();
    curInst = i;

    //schedule new event for fetch stage
    sys->schedule(fe,sys->getCurTick()+1);
}

void fetch::process()
{
    //Send fetched instruction to next stage
    if(!nextStage->isBusy())
    {
        sendInst(curInst);
    }
    else
    {
        schedule(fe,sys->getCurTick()+1);
    }
}

void decode::recvInst(inst * i)
{
    cout << " Decode: " << i->getInst();
    curInst = i;

    //schedule new event for decode stage
    sys->schedule(de,sys->getCurTick()+1);
}


void decode::process()
{
    //Send decoded instruction to next stage
    if(!nextStage->isBusy())
    {
        sendInst(curInst);
    }
    else
    {
        schedule(de,sys->getCurTick()+1);
    }
}

void execute::recvInst(inst * i)
{
    cout << " Execute: " << i->getInst();
    curInst = i;

    //schedule new event for execute stage
    sys->schedule(ee,sys->getCurTick()+1);
}


void execute::process()
{
    //Send executed instruction to next stage
    if(!nextStage->isBusy())
    {
        sendInst(curInst);
    }
    else
    {
        schedule(ee,sys->getCurTick()+1);
    }
}

void store::recvInst(inst * i)
{
    cout << " Store: " << i->getInst();
    curInst = i;

    //schedule new event for store stage
    sys->schedule(se,sys->getCurTick()+1);
}


void store::process()
{
    //Delete pipelined instruction after write back.
    curInst = NULL;
}
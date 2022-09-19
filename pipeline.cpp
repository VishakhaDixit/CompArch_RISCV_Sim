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
    cout << " Fetch: " << i->getInst() << endl;
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
        sys->schedule(fe,sys->getCurTick()+1);
        cout << " Fetch: " << curInst->getInst() << endl;
    }
}

void decode::recvInst(inst * i)
{
    cout << " Decode: " << i->getInst() << ",";
    curInst = i;

    //schedule new event for decode stage
    sys->schedule(de,sys->getCurTick()+1);
}

void decode::decodeInst()
{
    string str = curInst->getInst();
    int i = 0, j = 0;
    vector<string> ins;
    
    while(j < str.length())
    {
        while(str[j] != ' ' && j != str.length())
        {
            j++;
        }
        ins.push_back(str.substr(i, j-i));
        j++;
        i = j;
    }

    curInst->opcode = ins[0];

    for(int c = 1; c < ins.size(); c++)
        curInst->oprand.push_back(ins[c]);
}

void decode::process()
{
    //Send decoded instruction to next stage
    if(!nextStage->isBusy())
    {
        this->decodeInst();
        if(curInst->getCst() > 0)
        {
            inst *i = new inst();
            int stall = curInst->getCst();
            sendInst(curInst);
            
            //Set NOP for stall period
            i->setInst("NOP");
            i->setCst(stall-1);
            this->curInst = i;

            //Schedule NOP as next instruction
            sys->schedule(de,sys->getCurTick()+1);
            cout << " Decode: " << curInst->getInst() << ",";

            return;
        }
        sendInst(curInst);
    }
    else
    {
        sys->schedule(de,sys->getCurTick()+1);
    }
}

void execute::recvInst(inst * i)
{
    cout << " Execute: " << i->getInst() << ",";
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
        sys->schedule(ee,sys->getCurTick()+1);
    }
}

void store::recvInst(inst * i)
{
    cout << " Store: " << i->getInst() << ",";
    curInst = i;

    //schedule new event for store stage
    sys->schedule(se,sys->getCurTick()+1);
}


void store::process()
{
    //Delete pipelined instruction after write back.
    curInst = NULL;
}
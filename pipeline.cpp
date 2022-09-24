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

/**************************
 * @brief       This function returns the data value from Register.
 *
 * @param [in]  int id: index value of oprand.
 *
 * @return      int:    data value
 **************************/
int pipeline::getData(int id)
{
    int val;
    string str = curInst->getOprand(id);

    if(curInst->getOprand(id) == "x1" || curInst->getOprand(id) == "x2" || curInst->getOprand(id) == "x3" || curInst->getOprand(id) == "x4")
        val = sys->regMap[str];
    else
        val = stoi(str);

    return val;
}

/**************************
 * @brief       This function receives instruction for fetch unit & schedules it for execution.
 *
 * @param [in]  inst *i:    Instruction to be fetched.
 *
 * @return      NULL
 **************************/
void fetch::recvInst(inst *i)
{
    if(flushFlag == true)
    {
        cout << " Fetch: NOP";
        return;
    }
    cout << " Fetch: " << i->getInst() << endl;
    curInst = i;

    //schedule new event for fetch stage
    sys->schedule(fe,sys->getCurTick()+1, curInst->getInst(), "fetch");
}

/**************************
 * @brief       This function processes received ins by sending it to Decode unit if pipeline is not busy.
 *
 * @param [in]  NULL
 *
 * @return      NULL
 **************************/
void fetch::process()
{
    //Send fetched instruction to next stage
    if(!nextStage->isBusy())
    {
        sendInst(curInst);
    }
    else
    {
        sys->schedule(fe,sys->getCurTick()+1, curInst->getInst(), "fetch");
        cout << " Fetch: " << curInst->getInst() << endl;
    }
}

/**************************
 * @brief       This function receives instruction for decode unit & schedules it for execution.
 *
 * @param [in]  inst *i:    Instruction to be decoded.
 *
 * @return      NULL
 **************************/
void decode::recvInst(inst * i)
{
    if(flushFlag == true)
    {
        cout << " Decode: NOP";
        return;
    }
    cout << " Decode: " << i->getInst();
    curInst = i;

    //schedule new event for decode stage
    sys->schedule(de,sys->getCurTick()+1, curInst->getInst(), "decode");
}

/**************************
 * @brief       This function decodes the received ins by identifying the opcode & oprand.
 *
 * @param [in]  NULL
 *
 * @return      NULL
 **************************/
void decode::decodeInst()
{
    string str = curInst->getInst();

    if(str == "NOP")
    {
        return;
    }
    else
    {
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

        curInst->setOpcode(ins[0]);

        for(int c = 1; c < ins.size(); c++)
            curInst->insertOprand(ins[c]);
    }
}

/**************************
 * @brief       This function processes decoded ins by sending it to Execute unit if pipeline is not busy.
 *              It also insert NOP ins to stall the pipeline based on time needed for ins to execute.
 *
 * @param [in]  NULL
 *
 * @return      NULL
 **************************/
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
            string curOp = curInst->getInst();
            sys->schedule(de,sys->getCurTick()+1,  curOp.substr(0, curOp.find(" ")), "decode");
            cout << " Decode: " << curInst->getInst() << ",";

            return;
        }
        sendInst(curInst);
    }
    else
    {
        sys->schedule(de,sys->getCurTick()+1, curInst->getInst(), "execute");
    }
}

/**************************
 * @brief       This function receives instruction for Execute unit & schedules it for execution.
 *
 * @param [in]  inst *i:    Instruction to be executed.
 *
 * @return      NULL
 **************************/
void execute::recvInst(inst * i)
{
    if(flushFlag == true)
    {
        cout << " Execute: NOP";
        return;
    }
    curInst = i;
    if(curInst->getInst() == "NOP")
        cout << " Execute: " << i->getInst();
    else if(curInst->getOpcode() == "bne")
        cout << " Execute: " << i->getOpcode() << " " << this->getData(0) << "," << this->getData(1);
    else
        cout << " Execute: " << i->getOpcode() << " " << i->getOprand(0) << "," << this->getData(1) << "," << this->getData(2);

    //schedule new event for execute stage
    sys->schedule(ee,sys->getCurTick()+1, curInst->getInst(), "execute");
}

/**************************
 * @brief       This function performs intended operation on oprands based on the opcodes received.
 *
 * @param [in]  NULL
 *
 * @return      NULL
 **************************/
void execute::executeInst()
{
    int val1, val2, result;
    string op = curInst->getOpcode();
    
    if(op == "ld" || op == "add.d" || op == "sd" || op == "addi")
    {
        val1 = this->getData(1);
        val2 = this->getData(2);

        result = val1 + val2;
        string resReg = curInst->getOprand(0);
        sys->regMap[resReg] = result;
    }
    else if(op == "bne")
    {
        val1 = this->getData(0);
        val2 = this->getData(1);

        if(val1 == val2)
        {
            flushFlag = true;
            sys->flushMEQ();
        }
        return;
    }
}

/**************************
 * @brief       This function executes the received instruction & sends it to Store stage for write back.
 *
 * @param [in]  NULL
 *
 * @return      NULL
 **************************/
void execute::process()
{
    //Send executed instruction to next stage
    if(!nextStage->isBusy())
    {
        if(curInst->getInst() != "NOP")
            this->executeInst();
        if(flushFlag == false)
            sendInst(curInst);
    }
    else
    {
        sys->schedule(ee,sys->getCurTick()+1, curInst->getInst(), "execute");
    }
}

/**************************
 * @brief       This function receives instruction for Store unit & schedules it for execution.
 *
 * @param [in]  inst *i:    Instruction to be written back.
 *
 * @return      NULL
 **************************/
void store::recvInst(inst * i)
{
    if(flushFlag == true)
    {
        cout << " Store: NOP";
        sys->flushMEQ();
        return;
    }
    curInst = i;
    if(curInst->getInst() == "NOP" || curInst->getOpcode() == "bne")
        cout << " Store: " << "NOP";
    else
        cout << " Store: " << i->getOpcode() << " " << i->getOprand(0) << "," << this->getData(1) << "," << this->getData(2);

    //schedule new event for store stage
    sys->schedule(se,sys->getCurTick()+1, curInst->getInst(), "store");
}

/**************************
 * @brief       This function deletes the executed instruction from pipeline.
 *
 * @param [in]  NULL
 *
 * @return      NULL
 **************************/
void store::process()
{
    //Delete pipelined instruction after write back.
    curInst = NULL;
}
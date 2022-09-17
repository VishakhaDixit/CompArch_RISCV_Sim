/**************************
 *
 * @file    inst.h
 *
 * @brief   This file contains Event class with mehtods for an event.
 *
 * @date    Sept 17, 2022
 *
 * @author  Vishakha Dixit
 *
 **************************/

#ifndef __INST_H__
#define __INST_H__

#include <string>

using namespace std;

class inst
{
    private:
        string instruction;

    public:
        string getInst() { return instruction; }
        void setInst(string i) { instruction = i; }
};

#endif //__INST_H__
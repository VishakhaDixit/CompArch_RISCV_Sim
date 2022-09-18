/**************************
 *
 * @file    inst.h
 *
 * @brief   This file contains inst class with mehtods for an instruction.
 *
 * @date    Sept 17, 2022
 *
 * @author  Vishakha Dixit
 *
 **************************/

#ifndef __INST_H__
#define __INST_H__

#include <string>
#include <unordered_map>

#define MAX_INS (5)

using namespace std;

class inst
{
    private:
        string instruction;
        int cst;                                        //Current stall tick
        unordered_map<string, int> stallList = {        //Stall tick per instruction
            {"fld f0,0(x1)", 1},
            {"fadd.d f4,f0,f2", 2},
            {"fsd f4,0(x1)", 0},
            {"addi x1,x1,-8", 0},
            {"bne x1,x2", 0}
        };

    public:
        string getInst() { return instruction; }
        void setInst(string i) { instruction = i; }
        int getCst() { return cst; }
        void setCst(int c) { cst = c; }
        int getStallTime(string i) { return stallList[i]; }
};

#endif //__INST_H__
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
    protected:
        string instruction;
        int cst;                                        //Current stall tick        
        string opcode;
        vector<string> oprand;

    public:
        string getInst() { return instruction; }
        void setInst(string i) { instruction = i; }
        int getCst() { return cst; }
        void setCst(int c) { cst = c; }
        void setOpcode(string op) { opcode = op; }
        string getOpcode() { return opcode; }
        void insertOprand(string op) { oprand.push_back(op); }
        string getOprand(int i) { return oprand[i]; }
        int getTotalOprands() { return oprand.size(); }
};

#endif //__INST_H__
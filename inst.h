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

#define MAX_INS (5)

using namespace std;

class inst
{
    protected:
        int cst;             //Current stall tick        
        uint32_t binIns;    //  Binary Instruction
        int32_t opcode;
        int32_t rd, func3, func7, rs1, rs2, shamt, imm12b, imm20b;
        string insType;
        uint32_t result;

    public:
        // Control Signals are initially zero.
        int Regdst, jump, branch, memread, memtoreg, aluop, memwrite, alusrc, regwrite, PcToReg, RegToPc;
    
        inst(uint32_t data) : binIns(data) {
            uint8_t Regdst = 0;
            uint8_t jump = 0;
            uint8_t branch = 0;
            uint8_t memread = 0; 
            uint8_t memtoreg = 0;
            uint8_t aluop = 0; 
            uint8_t memwrite = 0; 
            uint8_t alusrc = 0; 
            uint8_t regwrite = 0; 
            uint8_t PcToReg = 0; 
            uint8_t RegToPc = 0;
        };

        uint32_t getInst() { return binIns; }
        void    setInst(uint32_t i) { binIns = i; }
        string  getInsType() { return insType; }
        void    setInsType(string i) { insType = i; }
        int     getCst() { return cst; }
        void    setCst(int i) { cst = i; }
        void    setOpcode(int32_t op) { opcode = op; }
        int32_t getOpcode() { return opcode; }
        int32_t getrd() { return rd; }
        void    setrd(int32_t data) { rd = data; }
        int32_t getfunc3() { return func3; }
        int32_t getrs1() { return rs1; }
        int32_t getrs2() { return rs2; }
        int32_t getfunc7() { return func7; }
        int32_t getimm12b() { return imm12b; }
        int32_t getimm20b() { return imm20b; }
        int32_t getshamt() { return shamt; }
        void    setfunc3(int32_t i) { func3 = i; }
        void    setrs1(int32_t i) { rs1 = i; }
        void    setrs2(int32_t i) { rs2 = i; }
        void    setfunc7(int32_t i) { func7 = i; }
        void    setshamt(int32_t i) { shamt = i; }
        void    setimm12b(int32_t i) { imm12b = i; }
        void    setimm20b(int32_t i) { imm20b = i; }   
        int32_t getResult() { return result; }
        void    setresult(int32_t data) { result = data; }
};

#endif //__INST_H__
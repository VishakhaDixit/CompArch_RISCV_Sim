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
        return;
    }
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
        return;
    }
    curInst = i;
    std::cout << "Decode unit received instruction " << i->getInst() << endl;

    //schedule new event for decode stage
    sys->schedule(de,sys->getCurTick()+1, curInst->getInst(), "decode");
}

/**************************
 * @brief       This function decodes the received ins by identifying the opcode & oprand.
 *              There are 6 Types of Instructions - R Type, I Type, J Type, S Type, B Type, U Type
 *
 * @param [in]  NULL
 *
 * @return      NULL
 **************************/
void decode::decodeInst()
{
    int32_t opcode, rd, func3, func7, rs1, rs2, shamt, imm12b, imm20b;
    unsigned bit20, bit10_1, bit11, bit19_12, bit4_1, bit10_5, bit12, bit4_0, bit11_5;
    uint32_t binIns = curInst->getInst();

    curInst->setresult(0);
    int opMask = 6;             
    opMask = (1 << opMask)-1;     // First 6 bits represents opcode.

    opcode = binIns & opMask;

    switch (opcode)
    {
    case 0x37:      
        // LUI - U Type
        // 0-6 Opcode, 7-11 rd, 20-31 Immediate value.
        rd = (((1 << 5) - 1) & (binIns >> 7));
        imm20b = (((1 << 20) - 1) & (binIns >> 12));
        break;

    case 0x17:     
        //AUIPC - Add Upper immediate to program counter - U Type
        // 0-6 Opcode, 7-11 rd, 20-31 Immediate value.
        rd = (((1 << 5) - 1) & (binIns >> 7));
        imm20b = (((1 << 20) - 1) & (binIns >> 12));
        break;    
    
    case 0x6F :     
        //JAL - Jump & Link - J Type
        // 0-6 Opcode, 7-11 rd, 12-31 Immediate value.
        rd = (((1 << 5) - 1) & (binIns >> 7));
        bit20 = (binIns & (1<<31)) != 0;
        bit10_1 = (((1 << 10) - 1) & (binIns >> 21));
        bit11 = (binIns & (1<<20)) != 0;
        bit19_12 = (((1 << 8) - 1) & (binIns >> 12)); 
        imm20b = (bit20 << 8) | bit19_12;
        imm20b = (imm20b << 1) | bit11;
        imm20b = (imm20b << 9) | bit10_1;
        imm20b = imm20b << 1;       //add on last bit 0
        break;

    case 0x67 :     
        //JALR - I Type
        // 0-6 Opcode, 7-11 rd, 12-14 func3 = 0, 15-19 rs1, 20-31 Immediate value.
        rd = (((1 << 5) - 1) & (binIns >> 7));
        func3 = 0;
        rs1 = (((1 << 5) - 1) & (binIns >> 15));
        imm12b = (((1 << 12) - 1) & (binIns >> 20));
        break;

    case 0x63 :     
        //BEQ, BNE, BLT, BGE, BLTU, BGEU - B Type
        // 0-6 Opcode, 7-11 Immediate value, 12-14 func3 = 0,1-7, 15-19 rs1, 20-24 rs2, 25-31 Immediate value.
        bit11 = (binIns & (1 << 7)) != 0;
        bit4_1 = (((1 << 4) - 1) & (binIns >> 8));
        func3 = (((1 << 3) - 1) & (binIns >> 12));
        rs1 = (((1 << 5) - 1) & (binIns >> 15));
        rs2 = (((1 << 5) - 1) & (binIns >> 20));
        bit10_5 = (((1 << 6) - 1) & (binIns >> 25));
        bit12 = (binIns & (1<<31)) != 0;
        imm12b = (bit12 << 1) | bit11;
        imm12b = (imm12b << 6) | bit10_5;
        imm12b = (imm12b << 4) | bit4_1;
        //add on last zero
        imm12b = imm12b << 1;
        break;

    case 0x3 :      
        //LB, LH, LW, LBU, LHU - I Type
        // Loads a value from imm bytes displaced of the contents of rs1.
        // 0-6 Opcode, 7-11 rd, 12-14 func3 = 0|1|2|4|5, 15-19 rs1, 20-31 Immediate value.
        rd = (((1 << 5) - 1) & (binIns >> 7));
        func3 = (((1 << 3) - 1) & (binIns >> 12));
        rs1 = (((1 << 5) - 1) & (binIns >> 15));
        imm12b = (((1 << 12) - 1) & (binIns >> 20));
        break;

    case 0x23 :     
        //SB, SH, SW - S Type
        // 0-6 Opcode, 7-11 Immediate value, 12-14 func3 values between 0-2, 15-19 rs1, 20-24 rs2, 25-31 Immediate value.
        bit4_0 = (((1 << 5) - 1) & (binIns >> 7));
        func3 = (((1 << 3) - 1) & (binIns >> 12));
        rs1 = (((1 << 5) - 1) & (binIns >> 15));
        rs2 = (((1 << 5) - 1) & (binIns >> 20));
        bit11_5 = (((1 << 7) - 1) & (binIns >> 25));
        imm12b = (bit11_5 << 5) | bit4_0;
        break;

    case 0x13 :     
        //ADDI, SLTI, SLTIU, XORI, ORI, ANDI - I Type for ALU operations
        // 0-6 Opcode, 7-11 rd, 12-14 func3 values between 0-7, 15-19 rs1, 20-31 Immediate value.
        // SLLI, SRLI, SRAI - I Type
        // 0-6 Opcode, 7-11 rd, 12-14 func3 values between 0-7, 15-19 rs1, 20-24 shamt, 25-31 func7.
        rd = (((1 << 5) - 1) & (binIns >> 7));
        func3 = (((1 << 3) - 1) & (binIns >> 12));
        rs1 = (((1 << 5) - 1) & (binIns >> 15));
        shamt = (((1 << 5) - 1) & (binIns >> 20));
        func7 = (((1 << 7) - 1) & (binIns >> 25));
        imm12b = (((1 << 12) - 1) & (binIns >> 20));
        
        if (imm12b > 2048) 
        {    
            //this immediate is signed so we must flip
            imm12b *= -1;
        }
        
        break;

    case 0x33 :     
        //ADD, SUB, SLL, SLT, SLTU, XOR, SRL, SRA, OR, AND - R Type
        // 0-6 Opcode, 7-11 rd, 12-14 func3 values between 0-7, 15-19 rs1, 20-24 rs2, 25-31 func7.
        // func7 differentiates between adding, subtracting, arithmatic shifting, logic shifting.
        rd = (((1 << 5) - 1) & (binIns >> 7));
        func3 = (((1 << 3) - 1) & (binIns >> 12));
        rs1 = (((1 << 5) - 1) & (binIns >> 15));
        rs2 = (((1 << 5) - 1) & (binIns >> 20));
        func7 = (((1 << 7) - 1) & (binIns >> 25));
        break;

    case 0x7 :      
        //FLW - To load floating point value from memory to rd.
        // 0-6 Opcode, 7-11 rd, 12-14 func3 values between 0-7, 15-19 rs1, 20-31 Immediate value.
        rd = (((1 << 5) - 1) & (binIns >> 7));
        func3 = (((1 << 3) - 1) & (binIns >> 12));
        rs1 = (((1 << 5) - 1) & (binIns >> 15));
        imm12b = (((1 << 12) - 1) & (binIns >> 20));
        break;

    case 0x27 :     
        //FSW - To store floating point value from rd to memory.
        // 0-6 Opcode, 7-11 rd, 12-14 func3 values between 0-7, 15-19 rs1, 20-31 Immediate value.
        bit4_0 = (((1 << 5) - 1) & (binIns >> 7));
        func3 = (((1 << 3) - 1) & (binIns >> 12));
        rs1 = (((1 << 5) - 1) & (binIns >> 15));
        rs2 = (((1 << 5) - 1) & (binIns >> 20));
        bit11_5 = (((1 << 7) - 1) & (binIns >> 25));
        imm12b = (bit11_5 << 5) | bit4_0;
        break;

    case 0x43 :     
        //FMADD.S  
        // 0-6 Opcode, 7-11 rd, 12-14 func3 values between 0-7, 15-19 rs1, 20-24 rs2, 25-31 func7.
        rd = (((1 << 5) - 1) & (binIns >> 7));
        func3 = (((1 << 3) - 1) & (binIns >> 12));
        rs1 = (((1 << 5) - 1) & (binIns >> 15));
        rs2 = (((1 << 5) - 1) & (binIns >> 20));
        func7 = (((1 << 7) - 1) & (binIns >> 25));
        break;

    case 0x47 :     
        //FMSUB.S
        // 0-6 Opcode, 7-11 rd, 12-14 func3 values between 0-7, 15-19 rs1, 20-24 rs2, 25-31 func7.
        rd = (((1 << 5) - 1) & (binIns >> 7));
        func3 = (((1 << 3) - 1) & (binIns >> 12));
        rs1 = (((1 << 5) - 1) & (binIns >> 15));
        rs2 = (((1 << 5) - 1) & (binIns >> 20));
        func7 = (((1 << 7) - 1) & (binIns >> 25));
        break;

    case 0x4B :     
        //FNMSUB.S
        // 0-6 Opcode, 7-11 rd, 12-14 func3 values between 0-7, 15-19 rs1, 20-24 rs2, 25-31 func7.
        rd = (((1 << 5) - 1) & (binIns >> 7));
        func3 = (((1 << 3) - 1) & (binIns >> 12));
        rs1 = (((1 << 5) - 1) & (binIns >> 15));
        rs2 = (((1 << 5) - 1) & (binIns >> 20));
        func7 = (((1 << 7) - 1) & (binIns >> 25));
        break;

    case 0x4F :     
        //FNMADD.S
        // 0-6 Opcode, 7-11 rd, 12-14 func3 values between 0-7, 15-19 rs1, 20-24 rs2, 25-31 func7.
        rd = (((1 << 5) - 1) & (binIns >> 7));
        func3 = (((1 << 3) - 1) & (binIns >> 12));
        rs1 = (((1 << 5) - 1) & (binIns >> 15));
        rs2 = (((1 << 5) - 1) & (binIns >> 20));
        func7 = (((1 << 7) - 1) & (binIns >> 25));
        break;

    case 0x53 :     
        //Rest of RV32F instructions
        // 0-6 Opcode, 7-11 rd, 12-14 func3 values between 0-7, 15-19 rs1, 20-24 rs2, 25-31 func7.
        rd = (((1 << 5) - 1) & (binIns >> 7));
        func3 = (((1 << 3) - 1) & (binIns >> 12));
        rs1 = (((1 << 5) - 1) & (binIns >> 15));
        rs2 = (((1 << 5) - 1) & (binIns >> 20));
        func7 = (((1 << 7) - 1) & (binIns >> 25));
        break;

    default:
        break;
    }

    curInst->setOpcode(opcode);
    curInst->setrd(rd);
    curInst->setfunc3(func3);
    curInst->setfunc7(func7);
    curInst->setrs1(rs1);
    curInst->setrs2(rs2);
    curInst->setshamt(shamt);
    curInst->setimm12b(imm12b);
    curInst->setimm20b(imm20b);
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

        switch(curInst->getOpcode())
        {
            case 0x37:
                cout << "Decode unit received opcode: LUI" << std::endl;
                break;
            case 0x17:
                cout << "Decode unit received opcode: AUIPC" << std::endl;
                break;   
            case 0x6F:
                cout << "Decode unit received opcode: JAL" << std::endl;
                break;    
            case 0x67:
                cout << "Decode unit received opcode: JALR" << std::endl;
                break;       
            case 0x63:
                switch (curInst->getfunc3())
                {
                    case 0:
                        cout << "Decode unit received opcode: BEQ" << std::endl;
                        break;
                    case 1:
                        cout << "Decode unit received opcode: BNE" << std::endl;
                        break;
                    case 4:
                        cout << "Decode unit received opcode: BLT" << std::endl;
                        break;
                    case 5:
                        cout << "Decode unit received opcode: BGT" << std::endl;
                        break;
                    case 6:
                        cout << "Decode unit received opcode: BLTU" << std::endl;
                        break;
                    case 7:
                        cout << "Decode unit received opcode: BGEU" << std::endl;
                        break;
                    default:
                        break;
                }
                break;
            case 0x3:
                cout << "Decode unit received opcode: LW" << std::endl;
                break;
            case 0x23:
                cout << "Decode unit received opcode: SW" << std::endl;
                break;
            case 0x13:
                switch (curInst->getfunc3())
                {
                    case 0:
                        cout << "Decode unit received opcode: ADDI" << std::endl;
                        break;
                    case 1:
                        cout << "Decode unit received opcode: SLLI" << std::endl;
                        break;
                    case 2:
                        cout << "Decode unit received opcode: SLTI" << std::endl;
                        break;
                    case 3:
                        cout << "Decode unit received opcode: SLTIU" << std::endl;
                        break;
                    case 4:
                        cout << "Decode unit received opcode: XORI" << std::endl;
                        break;
                    case 5:
                        cout << "Decode unit received opcode: SRLI" << std::endl;
                        break;                        
                    case 6:
                        cout << "Decode unit received opcode: ORI" << std::endl;
                        break;
                    case 7:
                        cout << "Decode unit received opcode: ANDI" << std::endl;
                        break;
                    default:
                        break;
                }
                break;
            case 0x33:
                switch (curInst->getfunc3())
                {
                    case 0:
                        cout << "Decode unit received opcode: ADD" << std::endl;
                        break;
                    case 1:
                        cout << "Decode unit received opcode: SLL" << std::endl;
                        break;
                    case 2:
                        cout << "Decode unit received opcode: SLT" << std::endl;
                        break;
                    case 3:
                        cout << "Decode unit received opcode: SLTU" << std::endl;
                        break;
                    case 4:
                        cout << "Decode unit received opcode: XOR" << std::endl;
                        break;
                    case 5:
                        cout << "Decode unit received opcode: SRL" << std::endl;
                        break;                        
                    case 6:
                        cout << "Decode unit received opcode: OR" << std::endl;
                        break;
                    case 7:
                        cout << "Decode unit received opcode: AND" << std::endl;
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        }

        cout << "Decode unit received rd: " << curInst->getrd() << std::endl;
        cout << "Decode unit received funct3: " << curInst->getfunc3() << std::endl;
        cout << "Decode unit received rs1: " << curInst->getrs1() << std::endl;
        cout << "Decode unit received immediate: " << curInst->getimm12b() << std::endl;
        cout << "-----------------------------------------------" << endl;
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
        cout << " Execute: NOP,";
        return;
    }
    curInst = i;

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
        if(curInst->getInst() != 0x00)
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
        cout << " Store: NOP,";
        sys->flushMEQ();
        return;
    }
    curInst = i;

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
    // Write data to destination register rd.
    // Delete pipelined instruction after write back.
    curInst = NULL;
}
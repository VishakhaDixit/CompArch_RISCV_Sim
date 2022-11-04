/**************************
 *
 * @file    main.cpp
 *
 * @brief   This program tends to implement an Event Driven Simulator with 4 stage pipeline.
 *
 * @date    Sep 10, 2022
 *
 * @author  Vishakha Dixit
 *
 **************************/

#include <iostream>
#include <array>
#include "simulator.h"
#include "dram.h"
#include "iport.h"
#include "dport.h"
#include "arbiter.h"

int main() {


	std::array<uint8_t, 0x1400> initData; 

	/*=======================CPU-0 INSTRUCTOINS BEGIN==========================*/

	// lui x7, 0x400
	initData[0] = 0x00;
	initData[1] = 0x40;
	initData[2] = 0x03;
	initData[3] = 0xB7;
	
	// lui x8, 0x800
	initData[4] = 0x00;
	initData[5] = 0x80;
	initData[6] = 0x04;
	initData[7] = 0x37;

	// lui x9, 0xC00
	initData[8] = 0x00;
	initData[9] = 0xC0;
	initData[10] = 0x04;
	initData[11] = 0xB7;

	// lui x0, 0x00
	initData[12] = 0x00;
	initData[13] = 0x00;
	initData[14] = 0x00;
	initData[15] = 0x37;

	// sw 0x00, sp
	initData[16] = 0x00;
	initData[17] = 0x07;
	initData[18] = 0xA0;
	initData[19] = 0x23;

	// lw x1, sp
	initData[20] = 0x00;
	initData[21] = 0x07;
	initData[22] = 0xA0;
	initData[23] = 0x83;

	// slli x1, 2
	initData[24] = 0x00;
	initData[25] = 0x20;
	initData[26] = 0x90;
	initData[27] = 0x93;

	// add x2, x7, x1
	initData[28] = 0x00;
	initData[29] = 0x13;
	initData[30] = 0x81;
	initData[31] = 0x33;

	// lw x3, x2
	initData[32] = 0x00;
	initData[33] = 0x01;
	initData[34] = 0x21;
	initData[35] = 0x83;

	// add x2, x8, x1
	initData[36] = 0x00;
	initData[37] = 0x14;
	initData[38] = 0x01;
	initData[39] = 0x33;

	// lw x4, x2
	initData[40] = 0x00;
	initData[41] = 0x01;
	initData[42] = 0x22;
	initData[43] = 0x03;

	// add x2, x9, x1
	initData[44] = 0x00;
	initData[45] = 0x14;
	initData[46] = 0x81;
	initData[47] = 0x33;

	// add x5, x3, x4
	initData[48] = 0x00;
	initData[49] = 0x41;
	initData[50] = 0x82;
	initData[51] = 0xB3;

	// sw x5, x2
	initData[52] = 0x00;
	initData[53] = 0x51;
	initData[54] = 0x20;
	initData[55] = 0x23;

	// srli x1, x1, 2
	initData[56] = 0x00;
	initData[57] = 0x20;
	initData[58] = 0xD0;
	initData[59] = 0x93;

	// addi x6, x1, 1
	initData[60] = 0x00;
	initData[61] = 0x10;
	initData[62] = 0x83;
	initData[63] = 0x13;

	// sw x6, sp
	initData[64] = 0x00;
	initData[65] = 0x67;
	initData[66] = 0xA0;
	initData[67] = 0x23;

	// lui x0, 255
	initData[68] = 0x00;
	initData[69] = 0x0F;
	initData[70] = 0xF0;
	initData[71] = 0x37;

	// bge x6, x0, -56
	initData[72] = 0xFC;
	initData[73] = 0x03;
	initData[74] = 0x52;
	initData[75] = 0x63;

	// RET (JALR x0,x1,0)
	initData[76] = 0x00;
	initData[77] = 0x00;
	initData[78] = 0x80;
	initData[79] = 0x67;

	/*=======================CPU-0 INSTRUCTOINS END==========================*/

	/*=======================CPU-1 INSTRUCTOINS BEGIN==========================*/

	// lui x7, 0x400
	initData[0x100] = 0x00;
	initData[0x101] = 0x40;
	initData[0x102] = 0x03;
	initData[0x103] = 0xB7;

	// lui x8, 0x800
	initData[0x104] = 0x00;
	initData[0x105] = 0x80;
	initData[0x106] = 0x04;
	initData[0x107] = 0x37;

	// lui x9, 0x1000
	initData[0x108] = 0x01;
	initData[0x109] = 0x00;
	initData[0x10A] = 0x04;
	initData[0x10B] = 0xB7;

	// lui x0, 0x00
	initData[0x10C] = 0x00;
	initData[0x10D] = 0x00;
	initData[0x10E] = 0x00;
	initData[0x10F] = 0x37;

	// sw 0x00, sp
	initData[0x110] = 0x00;
	initData[0x111] = 0x07;
	initData[0x112] = 0xA0;
	initData[0x113] = 0x23;

	// lw x1, sp
	initData[0x114] = 0x00;
	initData[0x115] = 0x07;
	initData[0x116] = 0xA0;
	initData[0x117] = 0x83;

	// slli x1, 2
	initData[0x118] = 0x00;
	initData[0x119] = 0x20;
	initData[0x11A] = 0x90;
	initData[0x11B] = 0x93;

	// add x2, x7, x1
	initData[0x11C] = 0x00;
	initData[0x11D] = 0x13;
	initData[0x11E] = 0x81;
	initData[0x11F] = 0x33;

	// lw x3, x2
	initData[0x120] = 0x00;
	initData[0x121] = 0x01;
	initData[0x122] = 0x21;
	initData[0x123] = 0x83;

	// add x2, x8, x1
	initData[0x124] = 0x00;
	initData[0x125] = 0x14;
	initData[0x126] = 0x01;
	initData[0x127] = 0x33;

	// lw x4, x2
	initData[0x128] = 0x00;
	initData[0x129] = 0x01;
	initData[0x12A] = 0x22;
	initData[0x12B] = 0x03;

	// add x2, x9, x1
	initData[0x12C] = 0x00;
	initData[0x12D] = 0x14;
	initData[0x12E] = 0x81;
	initData[0x12F] = 0x33;

	// sub x5, x3, x4
	initData[0x130] = 0x02;
	initData[0x131] = 0x41;
	initData[0x132] = 0x82;
	initData[0x133] = 0xB3;

	// sw x5, x2
	initData[0x134] = 0x00;
	initData[0x135] = 0x51;
	initData[0x136] = 0x20;
	initData[0x137] = 0x23;

	// srli x1, x1, 2
	initData[0x138] = 0x00;
	initData[0x139] = 0x20;
	initData[0x13A] = 0xD0;
	initData[0x13B] = 0x93;

	// addi x6, x1, 1
	initData[0x13C] = 0x00;
	initData[0x13D] = 0x10;
	initData[0x13E] = 0x83;
	initData[0x13F] = 0x13;

	// sw x6, sp
	initData[0x140] = 0x00;
	initData[0x141] = 0x67;
	initData[0x142] = 0xA0;
	initData[0x143] = 0x23;

	// lui x0, 255
	initData[0x144] = 0x00;
	initData[0x145] = 0x0F;
	initData[0x146] = 0xF0;
	initData[0x147] = 0x37;

	// bge x6, x0, -56
	initData[0x148] = 0xFC;
	initData[0x149] = 0x03;
	initData[0x14A] = 0x52;
	initData[0x14B] = 0x63;

	// RET (JALR x0,x1,0)
	initData[0x14C] = 0x00;
	initData[0x14D] = 0x00;
	initData[0x14E] = 0x80;
	initData[0x14F] = 0x67;

	/*=======================CPU-1 INSTRUCTOINS END==========================*/


	dram ram = dram(0x0000, 0x01FF, 0x0200, 0x13FF);
	ram.initDram(0x00, initData);

	for (uint32_t i = 0; i < 256; i++)
	{
		ram.getDataPort()->setData(0x400 + (i*4), 0x02020202);
	}
	
	for (uint32_t i = 0; i < 256; i++)
	{
		ram.getDataPort()->setData(0x800 + (i*4), 0x01010101);
	}

	arbiter *arb = new arbiter(&ram);
	
	System *sys = new System();
	Simulator *cpu0 = new Simulator(sys, arb, 0);
	cpu0->initSim();				//Initialize Simulator device.
		
	Simulator *cpu1 = new Simulator(sys, arb, 1);
	cpu1->initSim();				//Initialize Simulator device.

	sys->executeSim(200000);		//Run Simulator for 100 clk cycles, this function terminates if pipeline is flushed.


	// Calculate Total CPI 
	cout << "\nTotal CPI for CPU-0 = " << sys->cpu_cpi0/sys->getCurTick();
	cout << "\nTotal CPI for CPU-1 = " << sys->cpu_cpi1/sys->getCurTick() << endl;

	cout << "\n=======================CPU-0 RESULTS BEGIN==========================" << endl;
	ram.printDram(0xC00, 0xFFF);
	cout << "=======================CPU-0 RESULTS END============================" << endl;

	cout << "=======================CPU-1 RESULTS BEGIN==========================" << endl;
	ram.printDram(0x1000, 0x13FF);
	cout << "=======================CPU-1 RESULTS END============================" << endl;

	return 0;
}
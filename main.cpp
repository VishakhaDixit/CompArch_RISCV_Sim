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

int main() {


	std::array<uint8_t, 0x1400> initData; 

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

	dram ram = dram(0x0000, 0x01FF, 0x0200, 0x13FF);
	ram.initDram(0x00, initData);

	for (uint32_t i = 0; i < 256; i++)
	{
		ram.getDataPort()->setData(0x400 + (i*4), 0x01010101);
	}
	
	for (uint32_t i = 0; i < 256; i++)
	{
		ram.getDataPort()->setData(0x800 + (i*4), 0x02020202);
	}
	
	System *sys = new System();
	Simulator *es = new Simulator(sys, &ram);
	es->initSim();				//Initialize Simulator device.
	sys->executeSim(100);		//Run Simulator for 100 clk cycles, this function terminates if pipeline is flushed.

	return 0;
}
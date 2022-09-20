/**************************
 *
 * @file    main.cpp
 *
 * @brief   This program tends to implement an Event Driven Simulator.
 *
 * @date    Sep 10, 2022
 *
 * @author  Vishakha Dixit
 *
 **************************/

#include <iostream>
#include "simulator.h"

int main() {
	System *sys = new System();
	Simulator *es = new Simulator(sys);
	es->initSim();				//Initialize Simulator device.
	sys->executeSim(100);		//Run Simulator for 100 clk cycles, this function terminates if pipeline is flushed.
	return 0;
}
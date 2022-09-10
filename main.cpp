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
	eventSimulator *es = new eventSimulator(sys);
	es->initSim();				//Initialize Simulator device with random 20 events
	sys->executeSim(100);		//Run Simulator for 100 clk cycles
	return 0;
}
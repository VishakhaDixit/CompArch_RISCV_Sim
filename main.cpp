#include "simobject.hh"
#include <iostream>

#include "simobjecttest.hh"

int main() {
	System *sys = new System();
	SimObjectTest * sot = new SimObjectTest(sys);
	sot->initialize();			//Initialize event queue with random 20 events
	sys->runSimulation(100);	//Run Simulator for 100 clk cycles
	return 0;
}
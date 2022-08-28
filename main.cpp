#include "simobject.hh"
#include <iostream>

#include "simobjecttest.hh"

int main() {
	System *sys = new System();
	SimObjectTest * sot = new SimObjectTest(sys);
	sot->initialize();
	sys->runSimulation(100);
	return 0;
}
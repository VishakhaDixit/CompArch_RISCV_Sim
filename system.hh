#ifndef __SYSTEM_HH__
#define __SYSTEM_HH__

#include "event.hh"
#include <vector>

class System {
private:
	Tick currentTick;
	std::vector<Event *> MEQ;
	std::vector<Event *>::iterator findEvent(Event *e);
public:
	System() : currentTick(0) {}
	bool schedule(Event *e, Tick t, int v);			//Returns 1 on succesfully scheduling, 0 on failure.
	void reschedule(Event *e, Tick t, int v);
	void runSimulation(Tick endTick=-1);
	Tick currTick() { return currentTick; }
	void printMEQ();
	Event * popEvent();
};

#endif //__SYSTEM_HH__
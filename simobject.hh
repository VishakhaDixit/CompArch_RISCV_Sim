#ifndef __SIMOBJECT_HH__
#define __SIMOBJECT_HH__

#include "event.hh"
#include "system.hh"

class SimObject {
private:
	System * sys;
public:
	SimObject(System * _sys) : sys(_sys) {}
	Tick currTick() { return sys->currTick(); }
	bool schedule(Event *e, Tick t) { sys->schedule(e,t); }
	void reschedule(Event *e, Tick t) { sys->reschedule(e,t); }
	virtual void initialize() = 0;
};

#endif //__SIMOBJECT_HH__
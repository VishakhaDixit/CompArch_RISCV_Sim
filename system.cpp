#include "system.hh"
#include <iostream>
#include <cassert>

std::vector<Event *>::iterator
System::findEvent(Event *e) {
	// printMEQ();
	for (auto it = MEQ.begin(); it != MEQ.end(); it++) {
		if (*it == e) {
			std::cout << "Event found\n";
			return it;
		}
	}
	return MEQ.end();
}

bool
System::schedule(Event *e, Tick t, int v) {
	assert(t >= currentTick);
	
	e->schedule(t,v);
	for (auto it = MEQ.begin(); it != MEQ.end(); it++) {
		if (e->time() < (*it)->time()) {
			MEQ.insert(it, e);
			std::cout << "Scheduled new " << e->description() << " time = " << t << ", " << "val = " << v <<  std::endl;
			return true;
		}
		else if(e->time() == (*it)->time())
		{
			return false;
		}
	}
	MEQ.push_back(e);
	std::cout << "Scheduled new " << e->description() << " time = " << t << ", " << "val = " << v <<  std::endl;
	return true;
}

void
System::reschedule(Event *e, Tick t, int v) {
	assert(t>=currentTick);
	std::cout << "Attempting to schedule " << e->description() << " at time " << t << std::endl;
	if (t < e->time()) {
		MEQ.erase(findEvent(e));
		e->schedule(t,v);
		for (auto it = MEQ.begin(); it != MEQ.end(); it++) {
			if (e->time() < (*it)->time()) {
				MEQ.insert(it, e);
				return;
			}
		}
		MEQ.push_back(e);
	}
}

void
System::runSimulation(Tick endTick) {
	printMEQ();

	while (currentTick <= endTick) {
		std::cout << "\nSimulation Tick: " << currentTick << std::endl;
		
		while (MEQ.begin() != MEQ.end()) 
		{
			if (MEQ.front()->time() < currentTick) 
			{
				std::cout << "Event was scheduled prior to currentTick\n";
				assert(0);
			} 
			else if (MEQ.front()->time() == currentTick) 
			{
				int val = MEQ.front()->getValue();
				Event *e = popEvent();
				e->setValue(val);
				e->process();
				std::cout << "tick = " << currentTick << "," << "val = " << val << std::endl;
				
				//Generate new event time
				Tick newEventTime = 0;
				int newEventVal = e->getValue();
				bool isScheduled = false;

				while(!isScheduled)
				{
					newEventTime = currentTick + (rand() % val) +1;
					isScheduled = schedule(e, newEventTime, newEventVal);
				}
				printMEQ();
			} 
			else 
			{
				break;
			}
		}
		currentTick++;
	}
}

void
System::printMEQ() {
	std::cout << "\nStart of MEQ\n";
	for (auto e : MEQ) {
		std::cout << e->time() << ":" << e->description() << std::endl;
	}
	std::cout << "End of MEQ\n";
}

Event *
System::popEvent() {
	Event * tmp = MEQ.front();
	tmp->deschedule();
	MEQ.erase(MEQ.begin());
	return tmp;
}
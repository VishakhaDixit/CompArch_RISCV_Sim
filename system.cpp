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

void
System::schedule(Event *e, Tick t) {
	assert(t>=currentTick);
	std::cout << "Attempting to schedule " << e->description() << " at time " << t << std::endl;
	if (!(e->isScheduled())) {
		e->schedule(t);
		for (auto it = MEQ.begin(); it != MEQ.end(); it++) {
			if (e->time() < (*it)->time()) {
				MEQ.insert(it, e);
				return;
			}
		}
		MEQ.push_back(e);
	} else {
		std::cout << "ERROR: Event already scheduled. Cannot be rescheduled.\n";
		assert(0);
	}
}

void
System::reschedule(Event *e, Tick t) {
	assert(t>=currentTick);
	std::cout << "Attempting to schedule " << e->description() << " at time " << t << std::endl;
	if (e->isScheduled() && t < e->time()) {
		MEQ.erase(findEvent(e));
		e->schedule(t);
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
	while (currentTick <= endTick) {
		std::cout << "Simulation Tick: " << currentTick << std::endl;
		printMEQ();
		while (MEQ.begin() != MEQ.end()) {
			// printMEQ();
			if (MEQ.front()->time() < currentTick) {
				std::cout << "Event was scheduled prior to currentTick\n";
				assert(0);
			} else if (MEQ.front()->time() == currentTick) {
				popEvent()->process();
			} else {
				break;
			}
		}
		currentTick++;
	}
}

void
System::printMEQ() {
	std::cout << "Start of MEQ\n";
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
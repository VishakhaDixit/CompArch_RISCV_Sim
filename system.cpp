#include "system.hh"
#include <iostream>
#include <cassert>

std::vector<Event *>::iterator
System::findEvent(Event *e) 
{
	for (auto it = MEQ.begin(); it != MEQ.end(); it++) 
	{
		if (*it == e) 
		{
			std::cout << "Event found\n";
			return it;
		}
	}
	return MEQ.end();
}

void
System::schedule(Event *e, Tick t, int v) 
{
	e->schedule(t,v);

	for (auto it = MEQ.begin(); it != MEQ.end(); it++) 
	{
		if (e->time() <= (*it)->time()) 
		{
			if(e->time() == (*it)->time())
			{
				if(e->getValue() > (*it)->getValue())
					continue;
			}
			MEQ.insert(it, e);
			std::cout << "Scheduled new " << e->description() << " time = " << t << ", " << "val = " << v <<  std::endl;
			return;
		}
	}
	MEQ.push_back(e);
	std::cout << "Scheduled new " << e->description() << " time = " << t << ", " << "val = " << v <<  std::endl;
	return;
}

void
System::reschedule(Event *e, Tick t, int v) 
{
	assert(t>=currentTick);
	std::cout << "Attempting to schedule " << e->description() << " at time " << t << std::endl;
	if (t < e->time()) 
	{
		MEQ.erase(findEvent(e));
		e->schedule(t,v);
		for (auto it = MEQ.begin(); it != MEQ.end(); it++) 
		{
			if (e->time() < (*it)->time()) 
			{
				MEQ.insert(it, e);
				return;
			}
		}
		MEQ.push_back(e);
	}
}

void
System::runSimulation(Tick endTick) 
{
	printMEQ();

	while ((currentTick <= endTick) && !(MEQ.empty()))
	{
		std::cout << "\nSimulation Tick: " << currentTick << std::endl;
		
		if (MEQ.front()->time() <= currentTick) 
		{
			if (MEQ.front()->time() < currentTick)
				std::cout << "Event was scheduled prior to currentTick\n";
			
			Tick t = MEQ.front()->time();
			int v = MEQ.front()->getValue();

			//Generate new Event
			popEvent()->process(t, v);
			printMEQ();
		} 

		currentTick++;
	}
}

void
System::printMEQ() 
{
	std::cout << "\nStart of MEQ\n";
	for (auto e : MEQ) 
	{
		std::cout << e->time() << ":" << e->getValue() << std::endl;
	}
	std::cout << "End of MEQ\n";
}

Event *
System::popEvent() 
{
	Event * tmp = MEQ.front();
	tmp->deschedule();
	MEQ.erase(MEQ.begin());
	return tmp;
}
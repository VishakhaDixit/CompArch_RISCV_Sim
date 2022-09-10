/**************************
 *
 * @file    system.cpp
 *
 * @brief   This file contains definitions for System class APIs.
 *
 * @date    Sept 10, 2022
 *
 * @author  Vishakha Dixit
 *
 **************************/

#include "system.h"
#include <iostream>

/**************************
 * @brief       This function inserts the given event in the MEQ in an ordered way.
 *
 * @param [in]  Event *e: 	Event class object
 * 				TICK t: 	Event time
 * 				int v: 		Event Value
 *
 * @return      NULL
 **************************/
void System::schedule(Event *e, TICK t, int v) 
{
	e->schEve(t,v);

	for (auto i = MEQ.begin(); i != MEQ.end(); i++) 
	{
		if (e->getTime() <= (*i)->getTime()) 
		{
			if(e->getTime() == (*i)->getTime())
			{
				if(e->getValue() > (*i)->getValue())
					continue;
			}
			MEQ.insert(i, e);
			std::cout << "Scheduled new Test Event at " << " time = " << t << ", " << "val = " << v <<  std::endl;
			return;
		}
	}
	MEQ.push_back(e);
	std::cout << "Scheduled new Test Event at" << " time = " << t << ", " << "val = " << v <<  std::endl;
	return;
}

/**************************
 * @brief       This function runs the simulation upto given endClkTick.
 *
 * @param [in]  TICK endClkTick: Clk tick upto which simulator will execute.
 *
 * @return      NULL
 **************************/
void System::executeSim(TICK endClkTick) 
{
	displayMEQ();

	while ((getCurTick() <= endClkTick) && !(MEQ.empty()))
	{
		std::cout << "\nSimulation Tick: " << getCurTick() << std::endl;
		
		if (MEQ.front()->getTime() <= getCurTick()) 
		{
			if (MEQ.front()->getTime() < getCurTick())
				std::cout << "Event was scheduled prior to currentTick\n";
			
			TICK t = MEQ.front()->getTime();
			int v = MEQ.front()->getValue();

			//Generate new Event
			popEve()->process(t, v);
			displayMEQ();
		} 

		curClkTick++;
	}
}

/**************************
 * @brief       This function displays the contents of MEQ.
 *
 * @param [in]  NULL
 *
 * @return      NULL
 **************************/
void System::displayMEQ() 
{
	std::cout << "\nStart of MEQ\n";
	for (auto e : MEQ) 
	{
		std::cout << e->getTime() << ":" << e->getValue() << std::endl;
	}
	std::cout << "End of MEQ\n";
}

/**************************
 * @brief       This function remove the front elements of MEQ after setting it's value to default.
 *
 * @param [in]  NULL
 *
 * @return      Event *: Returns a pointer of event that has been descheduled & erased from MEQ.
 **************************/
Event *System::popEve() 
{
	Event *eve = MEQ.front();
	eve->dschEve();
	MEQ.erase(MEQ.begin());
	return eve;
}
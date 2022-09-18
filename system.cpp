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
 *
 * @return      NULL
 **************************/
void System::schedule(Event *e, TICK t) 
{
	e->schEve(t);

	for (auto i = MEQ.begin(); i != MEQ.end(); i++) 
	{
		if (e->getTime() < (*i)->getTime()) 
		{
			MEQ.insert(i, e);
			// std::cout << "Scheduled new Test Event at " << " time = " << t <<  std::endl;
			return;
		}
	}
	MEQ.push_back(e);
	// std::cout << "Scheduled new Test Event at " << " time = " << t <<  std::endl;
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
	while ((getCurTick() <= endClkTick) && !(MEQ.empty()))
	{
		std::cout << "\nSimulation Tick: " << getCurTick();
		
		while(MEQ.begin() != MEQ.end())
		{
			if (MEQ.front()->getTime() < getCurTick()) 
			{
				std::cout << "\nERROR:-Event was scheduled prior to currentTick\n";
				return;
			}
			else if(MEQ.front()->getTime() == getCurTick())
			{	
				//Generate new Event
				popEve()->process();
			}
			else
				break;
		} 

		curClkTick++;
	}
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
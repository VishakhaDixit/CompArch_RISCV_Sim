/**************************
 *
 * @file    system.h
 *
 * @brief   This file contains System class that maintains an MEQ for events scheduled for execution & contains methods to maintain the MEQ.
 *
 * @date    Sept 10, 2022
 *
 * @author  Vishakha Dixit
 *
 **************************/

#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#include "event.h"
#include <vector>

class System 
{
	private:
		TICK curClkTick;
		std::vector<Event *> MEQ;

	public:
		System() : curClkTick(0) {}
		
		void schedule(Event *e, TICK t);			
		void executeSim(TICK endClkTick=-1);
		TICK getCurTick() { return curClkTick; }
		void displayMEQ();
		Event *popEve();
};

#endif //__SYSTEM_H__
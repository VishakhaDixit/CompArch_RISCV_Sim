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
#include <unordered_map>
#include <string>

using namespace std;

class System 
{
	private:
		TICK curClkTick;
		std::vector<Event *> MEQ;

	public:
		System() : curClkTick(0) {}

		unordered_map<string, int> regMap = 
		{
			{"x1", 0},
			{"x2", 0},
			{"x3", 0},
			{"x4", 0}
		};
		
		void schedule(Event *e, TICK t);			
		void executeSim(TICK endClkTick=-1);
		TICK getCurTick() { return curClkTick; }
		void displayMEQ();
		Event *popEve();
};

#endif //__SYSTEM_H__
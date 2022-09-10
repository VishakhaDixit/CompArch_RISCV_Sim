/**************************
 *
 * @file    simulator.h
 *
 * @brief   This file contains class with mehtods for initializing and processing events for simulator.
 *
 * @date    Sept 10, 2022
 *
 * @author  Vishakha Dixit
 *
 **************************/

#ifndef __SIMULATOR_H__
#define __SIMULATOR_H__

#include <iostream>
#include <sys/time.h>
#include "system.h"
#include "event.h"

class eventSimulator : public System
{
private:
	class testEve : public Event 
	{
	private:
		eventSimulator *simDev;
	public:
		testEve(eventSimulator * es) : Event(), simDev(es) {}
		virtual void process(TICK t, int v) override { simDev->process(t, v); }
	};

	System *sys;
	testEve *e;

public:
	eventSimulator(System *_sys) : sys(_sys),  e(new testEve(this)) {}
	
	void initSim()
	{
		//(Q-1) Generate random 20 events
		uint8_t event_cnt = 0;
		TICK event_time;
		int event_val;

		time_t time_ptr;
		time_ptr = time(NULL);
	
		//Get the localtime
		tm* tm_local = localtime(&time_ptr);

		srand(time(0));

		while(event_cnt < 20)
		{
			event_time = 1 + tm_local->tm_sec;
			event_val = rand()%1000;

			sys->schedule(e, event_time, event_val);
			e = new testEve(this);
			event_cnt++;
		}
	}
	
	void process(TICK t, int v) 
	{
		//(Q-3) Generates new event.
		std::cout << "Processing: " << "tick = " << t << "," << "val = " << v << std::endl;

		t = t + (rand()% v) + 1;
		Event *e = new testEve(this);
		sys->schedule(e, t, v);
	}
};

#endif //__SIMULATOR_H__
/**************************
 *
 * @file    event.h
 *
 * @brief   This file contains Event class with mehtods for an event.
 *
 * @date    Sept 10, 2022
 *
 * @author  Vishakha Dixit
 *
 **************************/

#ifndef __EVENT_H__
#define __EVENT_H__

#include <cinttypes>

#define TICK uint64_t

class Event 
{
	private:
		TICK eveTime;
		int eveValue;
	public:
		Event() : eveTime(0), eveValue(0) { }
		
		void schEve(TICK newTime, int newVal) 
		{
			eveTime = newTime;
			eveValue = newVal;
		}
		void dschEve() 
		{
			eveTime = -1;
			eveValue = -1;
		}
		
		void setValue(int v) { eveValue = v; }
		void setTime(TICK t) { eveTime = t; }
		int getValue() { return eveValue; }
		TICK getTime() { return eveTime; }
		
		virtual void process(TICK t, int v) = 0;
};

#endif //__EVENT_H__
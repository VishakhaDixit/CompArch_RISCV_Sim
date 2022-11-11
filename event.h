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
#include <string>

#define TICK uint64_t

using namespace std;

class Event 
{
	private:
		TICK eveTime;
		uint32_t ins;
		string stage;

	public:
		Event() : eveTime(0) { }
		
		void schEve(TICK newTime, uint32_t i, string s) 
		{
			eveTime = newTime;
			ins = i;
			stage = s;
		}
		void dschEve() 
		{
			eveTime = -1;
			ins = 0;
			stage = "";
		}
		
		void setTime(TICK t) { eveTime = t; }
		TICK getTime() { return eveTime; }
		uint32_t getInst() { return ins; }
		string getStage() { return stage; }
		
		virtual void process() = 0;
};

#endif //__EVENT_H__
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
		System() : curClkTick(1) {}
        bool flushFlag = false;

		//TODO: Make this a vector for multi-cpu system.
		
		unordered_map<uint32_t, int32_t>regMap[2] = 
		{
			{
				{0, 0},
				{1, 0},
				{2, 0},
				{3, 0},
				{4, 0},
				{5, 0},
				{6, 0},
				{7, 0},
				{8, 0},
				{9, 0},
				{0xE, 0},
				{0xF, 0x200}
			},
			{
				{0, 0},
				{1, 0},
				{2, 0},
				{3, 0},
				{4, 0},
				{5, 0},
				{6, 0},
				{7, 0},
				{8, 0},
				{9, 0},
				{0xE, 0x100},
				{0xF, 0x300}
			}
		};

		// Used for displaying in terms of Simulation ticks
		uint64_t cpu_sim_ticks_per_ins[2] = {0, 0};
		uint64_t total_sim_ticks_cpu0 = 0;
		uint64_t total_sim_ticks_cpu1 = 0;
		uint64_t totalSimTicks = 1;

		// Used for Calculating CPI in terms of CPU clk.
		uint64_t totalInsExecuted[2] = {0, 0};
		uint64_t cpu_clk_ticks_per_ins[2] = {0, 0};
		uint64_t total_cpu_clk_cpu0 = 0;
		uint64_t total_cpu_clk_cpu1 = 0;
		
		void schedule(Event *e, TICK t, uint32_t i, string s);			
		void executeSim(TICK endClkTick=-1);
		TICK getCurTick() { return curClkTick; }
		void displayMEQ();
		void flushMEQ();
		Event *popEve();
};

#endif //__SYSTEM_H__
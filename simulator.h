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
#include <string>
#include "system.h"
#include "event.h"
#include "pipeline.h"
#include "inst.h"
#include "arbiter.h"

using namespace std;

class Simulator : public System
{
private:
	class testEve : public Event 
	{
	private:
		Simulator *simDev;
	public:
		testEve(Simulator * es) : Event(), simDev(es) {}
		virtual void process() override { simDev->process(); }
        void process(uint32_t addr) {}
	};

	//TODO: Add CPU ID.
	uint8_t cpu_id;
	System *sys;
	testEve *te;

	fetch *f;
	decode *d;
	execute *e;
	store *s;

	// dram *ram;
	arbiter *arb;


public:
	Simulator(System *_sys, arbiter *a, uint8_t id) : sys(_sys),  te(new testEve(this)), f(new fetch(sys, a, id)),
							d(new decode(sys, id)), e(new execute(sys, a, id)), s(new store(sys, a, id)) {
								arb = a;
								cpu_id = id;
							}
	
	void initSim();
	void process();

	uint32_t getPc() { return sys->regMap[cpu_id][0xE]; }
	void setPc(uint32_t p) { sys->regMap[cpu_id][0xE] = p; }
	uint32_t getSp() { return sys->regMap[cpu_id][0xF]; }
	void setSp(uint32_t s) { sys->regMap[cpu_id][0xF] = s; }
};

#endif //__SIMULATOR_H__
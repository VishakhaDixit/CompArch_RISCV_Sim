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
#include "cache.h"

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
	};

	//TODO: Add CPU ID.
	uint8_t cpu_id;
	System *sys;
	testEve *te;

	fetch *f;
	decode *d;
	execute *e;
	store *s;

	Cache *iCache;
	Cache *dCache;


public:
	Simulator(System *_sys, Cache *i_cache, Cache *d_cache, uint8_t id) : sys(_sys),  te(new testEve(this)), f(new fetch(sys,i_cache, id)),
							d(new decode(sys, id)), e(new execute(sys, d_cache, id)), s(new store(sys, d_cache, id)) {
								cpu_id = id;
								iCache = i_cache;
								dCache = d_cache;
							}

	// For testing purposes
	Simulator(Cache *d_cache, uint8_t id) {
		dCache = d_cache;
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
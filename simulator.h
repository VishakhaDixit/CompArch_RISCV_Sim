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
#include "dram.h"

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

	System *sys;
	testEve *te;

	vector<inst *> insQ;
	vector<uint32_t> instructions = 
	{
		0x00300193,
		0x00618193
	};

	fetch *f;
	decode *d;
	execute *e;
	store *s;

	dram *ram;


public:
	Simulator(System *_sys, dram *dr) : sys(_sys),  te(new testEve(this)), f(new fetch(sys)),
							d(new decode(sys)), e(new execute(sys, dr)), s(new store(sys, dr)) {
								ram = dr;
							}
	
	void initSim();
	void process();
	void initInsQ();

	uint32_t getPc() { return sys->regMap[0xE]; }
	void setPc(uint32_t p) { sys->regMap[0xE] = p; }
	uint32_t getSp() { return sys->regMap[0xF]; }
	void setSp(uint32_t s) { sys->regMap[0xF] = s; }
};

#endif //__SIMULATOR_H__
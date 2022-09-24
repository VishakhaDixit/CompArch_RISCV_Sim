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
	vector<string> instructions = {"ld x3 0 x1", "add.d x4 x3 x2", "sd x4 0 x1", "addi x1 x1 -4", "bne x1 x2"};
	unordered_map<string, int> stallList = {        //Stall tick per instruction
	{"ld x3 0 x1", 3},
	{"add.d x4 x3 x2", 3},
	{"sd x4 0 x1", 3},
	{"addi x1 x1 -4", 3},
	{"bne x1 x2", 2}
	};

	fetch *f;
	decode *d;
	execute *e;
	store *s;

public:
	Simulator(System *_sys) : sys(_sys),  te(new testEve(this)), f(new fetch(sys)),
							d(new decode(sys)), e(new execute(sys)), s(new store(sys)) {}
	
	void initSim();
	void process();
	void initInsQ();
};

#endif //__SIMULATOR_H__
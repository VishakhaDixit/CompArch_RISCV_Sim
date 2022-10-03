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
	vector<uint32_t> instructions = 
	{
		0x00300193,
		0x00618193,
		0x00518433,
		0x404280B3,
		0x0021C0B3,
		0x0083E7B3,
		0x00537233,
		0x00520493,
		0x0052AA13,
		0x0021C093,
		0x0083E793,
		0x00537213,
		0x005101A3,
		0x008C9223,
		0x01192203,
		0x00040203,
		0x00528063,
		0x00749063,
		0xFE834FE3,
		0xFE855FE3,
		0x000031B7,
		0x00007397
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
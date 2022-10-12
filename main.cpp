/**************************
 *
 * @file    main.cpp
 *
 * @brief   This program tends to implement an Event Driven Simulator with 4 stage pipeline.
 *
 * @date    Sep 10, 2022
 *
 * @author  Vishakha Dixit
 *
 **************************/

#include <iostream>
#include "simulator.h"

int main() {
	System *sys = new System();
	Simulator *es = new Simulator(sys);
	decode *d = new decode(sys);

	es->initInsQ();

	for(auto i : es->insQ)
	{
		d->recvInst(i);
		d->process();
	}

	return 0;
}
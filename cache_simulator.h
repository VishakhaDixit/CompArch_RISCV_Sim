#ifndef __CACHE_SIM_H__
#define __CACHE_SIM_H__

#include <vector>
#include "event.h"
#include "simulator.h"
#include "arbiter.h"
#include "globals.h"

using namespace std;

class CacheSim 
{
    private:
        typedef struct CacheEvent
        {
            operation_type op;
            Simulator *cpu;
            uint32_t addr;
        }cache_eve_t;

        vector<cache_eve_t> events;
        vector<Simulator*> cpu_list;
        vector<vector<string>> result;

        // map of addr and transitions for each cpu.
        unordered_map< uint32_t, vector<vector<string>> > state_transitions_map;

        dram *ram;
        uint8_t totalCpus;
        Globals *gb;

    public:

        CacheSim(dram *r, Globals *g, uint8_t total_cpus);

    	void initSim();
	    void process();
};


#endif //__CACHE_SIM_H__
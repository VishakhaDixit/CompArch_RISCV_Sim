#include "cache_simulator.h"

CacheSim::CacheSim(dram *r, Globals *g, uint8_t total_cpus)
{
    ram = r;
    totalCpus = total_cpus;
    gb = g;
}

void CacheSim::initSim()
{
    arbiter *arb = new arbiter(ram, gb);

    this->result.reserve(this->totalCpus);

    // Create Cpu and Cache objects
    for(uint8_t i = 0; i < totalCpus; i++)
    {
        Cache *l1Cache = new Cache(64, 4, none, arb);
        Simulator *cpu = new Simulator(l1Cache, i);
        cpu_list.push_back(cpu);
        vector<string> cpu_state = {"invalid"};
        this->result.push_back(cpu_state);
    }

    // Generate Cache events for testing
    cache_eve_t event1 = {.op=Read, .cpu=cpu_list[0], .addr=0x400};
    events.push_back(event1);
    cache_eve_t event2 = {.op=Read, .cpu=cpu_list[1], .addr=0x400};
    events.push_back(event2);
    cache_eve_t event3 = {.op=Read, .cpu=cpu_list[2], .addr=0x400};
    events.push_back(event3);
    cache_eve_t event4 = {.op=Write, .cpu=cpu_list[1], .addr=0x400};
    events.push_back(event4);
    cache_eve_t event5 = {.op=Read, .cpu=cpu_list[3], .addr=0x400};
    events.push_back(event5);
    cache_eve_t event6 = {.op=Write, .cpu=cpu_list[3], .addr=0x400};
    events.push_back(event6);
    cache_eve_t event7 = {.op=Write, .cpu=cpu_list[3], .addr=0x404};
    events.push_back(event7);
    cache_eve_t event8 = {.op=Read, .cpu=cpu_list[1], .addr=0x404};
    events.push_back(event8);
    cache_eve_t event9 = {.op=Read, .cpu=cpu_list[1], .addr=0x404};
    events.push_back(event9);
    cache_eve_t event10 = {.op=Write, .cpu=cpu_list[1], .addr=0x404};
    events.push_back(event10);
    cache_eve_t event11 = {.op=Write, .cpu=cpu_list[1], .addr=0x408};
    events.push_back(event11);
}

void CacheSim::process()
{
    uint32_t data_buf;
    uint32_t clk_tick = 1;

    for(auto i : events)
    {
        data_buf = 0;

        if(i.op == Read)
        {
            if(i.cpu->dCache->getData(i.addr, &data_buf))
            {
                cout << "[CPU-" << to_string(i.cpu->getCpuId()) << "]: LW x1, " << i.addr << endl;
                cout << "[CPU-" << to_string(i.cpu->getCpuId()) << "]: Local Cache Read --> x1 = " << data_buf << endl; 
                cout << "States: " << endl;

                auto x = state_transitions_map[i.addr];
                for(uint8_t it = 0; it < totalCpus; it++)
                {
                    cout << "CPU-" << to_string(it) << " ";
                    for(auto s : x[it])
                        cout << "->" << s;
                    cout << "\n";
                }
                
                clk_tick++;
            }
            else
            {
                cout << "[CPU-" << to_string(i.cpu->getCpuId()) << "]: LW x1, " << i.addr << endl;
                cout << "[CPU-" << to_string(i.cpu->getCpuId()) << "]: MM Read" << endl;

                //Get data from RAM is arbiter is not busy
                if(!i.cpu->dCache->isArbBusy())
                {
                    i.cpu->dCache->setArbBusy(true);
                    
                    i.cpu->dCache->processArbMesi(Read, i.cpu->getCpuId(), i.addr, &clk_tick);
                    uint32_t data_buf = i.cpu->dCache->getInsFromRAM(i.addr); 
                    cout << "Data loaded from RAM --> x1 = " << data_buf << endl;
                    cout << "States: " << endl;

                    i.cpu->dCache->setArbBusy(false);
                    
                    for(auto x : cpu_list)
                    {
                        cache_state st = gb->getUpdtCacheState(x->getCpuId(), i.addr);
                        if(x->dCache->getCurCacheState(i.addr) != st)
                        {
                            x->dCache->setCurCacheState(i.addr, st);

                            if(state_transitions_map[i.addr].size() == 0)
                            {
                                state_transitions_map[i.addr] = result;
                            }
                            state_transitions_map[i.addr][x->getCpuId()].push_back(gb->convToStr(st));
                        }
                    }

                    auto x = state_transitions_map[i.addr];
                    
                    for(uint8_t it = 0; it < totalCpus; it++)
                    {
                        cout << "CPU-" << to_string(it) << " ";
                        for(auto s : x[it])
                            cout << "->" << s;
                        cout << "\n";
                    }
                }                
            }
        }
        else if(i.op == Write)
        {
            cout << "[CPU-" << to_string(i.cpu->getCpuId()) << "]: SW x1, " << i.addr << endl;
            cout << "[CPU-" << to_string(i.cpu->getCpuId()) << "]: Main Memory Write" << endl;

            //Get data from RAM is arbiter is not busy
            if(!i.cpu->dCache->isArbBusy())
            {
                data_buf = 3;
                i.cpu->dCache->setArbBusy(true);
                
                i.cpu->dCache->processArbMesi(Write, i.cpu->getCpuId(), i.addr, &clk_tick);
                i.cpu->dCache->setDataToRAM(i.addr, data_buf);
                cout << "Data Written to RAM --> x1 = " << data_buf << endl;
                cout << "States: " << endl;

                i.cpu->dCache->setArbBusy(false);
                
                for(auto x : cpu_list)
                {
                    cache_state st = gb->getUpdtCacheState(x->getCpuId(), i.addr);
                    if(x->dCache->getCurCacheState(i.addr) != st)
                    {
                        x->dCache->setCurCacheState(i.addr, st);

                        if(state_transitions_map[i.addr].size() == 0)
                        {
                            clk_tick += 2;
                            state_transitions_map[i.addr] = result;
                        }
                        state_transitions_map[i.addr][x->getCpuId()].push_back(gb->convToStr(st));
                    }
                }

                auto x = state_transitions_map[i.addr];
                
                for(uint8_t it = 0; it < totalCpus; it++)
                {
                    cout << "CPU-" << to_string(it) << " ";
                    for(auto s : x[it])
                        cout << "->" << s;
                    cout << "\n";
                }
            }
        }

        cout << "Clk Tick: " << clk_tick << endl;
        cout << "\n======================================================================" << endl;
        cout << "======================================================================" << endl;
        cout << endl;
    }
}
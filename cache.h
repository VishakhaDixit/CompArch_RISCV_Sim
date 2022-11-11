#ifndef __CACHE_H__
#define __CACHE_H__

#include <utility>
#include <vector>
#include <string>
#include "arbiter.h"
#include "system.h"

using namespace std;


enum associativity_type {none, two_way, four_way, full};

class Cache : public System{
    private: 
        class cacheEvent : public Event
        {
        private:
            Cache *cDev;
        public:
            cacheEvent(Cache *cd) : Event(), cDev(cd) {}
            void process() {}
            void process(uint32_t addr) { cDev->process(addr); }
        };

        cacheEvent *ce;

        size_t cache_size;
        size_t line_size;
        size_t set_size;

        //struct to keep all of line data
        struct lineData {
            uint32_t tag;
            bool valid_bit;
            uint32_t lru_count; //tracks lru
            uint8_t set_num;
            uint32_t data;
        };
        std::vector<lineData*> maps;
        
        associativity_type assoc;
        arbiter *arb;

        //for testing puruposes
        int hit_num, miss_num;

    public:
        Cache(size_t size, size_t line_size, associativity_type a, arbiter *arbC);
        virtual ~Cache();

        void updateCache(uint32_t addr, uint32_t val);
        bool isHit(uint32_t addr);
        void process(uint32_t addr);
        uint8_t getData(uint32_t addr);


        //for testing
        int getNumHits() { return hit_num; } 
        int getNumMisses() { return miss_num; }
};

#endif //__CACHE_H__
#ifndef __CACHE_H__
#define __CACHE_H__

#include <utility>
#include <vector>

enum associativity_type {none, two_way, four_way, full};

class Cache{
    private: 
        size_t cache_size;
        size_t line_size;

        //struct to keep all of line data
        struct lineData {
            uint8_t index;
            uint32_t tag;
            bool valid_bit;
            uint8_t lru_count; //tracks lru (Bit-PLRU)
        };
        std::vector<lineData*> maps;
        
        associativity_type assoc;


        //for testing puruposes
        int hit_num, miss_num;

    public:
        Cache(size_t size, size_t line_size, associativity_type a);

        bool isHit(uint32_t addr);

        uint8_t getData(uint32_t addr);

        //for testing
        int getNumHits() {return hit_num;}
        int getNumMisses() {return miss_num;}
};

#endif //__CACHE_H__
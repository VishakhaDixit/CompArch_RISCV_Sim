#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#include <unordered_map>

using namespace std;

enum cache_state {invalid, exclusive, shared, modified};
enum operation_type {Read, Write};

class Globals 
{
    private:
        typedef struct line_data {
            cache_state state;  //MESI states
            uint32_t addr;
        }line_data_t;

    public:

        // Map of cpu id and cache line.
        unordered_map< uint8_t, line_data_t > curCacheState;

        string convToStr(cache_state s);
        cache_state getUpdtCacheState(uint8_t cpu_id, uint32_t addr);
};

#endif //__GLOBALS_H__
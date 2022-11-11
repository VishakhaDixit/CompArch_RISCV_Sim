/**************************
 *
 * @file    pipeline.h
 *
 * @brief   This file contains classes for pipeline and it's 4 stages.
 *
 * @date    Sept 17, 2022
 *
 * @author  Vishakha Dixit
 *
 **************************/

#ifndef __PIPELINE_H__
#define __PIPELINE_H__

#include <string>
#include "system.h"
#include "inst.h"
#include "arbiter.h"
#include "cache.h"

using namespace std;

class pipeline : public System
{
    protected:
        inst *curInst;             //Current pipeline instruction
        pipeline *nextStage;       //Pointer to store next stage in pipeline

        System *sys;

    public:
        pipeline(System *_sys) : sys(_sys), curInst(NULL) {};
        
        virtual void recvInst(inst *i) = 0;
        
        void sendInst(inst *i)
        {
            if(nextStage != NULL)
                nextStage->recvInst(i);         //Send current instruction to the next stage in pipeline.

            curInst = NULL;
        }

        void setNextStage(pipeline *nxtStg)
        {
            nextStage = nxtStg;
        }

        bool isBusy()
        {
            return (curInst != NULL);
        }
};

class fetch : public pipeline
{
    private:
        class fetchEvent : public Event
        {
        private:
            fetch *fDev;
        public:
            fetchEvent(fetch *fd) : Event(), fDev(fd) {}
            void process() { fDev->process(); }
            void process(uint32_t addr) {}

        };

        fetchEvent *fe;
        arbiter *arb;
        uint8_t cpu_id;
	    Cache *iCache;
    
    public:
        fetch(System *sys, arbiter *a, Cache *i_cache, uint8_t id) : pipeline(sys), fe(new fetchEvent(this)) {
            arb = a;
            cpu_id = id;
            iCache = i_cache;
        };

        void recvInst(inst *i);
        void process();
};

class decode : public pipeline
{
    private:
        class decodeEvent : public Event
        {
        private:
            decode *dDev;
        public:
            decodeEvent(decode *dd) : Event(), dDev(dd) {}
            void process() { dDev->process(); }
            void process(uint32_t addr) {}

        };

        decodeEvent *de;
        uint8_t cpu_id;
    
    public:
        decode(System *sys, uint8_t id) : pipeline(sys), de(new decodeEvent(this)) {
            cpu_id = id;
        };

        void recvInst(inst *i);
        void decodeInst();
        void process();
};

class execute : public pipeline
{
    private:
        class executeEvent : public Event
        {
        private:
            execute *eDev;
        public:
            executeEvent(execute *ed) : Event(), eDev(ed) {}
            void process() { eDev->process(); }
            void process(uint32_t addr) {}

        };

        executeEvent *ee;
        arbiter *arb;
        uint8_t cpu_id;
        Cache *dCache;
        bool isExecuted;
    
    public:
        execute(System *sys, arbiter* a, Cache *d_cache, uint8_t id) : pipeline(sys), ee(new executeEvent(this)) {
            arb = a;
            cpu_id = id;
            dCache = d_cache;
            isExecuted = false;
        };

        void recvInst(inst *i);
        void executeInst();
        void process();
};

class store : public pipeline
{
    private:
        class storeEvent : public Event
        {
        private:
            store *sDev;
        public:
            storeEvent(store *sd) : Event(), sDev(sd) {}
            void process() { sDev->process(); }
            void process(uint32_t addr) {}

        };

        storeEvent *se;
        arbiter *arb;
        uint8_t cpu_id;
        Cache *dCache;
    
    public:
        store(System *sys, arbiter *a,Cache *d_cache, uint8_t id) : pipeline(sys), se(new storeEvent(this)) {
            arb = a;
            cpu_id = id;
            dCache = d_cache;
        };

        void recvInst(inst *i);
        void process();
};

#endif //__PIPELINE_H__
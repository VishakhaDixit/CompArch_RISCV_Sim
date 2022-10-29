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

        };

        fetchEvent *fe;
        arbiter *arb;
        uint8_t cpu_id;
    
    public:
        fetch(System *sys, arbiter *a, uint8_t id) : pipeline(sys), fe(new fetchEvent(this)) {
            arb = a;
            cpu_id = id;
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

        };

        decodeEvent *de;
    
    public:
        decode(System *sys) : pipeline(sys), de(new decodeEvent(this)) {};

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

        };

        executeEvent *ee;
        arbiter *arb;
        uint8_t cpu_id;
    
    public:
        execute(System *sys, arbiter* a, uint8_t id) : pipeline(sys), ee(new executeEvent(this)) {
            arb = a;
            cpu_id = id;
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

        };

        storeEvent *se;
        arbiter *arb;
        uint8_t cpu_id;
    
    public:
        store(System *sys, arbiter *a, uint8_t id) : pipeline(sys), se(new storeEvent(this)) {
            arb = a;
            cpu_id = id;
        };

        void recvInst(inst *i);
        void process();
};

#endif //__PIPELINE_H__
#include "simobject.hh"
#include <iostream>
#include <sys/time.h>

class SimObjectTest : public SimObject {
private:
	class TestEvent : public Event {
	private:
		SimObjectTest *device;
	public:
		TestEvent(SimObjectTest * sot) : Event(), device(sot) {}
		virtual void process() override { device->process(); }
		virtual const char* description() override {
			return "Test Event";
		}
	};

	TestEvent * e;
	Tick clk_tick;

public:
	SimObjectTest(System * sys) : SimObject(sys), e(new TestEvent(this)), clk_tick(10) {}
	virtual void initialize() override {
		//Generate random 20 events
		uint8_t event_cnt = 0;
		Tick event_time;
		// int event_val;
		bool isScheduled;

		srand(time(0));

		while(event_cnt < 20)
		{
			event_time = 1+ (rand() % 100);
			// event_val = rand()%100;

			isScheduled = schedule(e, event_time);

			if(isScheduled)
			{
				e = new TestEvent(this);
				event_cnt++;
			}
			else
			{
				e->deschedule();
				continue;
			}
		}
	}
	void process() {
		std::cout << "I am processing on Tick " << currTick() << std::endl;
		//Generate new event time
		// Tick newEventTime = 0;
		// newEventTime = rand()%(100-currTick() + 1) + currTick();

		schedule(e, currTick()+clk_tick);
	}
};
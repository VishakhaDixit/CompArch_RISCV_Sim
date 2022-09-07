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
		int event_val;

		time_t time_ptr;
		time_ptr = time(NULL);
	
		// Get the localtime
		tm* tm_local = localtime(&time_ptr);

		srand(time(0));

		while(event_cnt < 20)
		{
			event_time = 1 + tm_local->tm_sec;
			event_val = rand()%1000;

			schedule(e, event_time, event_val);
			e = new TestEvent(this);
			event_cnt++;
		}
	}
	
	void process() 
	{
		std::cout << "Processing: " << std::endl;
	}
};
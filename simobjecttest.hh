#include "simobject.hh"
#include <iostream>

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
		schedule(e, currTick());
	}
	void process() {
		std::cout << "I am processing on Tick " << currTick() << std::endl;
		schedule(e, currTick()+clk_tick);
	}
};
#include "simobject.hh"
#include <iostream>

class SimObjectTest : public SimObject {
private:
	class TestEvent : public Event {
	private:
		SimObjectTest *device;
	public:
		TestEvent(SimObjectTest * sot) : Event(), device(sot) {}
		void process() { device->process(); }
	};

	TestEvent * e;

public:
	SimObjectTest(System * sys) : SimObject(sys), e(new TestEvent(this)) {}
	virtual void initialize() override {
		schedule(e, currTick()+1);
	}
	void process() {
		std::cout << "I am processing on Tick: " << currTick() << std::endl;
		schedule(e, currTick()+1);
	}
};
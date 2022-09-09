#include "simobject.hh"
#include <iostream>

class SimObjectTest : public SimObject {
private:
	class TestEvent : public Event {
	private:
		SimObjectTest *device;
	public:
		TestEvent(SimObjectTest * sot) : Event(), device(sot) {}
		void process(Tick t, int v) { device->process(t, v); }
	};

	TestEvent * e;

public:
	SimObjectTest(System * sys) : SimObject(sys), e(new TestEvent(this)) {}
	virtual void initialize() override {
		schedule(e, currTick()+1);
	}
	void process(Tick t, int v) {
		std::cout << "I am processing on Tick: " << currTick() << std::endl;
		schedule(e, t, v);
	}
};
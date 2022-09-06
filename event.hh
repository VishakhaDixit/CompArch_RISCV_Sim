#ifndef __EVENT_HH__
#define __EVENT_HH__

#include <cinttypes>

#define Tick uint64_t

class Event {
private:
	Tick eventTime;
	int eventValue;
public:
	Event() : eventTime(0), eventValue(0) { }
	void schedule(Tick newTime, int newVal) {
		eventTime = newTime;
		eventValue = newVal;
	}
	void deschedule() {
		eventTime = -1;
		eventValue = -1;
	}
	void setValue(int v) { eventValue = v; }
	void setTime(Tick t) { eventTime = t; }
	int getValue() { return eventValue; }
	Tick time() { return eventTime; }
	virtual void process() = 0;
	virtual const char* description() = 0;
};

#endif //__EVENT_HH__
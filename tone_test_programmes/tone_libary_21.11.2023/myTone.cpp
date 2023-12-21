#include "Arduino.h"
#include "pinDefinitions.h"
#include "mbed.h"

using namespace std::chrono_literals;
using namespace std::chrono;

class myTone {
    mbed::DigitalOut   *pin;
    mbed::Timer        timer;
    mbed::Timeout      timeout;  // calls a callback once when a timeout expires
    mbed::Ticker       ticker;   // calls a callback repeatedly with a timeout
    uint32_t           frequency;
    uint32_t           duration;

public:
    myTone(PinName _pin, unsigned int frequency, unsigned long duration) : frequency(frequency), duration(duration)  {
    	pin = new mbed::DigitalOut(_pin);
    }

    ~myTone() {
        stop();
        timeout.detach();
        delete pin;
    }

    void start(void) {
        ticker.attach(mbed::callback(this, &myTone::toggle), 500000us / frequency );
        if (duration != 0) {
            start_timeout();
        }
    }

    void toggle() {
    	*pin = !*pin;
    }

    void stop(void) {
        ticker.detach();
        pin = 0;
    }

    void start_timeout(void) {
        timeout.attach(mbed::callback(this, &myTone::stop), duration * 1ms);
    }
};

myTone* active_tone = NULL;

void mytone(uint8_t pin, unsigned int frequency) {
	if (active_tone) {
		delete myTone;
    myTone* active_tone = NULL;
	}
	myTone* t = new myTone(digitalPinToPinName(pin), frequency, duration);
	t->start();
	active_tone = t;
};

void mynoTone(uint8_t pin) {
	if (active_tone) {
		active_tone->stop();
		delete active_tone;
		active_tone = NULL;
	}
};
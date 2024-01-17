// ARDUINO Sketch komplett mit setup() und loop()




#include "Arduino.h"
#include "pinDefinitions.h"
#include "mbed.h"

using namespace std::chrono_literals;
using namespace std::chrono;

class MyTone {
    mbed::DigitalOut   *pin;
    mbed::Timer        timer;
    mbed::Timeout      timeout;  // calls a callback once when a timeout expires
    mbed::Ticker       ticker;   // calls a callback repeatedly with a timeout
    uint32_t           frequency;
    uint32_t           duration;

public:
    MyTone(PinName _pin, unsigned int frequency, unsigned long duration) : frequency(frequency), duration(duration)  {
    	pin = new mbed::DigitalOut(_pin);
    }

    ~MyTone() {
        stop();
        timeout.detach();
        delete pin;
    }

    void startmytone(uint32_t frequency,uint32_t duration ) {
	if(this->duration == duration && duration == 0 && this->frequency==frequency) {
	    return; // nichts hat sich geändert ... gleiche Frequenz Dauerton bleibt
	}
	this->frequency = frequency;
	this->duration  = duration;
	stop();
	start();
    }

    void start(void) {
        ticker.attach(mbed::callback(this, &Tone::toggle), 500000us / frequency );
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
        timeout.attach(mbed::callback(this, &Tone::stop), duration * 1ms);
    }
};






MyTone* active_tone = Null;
unsigned long mytonefreq=1000;

void setup() {
    MyTone* = new MyTone(pin, mytonefreq, 200);  // 200 ms bei 1000 Hz bei Programmstart
}

void loop() {
    active_tone->startmytone(400);    
}

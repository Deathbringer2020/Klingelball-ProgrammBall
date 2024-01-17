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

    void startmytone(uint32_t frequency,uint32_t duration = 0) {
	if(this->duration == duration && duration == 0 && this->frequency==frequency) {
	    return; // nichts hat sich geändert ... gleiche Frequenz Dauerton bleibt
	}
	this->frequency = frequency;
	this->duration  = duration;
	stop();
	start();
    }

    void start(void) {
        ticker.attach(mbed::callback(this, &MyTone::toggle), 500000us / frequency );
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
        timeout.attach(mbed::callback(this, &MyTone::stop), duration * 1ms);
    }
};



unsigned long i;
int pin = 3;

MyTone* active_mytone = NULL;
unsigned long mytonefreq=1000;

void setup() {
      Serial.begin(115200);
    
}

void loop() {
  static int first = 1;
    
  if(first){
    Serial.println("Init"); 
    MyTone* active_mytone = new MyTone(digitalPinToPinName(pin), mytonefreq, 200);  // 200 ms bei 1000 Hz bei Programmstart
    active_mytone->start();
    first = 0;
  }


  
    active_mytone->startmytone(400);    
    delay(1000);
    active_mytone->startmytone(600); 
    Serial.println("Hi");
    delay(1000);
    
    
}

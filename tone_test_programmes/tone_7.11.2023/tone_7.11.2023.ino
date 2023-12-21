#define Pin1 GPIO0
#define Pin2 A0


//#include Arduino_BHY2
#include "Nicla_System.h"


void setup() {
  // put your setup code here, to run once:
  pinMode(Pin1, OUTPUT);
  pinMode(Pin2, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:

  tone(Pin1, 300);
  delay(2000);
  noTone(Pin1);
  digitalWrite(Pin1, 0);
  delay(1000);

  tone(Pin2, 300);  //GIPO0 ist A0, auch bei anderen wird meistens A0 
  delay(2000);
  noTone(Pin2);
  digitalWrite(Pin2, 0);
  delay(1000);

}

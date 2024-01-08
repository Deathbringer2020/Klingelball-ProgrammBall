#include <Arduino_LSM9DS1.h>

float accx, accy, accz, accsum;
int speed;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }


}

void loop() {
  // put your main code here, to run repeatedly:
  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(accx, accy, accz);
  }

  accsum = (accx + accy + accz) / 3; 
  

  speed = map(accsum, -5, 5, 0, 255);
  
    Serial.println(speed);

}

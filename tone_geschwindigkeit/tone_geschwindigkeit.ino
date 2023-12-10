#include "Arduino_BHY2.h"
#include "Nicla_System.h"

  SensorXYZ gyroscope(SENSOR_ID_GYRO);
  int16_t valueX;
  int16_t valueY;
  int16_t valueZ;
  int16_t value; 
  float mapValue = 700;

  void setup(){
    Serial.begin(115200);
    BHY2.begin();
    gyroscope.begin();
    pinMode(A0, OUTPUT);

    nicla::begin();
    nicla::leds.begin();
    

  }

  void loop(){

    while(true){
      BHY2.update();
      valueX = gyroscope.x();
      valueY = gyroscope.y();
      valueZ = gyroscope.z();
  

   // Serial.println(gyroscope.toString()); //Prints all the data "automatically"

    //Print the individual values
     // Serial.println(valueX);

      value = ( valueX + valueY + valueZ ) / 3;
      if(value > 3000){
        value = 3000;
        
      }
      if(value < -3000){
        
        value = -3000;
      }
      mapValue = map(value, -3000, 3000, 500, 1200); //frequenz 500 bis 1200
      tone(A0, mapValue);

    //  Serial.println(millis());
      nicla::leds.setColor(green);
      
      //noTone(A0);
      //tone(A0, mapValue);

      delay(250);
      nicla::leds.setColor(red);
      delay(250);
    };
  }
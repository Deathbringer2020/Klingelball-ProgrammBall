#include "Arduino_BHY2.h"

  SensorXYZ gyroscope(SENSOR_ID_GYRO);
  int16_t valueX;
  int16_t valueY;
  int16_t valueZ;
  int16_t value; 
  int16_t mapValue;

  void setup(){
    Serial.begin(115200);
    BHY2.begin();
    gyroscope.begin();

    
  }

  void loop(){
    BHY2.update();
    valueX = gyroscope.x();
    valueY = gyroscope.y();
    valueZ = gyroscope.z();

   // Serial.println(gyroscope.toString()); //Prints all the data "automatically"

    //Print the individual values
    Serial.println(valueX);

    value = ( valueX + valueY + valueZ ) / 3;
    mapValue = map(value, -3000, 3000, 500, 1200); //frequenz 500 bis 1200


    tone(1, mapValue);


    delay(10000);
  }
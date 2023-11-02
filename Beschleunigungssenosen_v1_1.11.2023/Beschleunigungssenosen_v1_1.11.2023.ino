#include "Arduino_BHY2.h"

  SensorXYZ gyroscope(SENSOR_ID_GYRO);
  int16_t valueX;
  int16_t valueY;
  int16_t valueZ;

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

    Serial.println(gyroscope.toString()); //Prints all the data "automatically"

    //Print the individual values
    Serial.println(valueX);

    delay(10000);
  }
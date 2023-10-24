

#include <ArduinoBLE.h>



#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"

#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"  // An/Aus
#define CHARACTERISTIC2_UUID "4a78b8dd-a43d-46cf-9270-f6b750a717c8" // Ton Lautstärke 
#define CHARACTERISTIC3_UUID "99067788-c62b-489d-82a9-6cbec8a31d07" // LED einstellungen
 

BLEService pService("SERVICE_UUID"); 

BLEIntCharacteristic xCharacteristic("CHARACTERISTIC_UUID", BLEBroadcast| BLERead | BLEWrite); 
BLEIntCharacteristic yCharacteristic("CHARACTERISTIC_UUID", BLERead | BLEWriteWithoutResponse); 
BLEIntCharacteristic zCharacteristic("CHARACTERISTIC_UUID", BLERead | BLEWrite); 



void setup() {
  Serial.begin(115200);
  Serial.println("Starting BLE work!");


  if (!BLE.begin()) {
    Serial.println("starting Bluetooth® Low Energy module failed!");

    while (1);
  }


 // BLE.setLocalName("Klingelball");
  //BLE.setDeviceName("Klingelball");

  BLE.addService(pService);
  BLE.setAdvertisedService(pService);

  pService.addCharacteristic(xCharacteristic);
  xCharacteristic.setValue(001);

  pService.addCharacteristic(yCharacteristic);
  yCharacteristic.setValue(010);

  pService.addCharacteristic(zCharacteristic);
  zCharacteristic.setValue(100);


  BLE.advertise();


}

void loop() {
  // put your main  code here, to run repeatedly:

  BLE.poll(); // weiß nicht 

  Serial.println("Test");
  delay(2000);
  BLE.stopAdvertise();//damit es immer neustartet es beendet sich selbst sonst
  BLE.advertise();
  if(BLE.connected()){
    
    int BallAn = xCharacteristic.value();
    Serial.println(BallAn);

    Serial.println("Hi"); 


    
  }
  Serial.println("ende");
//pCharacteristic->getValue();
  //BallAn = pCharacteristic->getValue();
  
 // Lautstärke = pCharacheristic2->getValue();
//  LEDs = pCharacheristic3->getValue();

 // Serial.println(BallAn);
 // Serial.println(Lautstärke);
 

}









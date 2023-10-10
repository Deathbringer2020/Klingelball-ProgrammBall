/*
    Based on Neil Kolban example for IDF: https://github.com/nkolban/esp32-snippets/blob/master/cpp_utils/tests/BLE%20Tests/SampleServer.cpp
    Ported to Arduino ESP32 by Evandro Copercini
    updates by chegewara
*/


#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>


// See the following for generating UUIDs:
// https://www.uuidgenerator.net/

#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"

#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"  // An/Aus
#define CHARACTERISTIC2_UUID "4a78b8dd-a43d-46cf-9270-f6b750a717c8" // Ton Lautstärke 
#define CHARACTERISTIC3_UUID "99067788-c62b-489d-82a9-6cbec8a31d07" // LED einstellungen
//#define CHARACTERISTIC4_UUID "a47b99b4-3804-4411-b61c-50852ab7aa2d" // Frequenz 


BLECharacteristic xCharacteristics(CHARACTERISTIC_UUID, BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE);
BLEDescriptor xDescriptor(BLEUUID((uint16_t)0x2902));
BLECharacteristic yCharacteristics(CHARACTERISTIC2_UUID, BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE);
BLEDescriptor yDescriptor(BLE2902());
BLECharacteristic zCharacteristics(CHARACTERISTIC3_UUID, BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE);
BLEDescriptor zDescriptor(BLE2902()); 
//BLECharacteristic tCharacteristics(CHARACTERISTIC4_UUID, BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE);
//BLEDescriptor tDescriptor(BLE2902()); 

bool deviceConnected = false;

class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
    };

    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
    }
};

void setup() {
  Serial.begin(115200);
  Serial.println("Starting BLE work!");

  BLEDevice::init("EchoBall");
  BLEServer *pServer = BLEDevice::createServer();
 // pServer->setCallbacks(new MyServerCallbacks);
  BLEService *pService = pServer->createService(SERVICE_UUID);
  pServer->setCallbacks(new MyServerCallbacks()); //An/Aus

  pService->addCharacteristic(&xCharacteristics);
  xCharacteristics.setValue("An/Aus");
 // xDescriptor.setValue("1");
  xCharacteristics.addDescriptor(new BLE2902());

  pService->addCharacteristic(&yCharacteristics);
  yCharacteristics.setValue("Lautstärke");
 // yDescriptor.setValue("2");
  yCharacteristics.addDescriptor(new BLE2902());

  pService->addCharacteristic(&zCharacteristics);
  zCharacteristics.setValue("LEDs");
 // zDescriptor.setValue("3");
  zCharacteristics.addDescriptor(new BLE2902());
/*
  pService->addCharacteristic(&tCharacteristics);
  tCharacteristics.setValue("7");
 // tDescriptor.setValue("3");
  tCharacteristics.addDescriptor(new BLE2902());
*/

 /* 
  BLECharacteristic *pCharacteristic = pService->createCharacteristic(  //
                                         CHARACTERISTIC_UUID,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );

  pCharacteristic->addDescriptor(new BLE2902());

  BLECharacteristic *pCharacteristic2 = pService->createCharacteristic(
                                         CHARACTERISTIC2_UUID,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );

  pCharacteristic2->addDescriptor(new BLE2902());
  
  BLECharacteristic *pCharacteristic3 = pService->createCharacteristic(
                                         CHARACTERISTIC3_UUID,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );

  pCharacteristic3->addDescriptor(new BLE2902());

  BLECharacteristic *pCharacteristic4 = pService->createCharacteristic(
                                         CHARACTERISTIC4_UUID,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );

  pCharacteristic4->addDescriptor(new BLE2902());
*/

  
 /* 
  pCharacteristic->setValue("An/Aus");

  pCharacteristic2->setValue("Lautstärke");

  pCharacteristic3->setValue("LEDS");
*/
 // pCharacteristic4->setValue("Frequenz");
  
  pService->start();


  // BLEAdvertising *pAdvertising = pServer->getAdvertising();  // this still is working for backward compatibility
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();
  Serial.println("Characteristic defined! Now you can read it in your phone!");

 // std::string BallAn = xCharacteristics.getValue();
 // Serial.println(BallAn.c_str());

  
}

void loop() {
  // put your main  code here, to run repeatedly:


  Serial.println("Test");
  delay(2000);
  BLEDevice::stopAdvertising();//damit es immer neustartet es beendet sich selbst sonst
  BLEDevice::startAdvertising();
  if(deviceConnected){
    
    std::string BallAn = xCharacteristics.getValue();
    Serial.println(BallAn.c_str());

    Serial.println("Hi"); 


    
  }
//pCharacteristic->getValue();
  //BallAn = pCharacteristic->getValue();
  
 // Lautstärke = pCharacheristic2->getValue();
//  LEDs = pCharacheristic3->getValue();

 // Serial.println(BallAn);
 // Serial.println(Lautstärke);
 

}









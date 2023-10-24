  // Defines 

  //Bluetooth
  
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

  int xValue[8], yValue[8], zValue[8];

void setup() {
  // put your setup code here, to run once:

    Serial.begin(115200);

  // Bluetooth Setup 

    

    Serial.println("Starting BLE work!");

    BLEDevice::init("EchoBall");
    BLEServer *pServer = BLEDevice::createServer();
    BLEService *pService = pServer->createService(SERVICE_UUID);
    pServer->setCallbacks(new MyServerCallbacks()); //An/Aus

    pService->addCharacteristic(&xCharacteristics);
    xCharacteristics.setValue("An/Aus");
    xCharacteristics.addDescriptor(new BLE2902());

    pService->addCharacteristic(&yCharacteristics);
    yCharacteristics.setValue("Lautstärke");
    yCharacteristics.addDescriptor(new BLE2902());

    pService->addCharacteristic(&zCharacteristics);
    zCharacteristics.setValue("LEDs");
    zCharacteristics.addDescriptor(new BLE2902());


    pService->start();


    // BLEAdvertising *pAdvertising = pServer->getAdvertising();  // this still is working for backward compatibility
    BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
    pAdvertising->addServiceUUID(SERVICE_UUID);
    pAdvertising->setScanResponse(true);
    pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
    pAdvertising->setMinPreferred(0x12);
    BLEDevice::startAdvertising();
    Serial.println("Characteristic defined! Now you can read it in your phone!");




  // Pin Setup 


  // Serial Setup (Zum testen)

}

void loop() {
  // put your main code here, to run repeatedly:

  // Ceck Bluetototh conection 
    Serial.println("Test");
    delay(2000);
    BLEDevice::stopAdvertising();//damit es immer neustartet es beendet sich selbst sonst
    BLEDevice::startAdvertising();


  // Bluetooth einlesen und paramenter anpassen 
    if(deviceConnected){
      
      std::string xString = xCharacteristics.getValue();
      Serial.println(xString.c_str());
      std::string yString = yCharacteristics.getValue();
      Serial.println(yString.c_str());
      std::string zString = zCharacteristics.getValue();
      Serial.println(zString.c_str());

      Serial.println("Hi"); 
      

/*
      xValue[] = xString.toInt(); //konvertierung der Strings aus Bluetooth in int arrays
      yValue[] = yString.toInt();
      zValue[] = zString.toInt();
*/

    }



  // Sensoren auslesen 


  // Anpassung Ton 


  // Anpassung LEDs 


  // Ladestation (LEDs und Ton aus)


  // Energiesparmodus (Wenn ball nicht in betrieb Per handy einstellbar)
    // entweder das oder das andere (außer bluetooth)


  // Akkustand

 

}

  // Defines 


  // Transport Varibles 

  //  int xCharact[9] = [000000000]


  //Bluetooth
      
    #include <ArduinoBLE.h>



    #define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"

    #define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"  // An/Aus
    #define CHARACTERISTIC2_UUID "4a78b8dd-a43d-46cf-9270-f6b750a717c8" // Ton Lautstärke 
    #define CHARACTERISTIC3_UUID "99067788-c62b-489d-82a9-6cbec8a31d07" // LED einstellungen
    

    BLEService pService("SERVICE_UUID"); 

    BLEUnsignedIntCharacteristic xCharacteristic("CHARACTERISTIC_UUID", BLEBroadcast | BLERead | BLEWrite); 
    BLEUnsignedIntCharacteristic yCharacteristic("CHARACTERISTIC2_UUID", BLEBroadcast | BLERead | BLEWriteWithoutResponse); 
    BLEUnsignedIntCharacteristic zCharacteristic("CHARACTERISTIC3_UUID", BLEBroadcast | BLERead | BLEWrite); 


void setup() {
  // put your setup code here, to run once:

    Serial.begin(115200);

  // Bluetooth Setup 

      
    Serial.println("Starting BLE work!");


    if (!BLE.begin()) {
      Serial.println("starting Bluetooth® Low Energy module failed!");

      while (1);
    }


    BLE.setLocalName("Klingelball");
    BLE.setDeviceName("Klingelball");

    BLE.setAdvertisedService(pService);

    pService.addCharacteristic(xCharacteristic);
    xCharacteristic.setValue(001);

    pService.addCharacteristic(yCharacteristic);
    yCharacteristic.setValue(10);   //es darf keine null vor der zahl stehen dann wird es nähmlich ein anderer wert

    pService.addCharacteristic(zCharacteristic);
    zCharacteristic.setValue(100);

    BLE.addService(pService);
    BLE.advertise();
    xCharacteristic.broadcast();
    yCharacteristic.broadcast();
    zCharacteristic.broadcast();



  // Pin Setup 


  // Serial Setup (Zum testen)

}

void loop() {
  // put your main code here, to run repeatedly:

  //Bluetooth loop 

    BLE.poll(); // weiß nicht 


    Serial.println("Test");
    delay(2000);
    BLE.stopAdvertise();//damit es immer neustartet es beendet sich selbst sonst
    BLE.advertise();
    if(BLE.connected()){
      

      int xCharact = xCharacteristic.value();
      int yCharact = yCharacteristic.value();
      int zCharact = zCharacteristic.value();

      Serial.println("Characteristics: ");
      Serial.print("X: ");
      Serial.println(xCharact);
      Serial.print("Y: ");
      Serial.println(yCharact);
      Serial.print("Z: ");
      Serial.println(zCharact);

      Serial.println("Hi"); 


    }
    Serial.println("ende");




  // Sensoren auslesen 

    int Helligkeit = xCharact[0] + xCharact[1]*10; //zum Beispiel 
    



  // Anpassung Ton 


  // Anpassung LEDs 


  // Ladestation (LEDs und Ton aus)


  // Energiesparmodus (Wenn ball nicht in betrieb Per handy einstellbar)
    // entweder das oder das andere (außer bluetooth)


  // Akkustand

 

}

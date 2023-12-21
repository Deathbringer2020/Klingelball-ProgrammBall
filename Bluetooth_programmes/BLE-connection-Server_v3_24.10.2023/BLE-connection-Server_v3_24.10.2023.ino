

#include <ArduinoBLE.h>



#define SERVICE_UUID         "4fafc201-1fb5-459e-8fcc-c5c9c331914b"

#define CHARACTERISTIC_UUID  "beb5483e-36e1-4688-b7f5-ea07361b26a8"  // An/Aus
#define CHARACTERISTIC2_UUID "4a78b8dd-a43d-46cf-9270-f6b750a717c8" // Ton Lautstärke 
#define CHARACTERISTIC3_UUID "99067788-c62b-489d-82a9-6cbec8a31d07" // LED einstellungen
 

BLEService pService(SERVICE_UUID); 

BLEUnsignedIntCharacteristic xCharacteristic(CHARACTERISTIC_UUID, BLEBroadcast | BLERead | BLEWrite); 
BLEUnsignedIntCharacteristic yCharacteristic(CHARACTERISTIC2_UUID, BLEBroadcast | BLERead | BLEWriteWithoutResponse); 
BLEUnsignedIntCharacteristic zCharacteristic(CHARACTERISTIC3_UUID, BLEBroadcast | BLERead | BLEWrite); 



void setup() {
  Serial.begin(115200);
  Serial.println("Starting BLE work!");


  if (!BLE.begin()) {
    Serial.println("starting Bluetooth® Low Energy module failed!");

    while (1);
  }


  BLE.setLocalName("Klingelball");
  BLE.setDeviceName("Klingelball");
  
  BLE.setAdvertisedService(pService);
  pService.addCharacteristic(xCharacteristic);  //muss hier sein sonst funktioniert es nicht
  pService.addCharacteristic(yCharacteristic);
  pService.addCharacteristic(zCharacteristic);
  BLE.addService(pService);

//  BLE.setConnectable(true); //zur sicherheit, sollte von selbst true sein 

//  BLE.setAdvertisedServiceUuid(SERVICE_UUID );
  BLE.setAppearance(0x80);

  
  xCharacteristic.writeValue(27);

  yCharacteristic.setValue(10);   //es darf keine null vor der zahl stehen dann wird es nähmlich ein anderer wert
  
  zCharacteristic.setValue(0);


  if (!xCharacteristic.broadcast()) {
    Serial.println("broadcast failed!");

    while (1);
  }
  yCharacteristic.broadcast();
  zCharacteristic.broadcast(); 
  BLE.advertise();

}

void loop() {
  // put your main  code here, to run repeatedly:

//  BLE.poll(); // weiß nicht 


  Serial.println("Test");
  delay(2000);
  BLE.stopAdvertise();//damit es immer neustartet es beendet sich selbst sonst
  BLE.advertise();
  if(BLE.connected()){
    
    //xCharacterstic.written() //schaut ob die characteristics beschrieben wurde | für einzelne abfrage

 /*
    byte properties = xCharacteristic.properties();
    if(properties & BLERead){
    Serial.print("Proterties: ");
    Serial.println("S");
  }
*/
    int xCharact = xCharacteristic.value();
    int yCharact = yCharacteristic.value();
    int64_t zCharact = zCharacteristic.value();

    Serial.print("Service: ");
    Serial.println(pService.uuid());
    Serial.print("Chara: ");
    Serial.println(xCharacteristic.uuid());

    Serial.println("Characteristics: ");
    Serial.print("X: ");
    Serial.println(xCharact);
    Serial.print("Y: ");
    Serial.println(yCharact);
    Serial.print("Z: ");
    Serial.println(zCharact);

    Serial.print("Lengh: ");
    Serial.println(xCharacteristic.valueLength());


    Serial.println("Hi"); 


  }
  Serial.println("ende");


}

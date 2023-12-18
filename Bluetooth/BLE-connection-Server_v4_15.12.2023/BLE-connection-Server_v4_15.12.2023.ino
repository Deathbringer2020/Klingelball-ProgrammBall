

#include <ArduinoBLE.h>



#define SERVICE_UUID         "4fafc201-1fb5-459e-8fcc-c5c9c331914b"

#define CHARACTERISTIC_UUID  "beb5483e-36e1-4688-b7f5-ea07361b26a8"  
#define CHARACTERISTIC2_UUID "4a78b8dd-a43d-46cf-9270-f6b750a717c8"

 

BLEService pService(SERVICE_UUID); 

BLEUnsignedIntCharacteristic xCharacteristic(CHARACTERISTIC_UUID, BLEBroadcast | BLERead | BLEWrite); 
BLEUnsignedIntCharacteristic yCharacteristic(CHARACTERISTIC2_UUID, BLEBroadcast | BLERead | BLEWrite); 


//für zeiten 
unsigned long myTime = 0;

//BLE eingabe werte 
  unsigned long xCharact = 0;
  unsigned long yCharact = 0;
  int xChAr[10] = {0,0,0,0,0,0,0,0,0,0};
  int aByteZ = 0;
  int aByteAr[3] = {0,0,0};
  int bByte = 0;
  int cByte = 0;
  int dByte = 0;
  int pruefziffer = 0;


//


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

  BLE.addService(pService);

  BLE.setAppearance(0x80);

  
  xCharacteristic.setValue(1);
  yCharacteristic.setValue(2);   //es darf keine null vor der zahl stehen dann wird es nähmlich ein anderer wert


  BLE.advertise();

}

void loop() {
  // put your main  code here, to run repeatedly:

 //BLE Programm 
  BLE.stopAdvertise();//damit es immer neustartet es beendet sich selbst sonst
  BLE.advertise();
  if(BLE.connected()){


  //Delay aber ohne das das programm unterbochen wird
  if(myTime <= millis()){   
    myTime = millis() + 5000;

   //eingabe werte von BLE in Variablen speichern 
    xCharact = xCharacteristic.value();
    yCharact = yCharacteristic.value();
  
   //Testen ob beide Characteristics gleich sind
    if(xCharact == yCharact){
    }else{
      Serial.println("Characteristics nicht gleich");
    }

   //eingabe in Array speichern
    for(int i = 0; i <= 9; i++){
      
      xChAr[i] = xCharact % 10; 
      xCharact = xCharact / 10;

    }

   //die einzelnen bytes in array und Varbiablen speichern
    aByteZ = xCharact & 0xFF;
    for(int i = 0; i <= 2; i++){  
      aByteAr[i] = aByteZ % 10; 
      aByteZ = aByteZ / 10;
    }
    bByte = (xCharact >> 8) & 0xFF;  // 0xFF = 11111111
    cByte = (xCharact >> 16) & 0xFF;
    dByte = (xCharact >> 24) & 0xFF;


   //Prüfziffer berechnen 
    for(int i = 1; i <= 9; i++){  //prüfziffer berechnen

      if(i % 2){
        pruefziffer += xChAr[i] * 3;

      } else{ //gerade
        pruefziffer += xChAr[i] * 1;

      }
    }
    pruefziffer = 10 - (pruefziffer % 10); 

    

   //überprüfung 
    if(aByteAr[0] == pruefziffer){
      
     //Switch Welche eingabe 

      switch((aByteAr[2]*10 + aByteAr[1])){
        default:
          Serial.println("Switch Error");
          break; 
        case 1:
          
          break;
        case 2:
          
          break;
        case 24:

          break;
      }


    }else{
      Serial.println("Pruefziffer falsch");
    }

   // BLE Tests outputs

    Serial.println("Characteristics: ");
    Serial.print("X: ");
    Serial.println(xCharact);
    Serial.print("Y: ");
    Serial.println(yCharact);

    //Byte auslesen test
    Serial.println("Bytes: ");
    Serial.print("a: "); 
    Serial.println(aByteZ);
    Serial.print("b: "); 
    Serial.println(bByte);
    Serial.print("c: "); 
    Serial.println(cByte);
    Serial.print("d: "); 
    Serial.println(dByte);

  }
  }


}

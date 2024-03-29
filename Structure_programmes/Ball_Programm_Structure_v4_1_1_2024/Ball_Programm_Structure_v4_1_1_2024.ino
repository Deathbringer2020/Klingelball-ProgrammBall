//Includes 
 //BLE Includes 
  #include <ArduinoBLE.h>
  #include <math.h> 
  #include <Arduino.h>

 //Accelerator Include
  #include <Arduino_LSM9DS1.h>

 //LED Include
  #include <Adafruit_NeoPixel.h>

 //





// Defines
  enum state {Bluetooth, Sensor, Ton, LED, Akku, OffMode};
  state state = Bluetooth;

 //BLE Defines
  
  #define SERVICE_UUID         "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
  #define CHARACTERISTIC_UUID  "beb5483e-36e1-4688-b7f5-ea07361b26a8" 
  #define CHARACTERISTIC2_UUID "4a78b8dd-a43d-46cf-9270-f6b750a717c8" 

  BLEService pService(SERVICE_UUID); 
  BLEUnsignedIntCharacteristic xCharacteristic(CHARACTERISTIC_UUID, BLEBroadcast | BLERead | BLEWrite); 
  BLEUnsignedIntCharacteristic yCharacteristic(CHARACTERISTIC2_UUID, BLEBroadcast | BLERead | BLEWrite); 

 //LED Defines
  #define LEDPIN  4
  #define NUMLEDs 4

  Adafruit_NeoPixel LEDs(NUMLEDs, LEDPIN, NEO_GRB + NEO_KHZ800);

 //Tone Defines 
 // #define Tone_Pin 10
  #define Volume_Pin 5
  #define ToneUebertroagung1_Pin 6
  #define ToneUebertroagung2_Pin 7
  #define BeepUebertroagung_Pin 8

 //Akku Defines
  #define AkkuRead_Pin A1



// Variablen
 //BLE Variablen

 

  //BLE eingabe werte 
    unsigned long xCharact = 0;
    byte aByteZ = 0;
    byte aByteAr[3] = {0,0,0};
    byte bByte = 0;
    byte cByte = 0;
    byte dByte = 0;
    unsigned long pruefziffer = 0;

 //Berechungs Bariablen 
  
  byte Volume = 0;
  byte FreqStill = 0;
  byte FreqMov = 0;
  bool Beep = 0;         // on/off
  byte BeepStill = 0;
  byte BeepMov = 0;
  byte LEDRedStill = 255;
  byte LEDGreenStill = 0;
  byte LEDBlueStill = 0;
  byte LEDRedMov = 0;
  byte LEDGreenMov = 255;
  byte LEDBlueMov = 0;
  byte Brightness = 100;
  bool LEDFlashing = 0;
  byte LEDFlashFreq = 0;

 //Sensor Variablen 
  float accx, accy, accz, accsum;
  
 //Ton Variablen 
  int Freq, BeepSound; 
  byte aFreqByte;
  byte bFreqByte;
   
 //LED Variablen 
  int LEDRed, LEDGreen, LEDBlue;
  unsigned long LEDFlashTime; 
  bool LEDFlashOF;

 //Akku Variablen

  int Akkuvalue = 0;  
  byte Akkuprocent = 0; 
  byte bAkkuByte = 0; 
  int AkkuPruefziffer = 0;
  byte aAkkuByte = 0;
  unsigned long AkkuValue = 0;

      


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

  pService.addCharacteristic(xCharacteristic);  //muss hier sein sonst funktioniert es nicht
  pService.addCharacteristic(yCharacteristic);

  BLE.addService(pService);
  BLE.setAppearance(0x80);

  xCharacteristic.setValue(0);
  yCharacteristic.setValue(0);

  BLE.advertise();
 
 //Accelerator 
  
  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }


  // Pin Setup 
   //LED Pins
   
   //Ton Pins


  /*  pinMode(Volume_Pin, OUTPUT); //nur mit 2 autputs programmieren einer gibt aus welcher und der andere den wert
    pinMode(ToneUebertroagung1_Pin, OUTPUT);
    pinMode(ToneUebertroagung2_Pin, OUTPUT);    
    pinMode(BeepUebertroagung_Pin, OUTPUT);
  */
   //Akku Pins
    pinMode(AkkuRead_Pin, INPUT);

   


}

void loop() {
 // put your main code here, to run repeatedly:

  switch(state){

    case Bluetooth: //Bluetooth loop 

     //BLE Programm 
      BLE.stopAdvertise();//damit es immer neustartet es beendet sich selbst sonst
      BLE.advertise();
      if(BLE.connected()){

       //eingabe werte von BLE in Variablen speichern 
        xCharact = xCharacteristic.value();
      
       //die einzelnen bytes in array und Varbiablen speichern
        aByteZ = xCharact & 0xFF;
        for(int i = 0; i <= 2; i++){  
          aByteAr[i] = aByteZ % 10; 
          aByteZ = aByteZ / 10;
        }
        bByte = (xCharact >> 8);  
        cByte = (xCharact >> 16);
        dByte = (xCharact >> 24);


       //Prüfziffer berechnen 
        pruefziffer = 0;
        pruefziffer += bByte * 3;
        pruefziffer += cByte * 1;
        pruefziffer += dByte * 3;
        

        pruefziffer = 9 - (pruefziffer % 10); 

       //überprüfung 
        if(aByteAr[0] == pruefziffer){
          
        //Switch Welche eingabe 

          switch((aByteAr[2]*10 + aByteAr[1])){
            default:
              Serial.println("Switch Error");
              break; 
            case 0: 

              if(bByte == 0){
                state = OffMode; 
              }else{
                state = Bluetooth;
              }


              break; 
            case 1:

              Volume = bByte;
              FreqStill = cByte;
              FreqMov = dByte;

              break;
            case 2:
              
              Beep = bByte;         // on/off
              BeepStill = cByte;
              BeepMov = dByte;

              break;
            case 3:

              LEDRedStill = bByte;
              LEDGreenStill = cByte;
              LEDBlueStill = dByte;

              break;
            case 4:

              LEDRedMov = bByte;
              LEDGreenMov = cByte;
              LEDBlueMov = dByte;

              break;
            case 5:

              Brightness = bByte;
              LEDFlashing = cByte;
              LEDFlashFreq = dByte;

              break;
          }

          xCharacteristic.setValue(1);

        }else{
          Serial.println("Pruefziffer falsch");
          xCharacteristic.setValue(2);


        }
        
      }


      state = Sensor;
    break; 


    case Sensor: // Sensoren auslesen 

      if (IMU.accelerationAvailable()) {
        IMU.readAcceleration(accx, accy, accz);
      }

      if(accx < 0){ accx = accx * -1; } 
      if(accy < 0){ accy = accy * -1; }
      if(accz < 0){ accz = accz * -1; }

      accsum = (accx + accy + accz) / 3; 
      
     

      state = Ton;
    break; 



    case Ton: // Anpassung Ton 


    
       /*
      analogWrite(Volume_Pin, Volume);
      
      Freq = map(accsum, 0, 4, FreqStill*70, FreqMov*70);
      bFreqByte = Freq;
      aFreqByte = (Freq >> 8);
      analogWrite(ToneUebertroagung1_Pin, aFreqByte);
      analogWrite(ToneUebertroagung2_Pin, bFreqByte);

      BeepSound = map(accsum, 0, 4, BeepStill, BeepMov); //in ms converter noch 
      analogWrite(BeepUebertroagung_Pin, BeepSound);

      */
      state = LED;
    break;

    case LED: // Anpassung LEDs 

      LEDRed = map(accsum, 0, 4, LEDRedStill, LEDRedMov);
      LEDGreen = map(accsum, 0, 4, LEDGreenStill, LEDGreenMov);
      LEDBlue = map(accsum, 0, 4, LEDBlueStill, LEDBlueMov);

      LEDs.setBrightness(Brightness);


      if(LEDFlashing == 1){
        if(millis() >= LEDFlashTime + LEDFlashFreq * 1){
          LEDFlashOF = !LEDFlashOF;
          if(LEDFlashOF){
            LEDs.fill(LEDs.Color(LEDRed, LEDGreen, LEDBlue), 0, 4);
            LEDs.show();
          }else{
            LEDs.clear();
            LEDs.show();
          }
        }

      }else {
        LEDs.fill(LEDs.Color(LEDRed, LEDGreen, LEDBlue), 0, 4);
        LEDs.show();
      }


      state = Akku;
    break; 

    case Akku:// Akkustand (LEDs und Ton aus)

      Akkuvalue = analogRead(AkkuRead_Pin);
      bAkkuByte = map(Akkuvalue, 2, 3, 0 , 100);
      bAkkuByte = 43;                             //TODO akku auslesen 
      AkkuPruefziffer = bAkkuByte * 1;
      AkkuPruefziffer = 9 - (AkkuPruefziffer % 10); 
      aAkkuByte = 60 + AkkuPruefziffer; 

      AkkuValue = 0x0;
      AkkuValue = aAkkuByte + (bAkkuByte << 8); 

      yCharacteristic.setValue(AkkuValue);
/*      Serial.print("AkkuValue: ");
      Serial.println(AkkuValue);
      Serial.print("Chaacter: ");
      Serial.println(yCharacteristic.value()); */
     
      state = Bluetooth;
    break;



    case OffMode: // Energiesparmodus (Wenn ball nicht in betrieb Per handy einstellbar)
      // entweder das oder das andere (außer bluetooth);  entweder nur bluetooth an oder nur sensoren 
      //BLE Programm 
      BLE.stopAdvertise();//damit es immer neustartet es beendet sich selbst sonst
      BLE.advertise();
      if(BLE.connected()){

        //eingabe werte von BLE in Variablen speichern 
          xCharact = xCharacteristic.value();
        
        //die einzelnen bytes in array und Varbiablen speichern
        
          aByteZ = xCharact & 0xFF;
          for(int i = 0; i <= 2; i++){  
            aByteAr[i] = aByteZ % 10; 
            aByteZ = aByteZ / 10;
          }
          bByte = (xCharact >> 8);  
          cByte = (xCharact >> 16);
          dByte = (xCharact >> 24);


        //Prüfziffer berechnen 
          pruefziffer = 0;
          pruefziffer += bByte * 3;
          pruefziffer += cByte * 1;
          pruefziffer += dByte * 3;
          
          pruefziffer = 9 - (pruefziffer % 10); 

        //überprüfung 
          if(aByteAr[0] == pruefziffer){
            
          //Switch Welche eingabe 

            switch((aByteAr[2]*10 + aByteAr[1])){
              default:
                Serial.println("Switch Error");

                break; 
              case 0: 

                if(bByte == 0){
                  state = OffMode; 
                }else{
                  state = Sensor;
                }

                break; 
              case 1:

                Volume = bByte;
                FreqStill = cByte;
                FreqMov = dByte;

                break;
              case 2:
                
                Beep = bByte;         // on/off
                BeepStill = cByte;
                BeepMov = dByte;

                break;
              case 3:

                LEDRedStill = bByte;
                LEDGreenStill = cByte;
                LEDBlueStill = dByte;

                break;
              case 4:

                LEDRedMov = bByte;
                LEDGreenMov = cByte;
                LEDBlueMov = dByte;

                break;
              case 5:

                Brightness = bByte;
                LEDFlashing = cByte;
                LEDFlashFreq = dByte;

                break;
            }
            xCharacteristic.setValue(1);

          }else{
            Serial.println("Pruefziffer falsch");
            xCharacteristic.setValue(2);
          }

      }

    break; 



  }

  //Tests von Variablen 
 
   // BLE Tests outputs  
   

    Serial.println();
    Serial.print("X: ");
    Serial.println(xCharact);

    Serial.print("Pruefziffer: ");
    Serial.println(pruefziffer);

    //Byte auslesen test
 //   Serial.print("State: ");
 //   Serial.println(state);
    Serial.print("Volume: ");
    Serial.println(Volume);
    Serial.print("Beep: ");
    Serial.println(Beep);
    Serial.print("LED Still: "); 
    Serial.println(LEDRedStill);
    Serial.print("Mov: "); 
    Serial.println(LEDRedMov);
    Serial.print("Brightness: ");
    Serial.println(Brightness);
    Serial.print("BLE connected: ");
    Serial.println( BLE.connected());



}


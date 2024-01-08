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
  #define LEDPIN  18
  #define NUMLEDs 10

  Adafruit_NeoPixel LEDs(NUMLEDs, LEDPIN, NEO_GRB + NEO_KHZ800);

 //



// Variablen
 //BLE Variablen

  unsigned long myTime = 0;  //für zeiten 

  //BLE eingabe werte 
    unsigned long xCharact = 0;
    unsigned long yCharact = 0;
    int aByteZ = 0;
    int aByteAr[3] = {0,0,0};
    int bByte = 0;
    int cByte = 0;
    int dByte = 0;
    int pruefziffer = 0;

 //Berechungs Bariablen 
  
  int Volume = 0;
  int FreqStill = 0;
  int FreqMov = 0;
  bool Beep = 0;         // on/off
  int BeepStill = 0;
  int BeepMov = 0;
  int LEDRedStill = 0;
  int LEDGreenStill = 0;
  int LEDBlueStill = 0;
  int LEDRedMov = 0;
  int LEDGreenMov = 0;
  int LEDBlueMov = 0;
  int Brightness = 0;
  bool LEDFlashing = 0;
  int LEDFlashFreq = 0;

 //Sensor Variablen 
  float accx, accy, accz, accsum;
  
 //Ton Variablen 
  int Freq, BeepSound; 
   
 //LED Variablen 
  int LEDRed, LEDGreen, LEDBlue;
  unsigned long LEDFlashTime; 
  bool LEDFlashOF;

 //Akku Variablen



//  int xCharact[9] = [000000000]

//Bluetooth
      








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

  xCharacteristic.setValue(1);
  yCharacteristic.setValue(2);   //es darf keine null vor der zahl stehen dann wird es nähmlich ein anderer wert

  BLE.advertise();
 
 //Accelerator 
  
  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }


  // Pin Setup 
   //LED Pins
   
   //Ton Pins

  // Serial Setup (Zum testen)


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
        yCharact = yCharacteristic.value();
      
      //Testen ob beide Characteristics gleich sind
        if(xCharact == yCharact){
        }else{
          Serial.println("Characteristics nicht gleich");
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

        pruefziffer += bByte * 3;
        pruefziffer += cByte * 1;
        pruefziffer += dByte * 3;
        

        pruefziffer = 9 - (pruefziffer % 10); 

        Serial.print("Pruefziffer: ");
        Serial.println(pruefziffer);

      //überprüfung 
        if(aByteAr[0] == pruefziffer){
          
        //Switch Welche eingabe 

          switch((aByteAr[2]*10 + aByteAr[1])){
            default:
              Serial.println("Switch Error");
              break; 
            case 0: 

              if(bByte == 1){
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


        }else{
          Serial.println("Pruefziffer falsch");
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

      //    int Volume = 0;
   
   
      Freq = map(accsum, 0, 4, FreqStill, FreqMov);

      if(Beep == 1){
        BeepSound = map(accsum, 0, 4, BeepStill, BeepMov); //in ms converter noch 
      }

    
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
            LEDs.fill(LEDs.Color(LEDRed, LEDGreen, LEDBlue));
            LEDs.show();
          }else{
            LEDs.clear();
            LEDs.show();
          }
        }

      }else {
        LEDs.fill(LEDs.Color(LEDRed, LEDGreen, LEDBlue));
        LEDs.show();
      }


      state = Akku;
    break; 

    case Akku:// Akkustand (LEDs und Ton aus)

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
          yCharact = yCharacteristic.value();
        
        //Testen ob beide Characteristics gleich sind
          if(xCharact == yCharact){
          }else{
            Serial.println("Characteristics nicht gleich");
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

          pruefziffer += bByte * 3;
          pruefziffer += cByte * 1;
          pruefziffer += dByte * 3;
          
          pruefziffer = 9 - (pruefziffer % 10); 

          Serial.print("Pruefziffer: ");
          Serial.println(pruefziffer);

        //überprüfung 
          if(aByteAr[0] == pruefziffer){
            
          //Switch Welche eingabe 

            switch((aByteAr[2]*10 + aByteAr[1])){
              default:
                Serial.println("Switch Error");

                break; 
              case 0: 

                if(bByte == 1){
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


          }else{
            Serial.println("Pruefziffer falsch");
          }

      }

    break; 



  }

  //Tests von Variablen 
 
   // BLE Tests outputs  
   /*

    Serial.println("Characteristics: ");
    Serial.print("X: ");
    Serial.println(xCharact);
    Serial.print("Y: ");
    Serial.println(yCharact);

    //Byte auslesen test
    Serial.print("a.0: "); 
    Serial.println(aByteAr[0]);
    Serial.print("a.1: "); 
    Serial.println(aByteAr[1]);
    Serial.print("a.2: "); 
    Serial.println(aByteAr[2]);
    Serial.println(aByteZ);
    Serial.print("b: "); 
    Serial.println(bByte);
    Serial.print("c: "); 
    Serial.println(cByte);
    Serial.print("d: "); 
    Serial.println(dByte);
   */


}


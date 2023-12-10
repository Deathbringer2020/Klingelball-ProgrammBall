#include <math.h>

int Eingabe = 1; // for incoming serial data
int valuelenght = 0;
int BLEEingabeArray[20];



void arrayzero(){
      for(int i = 0; i <= 20; i++){
      
      BLEEingabeArray[i] = 0; 

    }
}

int pruefziffer(){
  int pruef = 0; 

  for(int i = 1; i <= valuelenght; i++){  //prüfziffer berechnen
    if(i % 2){
      pruef += BLEEingabeArray[i] * 3;
    } else{ //gerade
      pruef += BLEEingabeArray[i] * 1;
    }

  }
  return pruef
}

void setup() {
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
}

void loop() {
  // send data only when you receive data:

    // read the incoming byte:


    /*  Bluetooth Übergabe 

      xCharacteristic:    //Für an ausschalten 
        1|1|1|1           //die Striche | sind nur damit man es besser erkennen kann. Im eigentlichen nicht dabei.
        1 2 3 4           //Abteilungen (1:, 2:, ...)
        1: Damit es besser übergeben werden kann und keine fehler hat
        2: Ton An/Aus: von 0-1;                   //damit er nicht immer ton ausgibt zum lagern   (vielleicht braucht man nicht weil man ton auf 0 setzen kann)
        3: Tonfrequenz min und max: von 0-1;      //0 bedeutet nur min. 1 bedeutet von min bis Max.
        4: Pipston: von 0-1;                      //0 bedeutet einen Konstantton. 1 bedeutet Pipston.

      yCharacteristic:  //Ton anpassen
        1|255|18000|18000|3000   //die Striche | sind nur damit man es besser erkennen kann. im eigentlichen nicht dabei
        1  2    3     4
        1: Damit es besser übergeben werden kann und keine fehler hat
        2: Lautstärke: von: 0-255;
        3: Tonfrequenz min: von: 50(Hz)-18000(Hz);  //wenn konstant dann nur min 
        4: Tonfrequenz max: von: 50(Hz)-18000(Hz);
        5: PipsFrequenz: von: 50(ms)-3000(ms); 

      yCharacteristic: //LEDs und Pips Frequenz 
        1|255|255|255|255   //die Striche | sind nur damit man es besser erkennen kann. im eigentlichen nicht dabei
        1  2    3     4
        1: Damit es besser übergeben werden kann und keine fehler hat
        2: Helligkeit der LEDS: von: 0-255; 
        3-5: RGB Werte 
          3: Grün: von: 0-255;
          4: Rot: von: 0-255;
          5: Blau: von: 0-255;


  Wegen änderungen doch wahrscheinlich das: 
    ersten zwei stellen wie viele stellen mit denen 
    dann welcher wert geändert wird (1 bis 2 stellig) 
    dann der wert 
    und dann eine prüfziffer 

    */



    Eingabe = xCharacteristic.value();            //xCharacteristic.value() || für testzwecke zahl einfügen
    valuelenght = floor(log10(abs(Eingabe))) + 1;  // floor(log10(abs(Eingabe))) + 1 || für testzwecke zahl einfügen

    for(int i = 0; i <= valuelenght; i++){
      
      BLEEingabeArray[i] = Eingabe % 10; 
      Eingabe = Eingabe / 10;

    }



    for(int i = 0; i <= 4; i++){ // zum überprüfen der eingabe
      Serial.print("Zahl ");
      Serial.print(4-i);
      Serial.print(": ");
      Serial.println(BLEEingabeArray[i]);
    // say what you got:

    }
    Serial.println();




    if((BLEEingabeArray[valuelenght]*10 + BLEEingabeArray[valuelenght-1]) == valuelenght){

      if(BLEEingabeArray[0] == pruefziffer()){

        Serial.println("Working");

      } else{
        Serial.println("Prüfziffer Falsch");
      }


    } else{
      Serial.println("Länge Falsch");
    }


    arrayzero();
    valuelenght = 0;
    Eingabe = 0;
    delay(10000);
  
}


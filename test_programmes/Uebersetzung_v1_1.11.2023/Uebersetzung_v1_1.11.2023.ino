int Eingabe = 1; // for incoming serial data
int Array[4];

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




    */
    Eingabe = 32142;

    for(int i = 0; i <= 4; i++){
      
      Array[4-i] = Eingabe % 10; 
      Eingabe = Eingabe / 10;

    }

    for(int i = 0; i <= 4; i++){
      Serial.print("Zahl ");
      Serial.print(i);
      Serial.print(": ");
      Serial.println(Array[i]);
    // say what you got:

    }
    Serial.println();

    delay(10000);
  
}
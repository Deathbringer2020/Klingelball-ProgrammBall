int Eingabe = 1; // for incoming serial data
int Array[4];

void setup() {
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
}

void loop() {
  // send data only when you receive data:

    // read the incoming byte:

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
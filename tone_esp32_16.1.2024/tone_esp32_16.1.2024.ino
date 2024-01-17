#define Volume_Pin 4
#define ToneUebertroagung1_Pin 5 
#define ToneUebertroagung2_Pin 6
#define BeepUebertroagung_Pin 7

byte Volume;
int Freq;
byte Freq1; 
byte Freq2;
byte Beep; 

unsigned long BeepTime = 0;
bool toggle = 0; 


void setup(){

  ledcSetup(0, 5000, 8);
  ledcAttachPin(32,0); // ledc auf einen pin festlegen und name setzen (0) 

  ledcSetup(1, 5000, 8);
  ledcAttachPin(31,1); // ledc auf einen pin festlegen und name setzen (0) 

  
}

void loop(){

  Volume = analogRead(Volume_Pin);
  Freq1 = analogRead(ToneUebertroagung1_Pin);
  Freq2 = analogRead(ToneUebertroagung2_Pin);
  Beep = analogRead(BeepUebertroagung_Pin);

  Freq = (Freq1 << 8) + Freq2; 

  ledcWriteTone(0, Freq); // frequenz einstellen 

  if(Beep == 0){
    ledcWrite(1, Volume); // lautstärke einstellen (0 bis 255)
  }else{
    if(millis() > BeepTime + Beep*10){
      BeepTime = millis();
      switch(toggle){
        case 0:
          ledcWrite(1, Volume); 
        break; 
        case 1: 
          ledcWrite(1, 0); 
        break; 
      }
      toggle != toggle;
    }

  }


 
}
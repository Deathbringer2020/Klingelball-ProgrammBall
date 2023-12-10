#define delay1 100

void setup(){

  ledcSetup(0, 5000, 8);

  ledcAttachPin(32,0); // ledc auf einen pin festlegen und name setzen (0) 


/*
pinMode(32, 1);
pinMode(33, 1);
*/
}

void loop(){
/*
 // ledcWriteTone(0, 400);
   ledcWrite(0, 200);
  delay(5000);
 // ledcWriteTone(0, 800);
   ledcWrite(0, 255);
  delay(5000);
*/
  ledcWriteTone(0, 1500); // frequenz einstellen 

  ledcWrite(0, 255); // lautstärke einstellen (0 bis 255)
  delay(delay1);
  ledcWrite(0, 0);
  delay(delay1);



/*
  digitalWrite(32, 1);
  digitalWrite(33, 1);
*/
}
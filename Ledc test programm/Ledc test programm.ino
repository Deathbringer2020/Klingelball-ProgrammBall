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
ledcWriteTone(0, 3000); // frequenz einstellen 
for(int i = 0; i <= 300; i++ ){
  ledcWrite(0, i); // lautstärke einstellen (0 bis 255)
  delay(200);
}



/*
  digitalWrite(32, 1);
  digitalWrite(33, 1);
*/
}
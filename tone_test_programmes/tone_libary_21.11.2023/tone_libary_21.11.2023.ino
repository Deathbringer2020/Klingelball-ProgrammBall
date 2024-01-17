unsigned long i= 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
 
  tone(A0, 400);

  i++; 
  if(i > 2000){
    Serial.println("Hi");
    i = 0;
  }



  /*Tone* m_t = new Tone(digitalPinToPinName(pin), frequency, duration);
	m_t->start();
  //time
  m_t->stop();
  delete m_t;*/
  
}

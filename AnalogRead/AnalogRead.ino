  int Messung;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

}

void loop() {
  // put your main code here, to run repeatedly:
  Messung = analogRead(34);
  Serial.println(Messung);
  delay(2000);
}

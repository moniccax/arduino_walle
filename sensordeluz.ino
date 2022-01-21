void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  Serial.print(analogRead(0));
  Serial.print("\n");
  delay(1000);
}

int readPin = A0;
float voltVal;

void setup() {
  pinMode(readPin, INPUT);
  Serial.begin(9600);
  
}

void loop() {
  voltVal = analogRead(readPin);
  Serial.println(voltVal);
  Serial.println("\t");
  delay(1000);
}

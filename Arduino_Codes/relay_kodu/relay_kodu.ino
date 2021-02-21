int del = 1000;
void setup() {
  Serial.begin(9600);
  pinMode(3, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  
  digitalWrite(3, HIGH);
  Serial.println("HIGH");
  delay(del);
  
  digitalWrite(3, LOW);
  Serial.println("LOW");
  Serial.println("");
  delay(del);
} 

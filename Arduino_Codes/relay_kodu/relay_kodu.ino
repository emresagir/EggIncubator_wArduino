int del = 1000;

void setup() {
  Serial.begin(9600);
  pinMode(2, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  
  digitalWrite(2, HIGH);
  Serial.println("HIGH");
  delay(del);
  
  digitalWrite(2, LOW);
  Serial.println("LOW");
  Serial.println("");
  delay(del);
} 

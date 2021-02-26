int resVal = 0;
int senPin = A0;




void setup() {
  Serial.begin(9600);

}

void loop() {
  waterSensor();


  delay(500);
}

void waterSensor(){
  resVal = analogRead(senPin);
  Serial.println(resVal);
  if (resVal <= 100){
    Serial.println("Water Level = Empty");
  }

  else if (resVal > 100 && resVal <= 550){
    Serial.println("Water Level = Low");
  }

  else if (resVal > 550 && resVal <= 620){
    Serial.println("Water Level = Medium");
  }

  else {
    Serial.println("Water Level = High");
  }
  
}

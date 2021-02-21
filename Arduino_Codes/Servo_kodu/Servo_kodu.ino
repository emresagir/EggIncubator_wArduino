#include <Servo.h>

int servoPin = 3;
Servo servo;
int pos = 0;
int del = 5000;

void setup() {
  servo.attach(servoPin);
  Serial.begin(9600);
  servo.write(0);
}

void loop() {
  for (pos; pos <180; pos++){
    servo.write(pos);
    Serial.println(pos);
    delay(50);
  }
  pos = 0;
  delay(del);
}

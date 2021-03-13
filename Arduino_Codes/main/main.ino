//DHT11_fan_transistor_lcd_ntc_ds1302_servo
//codes included

#include <dht.h>
#include <Wire.h> // Library for I2C communication
#include <LiquidCrystal_I2C.h> // Library for LCD
#include <virtuabotixRTC.h>
#include <Servo.h>

dht DHT;
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);
virtuabotixRTC myRTC(9,8,10);
Servo servo;

int dht11Pin = 4;
int fanPin = 7;
int thermistorPin = 0;
int relayPin = 2;
int servoPin = 3;

double humid, temp, correctHumid, correctTemp;

int Vo;
float R1 = 10000;
float logR2, R2, T, Tc, Tf;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;
int pos;
int servoTime;
int servoTimeControl;
int servoFlag = -1;

int del = 500;
void setup() {
  pinMode(fanPin, OUTPUT);
  pinMode(relayPin, OUTPUT);
  digitalWrite(fanPin, LOW);
  digitalWrite(relayPin, LOW);
  servo.attach(servoPin);
  
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  Serial.println("Start");

  servoTimeControl = myRTC.minutes;
  //second, min, hour, day of the week, day of the month, month, year
  //myRTC.setDS1302Time(00, 30, 17, 7, 28, 2, 2021); //Uncomment for recalibrating
}

void loop() {
 timeFunc();
 
 int chk = DHT.read11(dht11Pin);
 
 humid = DHT.humidity;
 temp = DHT.temperature;
 
 
 humidFanControlFunc();
 
 tempFunc();

 tempCheckRelay(Tc);
 
 lcdFunc();

 servoControlFunc();

 
 delay(del);
 
 Serial.print("Servopos = ");
 Serial.println(pos);
}


void humidFanControlFunc(){

  if (humid > 0 || temp > 0){
         /*Serial.print(DHT.humidity);
         Serial.print("humidity ---- temp");
         Serial.println(DHT.temperature);*/
         correctHumid = DHT.humidity; // We dont want to use -999 value
                               // because of the dht11's frequency 
                               //we can read 1 time in a second
                               //with this we only take correct value
         correctTemp = DHT.temperature;
    if(humid > 30){
        
         digitalWrite(fanPin, HIGH);
        
    }
    if(humid <= 25){
        digitalWrite(fanPin, LOW);
    }
    
 }
}

void lcdFunc(){
  Serial.println("LCD part");
  lcd.setCursor(1, 0);
  lcd.print("Humid = ");
  lcd.setCursor(11, 0);
  lcd.print(correctHumid);
  lcd.setCursor(0,1);
  lcd.print("Temp =");
  lcd.setCursor(6, 1);
  lcd.print(correctTemp);
  lcd.setCursor(10,1);
  lcd.print("/");
  lcd.setCursor(11,1);
  lcd.print(Tc);
}


void tempFunc(){
  Vo = analogRead(thermistorPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
  Tc = T - 273.15;
  Tf = (Tc * 9.0)/ 5.0 + 32.0; 

  /*Serial.print("Temperature: "); 
  Serial.print(Tf);
  Serial.print(" F; ");
  Serial.print(Tc);
  Serial.println(" C");*/
}

void tempCheckRelay(float temp){
  if (temp > 38.5){
    digitalWrite(relayPin, LOW);
  }
  if (temp < 37.5){
    digitalWrite(relayPin, HIGH);
  }
}

void timeFunc(){
  myRTC.updateTime();
  Serial.print("Current Date / Time: ");
  Serial.print(myRTC.dayofmonth);
  Serial.print("/");
  Serial.print(myRTC.month);
  Serial.print("/");
  Serial.print(myRTC.year);
  Serial.print("  ");
  Serial.print(myRTC.hours);
  Serial.print(":");
  Serial.print(myRTC.minutes);
  Serial.print(":");
  Serial.println(myRTC.seconds);
  
  servoTime = myRTC.minutes;
  Serial.print("ServoTime = ");
  Serial.println(servoTime);
  
}

void servoFunc(){
  for (pos; pos < 145; pos++){
    servo.write(pos);
    Serial.println(pos);
    delay(50);
  }
  
}

void servoReverseFunc(){
  for (pos; pos > 25; pos--){
    servo.write(pos);
    Serial.println(pos);
    delay(50);
  }
}

void servoControlFunc(){
  if (servoTime == servoTimeControl + 1){
    if(servoFlag == -1){
      servoFunc();
    }
    if(servoFlag == 1){
      servoReverseFunc();
    }
    servoFlag = servoFlag * -1;// Changing rotation 
    Serial.print("ServoFlag = ");
    Serial.println(servoFlag);
  }
  servoTimeControl = servoTime;
  Serial.print("ServoTimeControl = ");
  Serial.println(servoTimeControl);
  
}

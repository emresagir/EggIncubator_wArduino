#include <dht.h>
#include <Wire.h> // Library for I2C communication
#include <LiquidCrystal_I2C.h> // Library for LCD

dht DHT;
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);

int dht11Pin = 4;
int fanPin = 7;
int del = 100;
double humid, temp, correctHumid;


void setup() {
  pinMode(fanPin, OUTPUT);
  digitalWrite(fanPin, LOW);
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
}

void loop() {
 
 int chk = DHT.read11(dht11Pin);
 
 humid = DHT.humidity;
 temp = DHT.temperature;
 
 //Accurate value detection
  HumidFunc();
  if (humid > 0){
         Serial.print(DHT.humidity);
         Serial.print("humidity ---- temp");
         Serial.println(DHT.temperature);
         correctHumid = DHT.humidity; // We dont want to use -999 value
                               // because of the dht11's frequency 
                               //we can read 1 time in a second
                               //with this we only take correct value
    if(humid > 30){
        
         digitalWrite(fanPin, HIGH);
        
    }
    if(humid <= 25){
        digitalWrite(fanPin, LOW);
    }

 //LCD part
  lcd.setCursor(1, 0);
  lcd.print("Humidity = ");
  lcd.setCursor(13, 0);
  lcd.print(correctHumid);
  lcd.setCursor(4,1);
  lcd.print("Temp = ");
  lcd.setCursor(12, 1);
  lcd.print(temp);
 
 delay(del);
 

}


void HumidFunc(){

  if (humid > 0){
         Serial.print(DHT.humidity);
         Serial.print("humidity ---- temp");
         Serial.println(DHT.temperature);
         correctHumid = DHT.humidity; // We dont want to use -999 value
                               // because of the dht11's frequency 
                               //we can read 1 time in a second
                               //with this we only take correct value
    if(humid > 30){
        
         digitalWrite(fanPin, HIGH);
        
    }
    if(humid <= 25){
        digitalWrite(fanPin, LOW);
    }
    
 }
}

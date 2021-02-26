#include <dht.h>
#include <Wire.h> // Library for I2C communication
#include <LiquidCrystal_I2C.h> // Library for LCD

dht DHT;
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);

int dht11Pin = 4;
int fanPin = 7;
int thermistorPin = 0;

double humid, temp, correctHumid, correctTemp;

int Vo;
float R1 = 10000;
float logR2, R2, T, Tc, Tf;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

int del = 500;
void setup() {
  pinMode(fanPin, OUTPUT);
  digitalWrite(fanPin, LOW);
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  Serial.println("Start");
}

void loop() {
 
 int chk = DHT.read11(dht11Pin);
 
 humid = DHT.humidity;
 temp = DHT.temperature;
 
 //Accurate value detection
 humidFanControlFunc();
 
 tempFunc();
 
 //LCD part
 lcdFunc();

 
 delay(del);
 

}


void humidFanControlFunc(){

  if (humid > 0 || temp > 0){
         Serial.print(DHT.humidity);
         Serial.print("humidity ---- temp");
         Serial.println(DHT.temperature);
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

  Serial.print("Temperature: "); 
  Serial.print(Tf);
  Serial.print(" F; ");
  Serial.print(Tc);
  Serial.println(" C");
}

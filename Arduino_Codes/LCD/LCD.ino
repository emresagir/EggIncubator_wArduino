#include <Wire.h> // Library for I2C communication
#include <LiquidCrystal_I2C.h> // Library for LCD

// Wiring: SDA pin is connected to A4 and SCL pin to A5.
// Connect to LCD via I2C, default address 0x27 (A0-A2 not jumpered)
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2); // Change to (0x27,20,4) for 20x4 LCD.

void setup() {
  // Initiate the LCD:
  lcd.init();
  lcd.backlight();
}

void loop() {
  lcd.setCursor(1, 0);
  lcd.print("Humidity = ");
  lcd.setCursor(13, 0);
  //lcd.print(humidity);
  lcd.setCursor(4,1);
  lcd.print("Temp = ");
  lcd.setCursor(12, 1);
  //lcd.print(temperature);
}

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define sensorPin A0

LiquidCrystal_I2C lcd(0x27, 16, 2);  // Address 0x27, 16 columns, 2 rows

// Create a custom heart symbol
byte heart[8] = {
  0b00000,
  0b01010,
  0b11111,
  0b11111,
  0b11111,
  0b01110,
  0b00100,
  0b00000
};

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.createChar(0, heart);  // store custom heart at index 0
  pinMode(sensorPin, INPUT);

  // Static text (only draw once)
  lcd.setCursor(4, 0);
  lcd.print("-I ");
  lcd.write(byte(0));  // print custom heart
  lcd.print(" IT-");
}

void loop() {
  int sensorValue = analogRead(sensorPin);
  float voltage = sensorValue * (5.0 / 1024.0);
  float temperatureC = (voltage - 0.5) * 100.0;

  lcd.setCursor(0, 1);
  lcd.print("67070159 ");
  lcd.print(temperatureC/2, 1); // display 1 decimal place
  lcd.print((char)223);       // degree symbol
  lcd.print("C   ");          // add spaces to overwrite old chars

  delay(1000);
}







//
//#include <Wire.h>
//#include <LiquidCrystal_I2C.h>
//
//#define sensorPin A0
//
//LiquidCrystal_I2C lcd(0x27, 16, 2); // Address 0x27, 16 columns, 2 rows
//
//// Create a custom heart symbol
//byte heart[8] = {
//  0b00000,
//  0b01010,
//  0b11111,
//  0b11111,
//  0b11111,
//  0b01110,
//  0b00100,
//  0b00000
//};
//
//// Create the custom degree symbol ( ° ) - NEW BYTE ARRAY
//byte degree_symbol[8] = {
//  0b01100,
//  0b10010,
//  0b10010,
//  0b01100,
//  0b00000,
//  0b00000,
//  0b00000,
//  0b00000
//};
//
//
//void setup() {
//  Serial.begin(9600);
//  lcd.init();
//  lcd.backlight();
//  lcd.createChar(0, heart);          // Store custom heart at index 0
//  lcd.createChar(1, degree_symbol);  // Store custom degree symbol at index 1 (NEW)
//  pinMode(sensorPin, INPUT);
//
//  // Static text (only draw once)
//  lcd.setCursor(4, 0);
//  lcd.print("-I ");
//  lcd.write(byte(0)); // print custom heart
//  lcd.print(" IT-");
//}
//
//void loop() {
//  int sensorValue = analogRead(sensorPin);
//  float voltage = sensorValue * (5.0 / 1024.0);
//  float temperatureC = (voltage - 0.5) * 100.0;
//
//  lcd.setCursor(0, 1);
//  lcd.print("67070144 ");
//  
//  // แสดงค่าอุณหภูมิ (หาร 2 ตามโค้ดเดิมของคุณ)
//  lcd.print(temperatureC / 2, 1); 
//  
//  // ใช้ Custom Character ที่ index 1 แทน (char)223
//  lcd.write(byte(1)); 
//  
//  lcd.print("C   "); // C และเพิ่มช่องว่างด้านหลังเพื่อลบตัวอักษรเก่า
//  
//  delay(1000);
//}

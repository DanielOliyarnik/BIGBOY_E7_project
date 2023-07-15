#include <Servo.h>
#include "GravityTDS.h"
#include <EEPROM.h>
#include <LiquidCrystal_I2C.h>

#define TdsSensorPin A1
GravityTDS gravityTds;
 
float temperature = 25,tdsValue = 0;

LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address 0x27, 16 column and 2 rows 

Servo servo;
int angle = 10;


void setup() {
  // Setup for sensor arm servo
  servo.attach(8);
   servo.write(angle);
   // Setup for water sensor
  Serial.print("hello");
   Serial.begin(115200);
   gravityTds.setPin(TdsSensorPin);
   gravityTds.setAref(5.0);  //reference voltage on ADC, default 5.0V on Arduino UNO
   gravityTds.setAdcRange(1024);  //1024 for 10bit ADC;4096 for 12bit ADC
   gravityTds.begin();  //initialization
  // Setup for LCD screen 
  lcd.init(); // initialize the lcd
   lcd.backlight();
}

void display(string m) {
  lcd.clear();                 // clear display
  lcd.setCursor(0, 0);         // move cursor to   (0, 0)
  lcd.print(m);        // print message at (0, 0)
  delay(2000);                 // display the above for two seconds
}

void sample() {
    gravityTds.setTemperature(temperature);  // set the temperature and execute temperature compensation
    gravityTds.update();  //sample and calculate
    tdsValue = gravityTds.getTdsValue();  // then get the value
    Serial.print(tdsValue,0);
    Serial.println("ppm");
    delay(1000);
}

void sample_dip() {
  for (angle = 10; angle < 90; angle++){
    servo.write(angle);               
    delay(15);    
  }
  sample()
  for (angle; angle > 0; angle--){
    servo.write(angle);               
    delay(15);    
  }
}
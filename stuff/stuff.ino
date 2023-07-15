#include <AccelStepper.h>
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>
#include "GravityTDS.h"

#define MotorInterfaceType 4

AccelStepper stepper_left(MotorInterfaceType, 4, 5, 6, 7); // Defaults right wheel to (4 pins) on 4, 5, 6, 7
AccelStepper stepper_right(MotorInterfaceType, 10, 11, 12, 13); // Defaults left wheel to (4 pins) on 10, 11, 12, 13

LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address 0x27, 16 column and 2 rows

Servo servo;
int angle = 0;

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

void loop() {
  straight(11350+525);
  //dip
  straight(1025);
  right_turn();
  straight();
  left_turn();
  straight();
  //dip
  straight():
  left_turn();
  straight();
  right_turn();
  straight();

}


int sample() {
    gravityTds.setTemperature(temperature);  // set the temperature and execute temperature compensation
    gravityTds.update();  //sample and calculate
    tdsValue = gravityTds.getTdsValue();  // then get the value
    Serial.print(tdsValue,0);
    Serial.println("ppm");
    delay(1000);
    return tdsValue;
}

//assuming to start at 0 degrees
void sample_dip() {
  for (angle = 10; angle < 90; angle++){
    servo.write(angle);               
    delay(15);    
  }
  reading = sample();
  for (angle; angle > 0; angle--){
    servo.write(angle);               
    delay(15);    
  }
  LCD_Display(reading);
  delay(1000);
}

void straight (ticks) {
	stepper_left.move(ticks);
	stepper_left.setMaxSpeed(500);
	stepper_left.setAcceleration(100);
  stepper_right.move(ticks);
	stepper_right.setMaxSpeed(500);
	stepper_right.setAcceleration(100);

  stepper_left.run();
  stepper_right.run();
}

void left_turn (ticks) {
	stepper_left.move(ticks);
	stepper_left.setMaxSpeed(500);
	stepper_left.setAcceleration(100);
  stepper_left.run();
}

void right_turn (ticks) {
	stepper_right.move(ticks);
	stepper_right.setMaxSpeed(500);
	stepper_right.setAcceleration(100);
  stepper_right.run();
}

void LCD_Display(TDS_value) {

  lcd.clear();                 // clear display
  lcd.setCursor(0, 0);         // move cursor to   (0, 0)
  lcd.print(TDS_value + " mg/L");        // print message at (0, 0)
  lcd.setCursor(0, 2);         // move cursor to   (0, 2)

  if(TDS_value>=600) {
	  lcd.print("UNSAFE!");        // print message at (0, 2)
  } else {
	  lcd.print("SAFE");
  }

  //delay(2000);                 // display the above for two seconds
}

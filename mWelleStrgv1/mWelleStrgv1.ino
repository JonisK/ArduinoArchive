// Adafruit Motor shield library
// copyright Adafruit Industries LLC, 2009
// this code is public domain, enjoy!

#include <AFMotor.h>

AF_DCMotor motor1(2, MOTOR12_64KHZ);
AF_DCMotor motor2(4, MOTOR12_64KHZ);

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Motor test!");

  // turn on motor
  
}

void loop() {
  
  motor1.run(FORWARD);
  for (int i=0; i<256; i++) {
    motor1.setSpeed(i);  
    delay(30);
 }
 
  
  motor2.run(FORWARD);
  for (int i=0; i<256; i++) {
    motor2.setSpeed(i);  
    delay(30);
 }
 
  while (1) {
    delay(5000);
  }
}

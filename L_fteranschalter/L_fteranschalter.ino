#include <AFMotor.h>

AF_DCMotor motor(1);

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Motor test!");

  // turn on motor
  motor.setSpeed(255);
 
  motor.run(RELEASE);
}

void loop() {}

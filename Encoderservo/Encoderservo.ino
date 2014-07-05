
#include <AFMotor.h>

/* Encoder Library - Basic Example
 * http://www.pjrc.com/teensy/td_libs_Encoder.html
 *
 * This example code is in the public domain.
 */

#include <Encoder.h>


// Change these two numbers to the pins connected to your encoder.
//   Best Performance: both pins have interrupt capability
//   Good Performance: only the first pin has interrupt capability
//   Low Performance:  neither pin has interrupt capability
Encoder myEnc(3, 5);
//   avoid using pins with LEDs attached
AF_DCMotor motor(2);

void setup() {
  Serial.begin(9600);
  Serial.println("Basic Encoder Test:");
  motor.setSpeed(55);
 
  motor.run(FORWARD);
}

long oldPosition  = -999;

void loop() {
  
  long newPosition = myEnc.read();
  if (newPosition != oldPosition) {
    oldPosition = newPosition;
    Serial.println(newPosition);
  }
}

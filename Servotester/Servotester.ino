// Sweep
// by BARRAGAN <http://barraganstudio.com> 
// This example code is in the public domain.


#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 
 
int pos = 0;    // variable to store the servo position 
char wahl = 'n';
 
void setup() 
{ 
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
  Serial.begin(9600);
  setPwmFrequency(9, 4);
} 
 
 
void loop() 
{ 
  if (Serial.available()) {
    wahl = Serial.read();
    switch (wahl) {
      case 'n': Serial.println("Neutral");
        if(myservo.read()>90) {
          for(pos = myservo.read(); pos>=90; pos-=1)     // goes from 180 degrees to 0 degrees 
          {                                
            myservo.write(pos);              // tell servo to go to position in variable 'pos' 
            delay(40);                       // waits 15ms for the servo to reach the position 
          }
        }
        if(myservo.read()<90) {
          for(pos = myservo.read(); pos <= 90; pos += 1)  // goes from 0 degrees to 180 degrees 
          {                                  // in steps of 1 degree 
            myservo.write(pos);              // tell servo to go to position in variable 'pos' 
            delay(40);                       // waits 15ms for the servo to reach the position 
          }
        }
        Serial.println("Neutral erreicht."); 
        break;
      case 'g': Serial.println("VollGas");
        for(pos = myservo.read(); pos < 180; pos += 1)  // goes from 0 degrees to 180 degrees 
        {                                  // in steps of 1 degree 
          myservo.write(pos);              // tell servo to go to position in variable 'pos' 
          delay(40);                       // waits 15ms for the servo to reach the position 
        }
        Serial.println("Vollgas erreicht.");
        break;
      case 'b': Serial.println("VollBremsung");
        for(pos = myservo.read(); pos>=1; pos-=1)     // goes from 180 degrees to 0 degrees 
        {                                
          myservo.write(pos);              // tell servo to go to position in variable 'pos' 
          delay(40);                       // waits 15ms for the servo to reach the position 
        }
        Serial.println("Vollbremsung erreicht.");
        break;
      case 'v': Serial.println("Langsam Vorwaerts");
        myservo.write(95);
        break;
      case 'r': Serial.println("Langsam Rückwaerts");
        myservo.write(85);
        break;
      default: Serial.println("default");
        break;
    }
  }
  /*for(pos = 90; pos < 180; pos += 1)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(100);                       // waits 15ms for the servo to reach the position 
  } 
  for(pos = 90; pos>=1; pos-=1)     // goes from 180 degrees to 0 degrees 
  {                                
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(500);                       // waits 15ms for the servo to reach the position 
  }*/
} 

void setPwmFrequency(int pin, int divisor) {
  byte mode;
  if(pin == 5 || pin == 6 || pin == 9 || pin == 10) {
    switch(divisor) {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 64: mode = 0x03; break;
      case 256: mode = 0x04; break;
      case 1024: mode = 0x05; break;
      default: return;
    }
    if(pin == 5 || pin == 6) {
      TCCR0B = TCCR0B & 0b11111000 | mode;
    } else {
      TCCR1B = TCCR1B & 0b11111000 | mode;
    }
  } else if(pin == 3 || pin == 11) {
    switch(divisor) {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 32: mode = 0x03; break;
      case 64: mode = 0x04; break;
      case 128: mode = 0x05; break;
      case 256: mode = 0x06; break;
      case 1024: mode = 0x7; break;
      default: return;
    }
    TCCR2B = TCCR2B & 0b11111000 | mode;
  }
}

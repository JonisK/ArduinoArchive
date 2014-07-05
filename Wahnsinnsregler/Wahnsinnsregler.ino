// Erstlingswerk vom 07.06.13 kurz nach Tagesbeginn
// von Fritz und Jonis

#include <AFMotor.h>

AF_DCMotor motor(2);
int w = 0;
int y = 0;
int e = 0;
int u = 0;
int u_stern = 0;

int piny = 4;
int pinw = 5;

void setup() {
  //Serial.begin(115200);           // set up Serial library at 9600 bps
  //Serial.println("Geiler Regler");

  // turn on motor
  motor.setSpeed(255);
 
  motor.run(RELEASE);
}

void loop() {
  y = analogRead(piny);
  w = analogRead(pinw);
  e = w-y;
  u = e/2;
  //Serial.println(y);
  //Serial.println(w);
  //Serial.println(e);
  //Serial.println(u);
  
  if (u>15) {
    motor.run(FORWARD);
    //Serial.println("FORWARD");
    u_stern = map(u, 0,255, 24, 255);
    motor.setSpeed(u_stern);
  }
  else if (u<-15){
    motor.run(BACKWARD);
    //Serial.println(BACKWARD);
    u_stern = map(u, 0,-255, -24, -255);
    motor.setSpeed(-u_stern);
    //u=-u;
  }
  else {
    motor.run(RELEASE);
  }
  //Serial.println("\n\n\n");
  
  
  //delay(200);
}

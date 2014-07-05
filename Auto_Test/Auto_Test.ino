#include <Encoder.h>
#include <Servo.h> 

Encoder eleft(2, 4), eright(3,5);
Servo left, right;

byte lamp1 = 6, lamp2 = 7, lamp3 = 14, lamp4 = 15, lamp5 = 16, lamp6 = 17, lamp7 = 18;

int pos = 0;    // variable to store the servo position 
int sspeed = 98;
void setup() 
{ 
  Serial.begin(9600);
  
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(15, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(17, OUTPUT);
	pinMode(18, OUTPUT);
	pinMode(19, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  digitalWrite(7, HIGH);
  digitalWrite(8, HIGH);
  digitalWrite(11, HIGH);
  digitalWrite(12, HIGH);
  digitalWrite(13, HIGH);
  digitalWrite(17, HIGH);
  digitalWrite(14, HIGH);
  digitalWrite(15, HIGH);
	digitalWrite(18, HIGH);
	digitalWrite(19, HIGH);
  delay(1000);
//  digitalWrite(12, LOW);
//  digitalWrite(13, LOW);
//  digitalWrite(14, LOW);
//  digitalWrite(15, LOW);
//  digitalWrite(16, LOW);
//  digitalWrite(17, LOW);
//  digitalWrite(18, LOW);
//  digitalWrite(19, LOW);
  delay(1000);
  left.attach(9);  // attaches the servo on pin 9 to the servo object 
  right.attach(10);
  left.write(92);
  right.write(98);
//  delay(10000000);
} 
 
 
void loop() 
{ 
  
//   left.write(45+92);
//   right.write(-45+98);
//   delay(4000);
//   left.write(-45+92);
//   right.write(45+98);
//   delay(2000);
//   left.write(45+92);
//   right.write(45+98);
//   delay(4000);
} 

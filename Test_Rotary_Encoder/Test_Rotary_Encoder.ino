/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int up = A1;
int supply = A2;
int down = A3;
int value = 0;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(up, INPUT);
  pinMode(supply, OUTPUT);
  pinMode(down, INPUT);
  digitalWrite(supply, LOW);
  digitalWrite(up, HIGH);
  digitalWrite(down, HIGH);
  Serial.begin(9600);
  
}

// the loop routine runs over and over again forever:
void loop() {
  if(digitalRead(up) == LOW) {
    Serial.print("Voltage: ");
    Serial.println(analogRead(A0));
    Serial.println(value);
    value++;
    delay(100);
  }
  else if (digitalRead(down) == LOW) {
    Serial.print("Voltage: ");
    Serial.println(analogRead(A2));
    Serial.println(value);
    value--;
    delay(100);
  }
  //Serial.println(value);
  
  //delay(10);
  
}

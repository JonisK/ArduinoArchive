/*
  Dim
  
  Lowers the brightness of the LED by switching it on and off 
  many times per second
 */ 

void setup() {                
  // initialize the digital pin as an output.
  // Pin 13 has an LED connected on most Arduino boards:
  pinMode(13, OUTPUT); 
  //float brightness = 0.42;
  //float brightness2 = 22.0 * brightness;
  Serial.begin(9600);
}

float brightness = 0.60;

void loop() {
  digitalWrite(13, HIGH);  // set the LED on
  Serial.println("LED on");
  delay(1);              // wait for a second
  digitalWrite(13, LOW);    // set the LED off
  Serial.println("LED off");
  delay(brightness*22.0);              // wait for a second
}

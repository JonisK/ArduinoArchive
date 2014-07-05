// Do not remove the include below
#include "Datenlogger-Rakete.h"


//The setup function is called once at startup of the sketch
void setup()
{
	// initialize the digital pin as an output.
	  // Pin 13 has an LED connected on most Arduino boards:
	  pinMode(13, OUTPUT);
	  //float brightness = 0.42;
	  //float brightness2 = 22.0 * brightness;

}

// The loop function is called in an endless loop
void loop()
{
	float brightness = 0.60;
	digitalWrite(13, HIGH);  // set the LED on

	  delay(1);              // wait for a second
	  digitalWrite(13, LOW);    // set the LED off

	  delay(brightness*22.0);              // wait for a second
//Add your repeated code here
}

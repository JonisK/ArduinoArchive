/*
* iPrototype.nl
* Compatible met de Arduino IDE 1.0
* Library versie: 0.1
* 
* Dit voorbeeld gebruikt pin 2 en 3 van de Pin Expander (23 en 24 van de MCP23016)
* 
* Aansluitschema's kunt u vinden op https://iprototype.nl/products/components/ics/pinexpander
*/

#include <IOexpander.h>
#include <Wire.h>;
#include <inttypes.h>;

int wahl = 0;
IOexpander e(0x24);

void setup()
{
  Serial.begin(9600);
  e.init();
  e.pinMode(7, OUTPUT);
  e.pinMode(8, OUTPUT);
  e.pinMode(9, OUTPUT);
  e.pinMode(10, OUTPUT);
  e.pinMode(11, OUTPUT);  
  e.pinMode(15, OUTPUT);
}

void loop()
{
  if (Serial.available()) {
    wahl = Serial.read() - 48;
    Serial.println(wahl);
    Serial.println(wahl+6);
    e.digitalWrite(wahl+6, HIGH);
    delay(48000);
    e.digitalWrite(wahl+6, LOW);
  }
}

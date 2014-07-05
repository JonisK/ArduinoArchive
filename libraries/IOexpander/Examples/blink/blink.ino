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

IOexpander e(0x20);

void setup()
{
  e.init();
  e.pinMode(2, OUTPUT);
  e.pinMode(3, OUTPUT);
}

void loop()
{
  e.digitalWrite(2, HIGH);
  e.digitalWrite(3, LOW);
  delay(500);
  e.digitalWrite(2, LOW);
  e.digitalWrite(3, HIGH);
  delay(500);
}

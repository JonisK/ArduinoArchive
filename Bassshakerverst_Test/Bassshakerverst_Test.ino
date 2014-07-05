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
  e.pinMode(6, OUTPUT);
  e.pinMode(7, INPUT);
  Serial.begin(9600);
}

void loop()
{
  Serial.println(e.digitalRead(7));
  delay(300);
//  if(e.digitalRead(7)==1) {
//    Serial.println("Der BSV ist aus und wird in 3 sek angeschaltet.");
//    delay(3000);
//    e.digitalWrite(6, HIGH);
//    delay(100);
//    e.digitalWrite(6, LOW);
//  }else{
//    Serial.println("Der BSV ist an und wird in 3 sek ausgeschaltet.");
//    delay(3000);
//    e.digitalWrite(6, HIGH);
//    delay(100);
//    e.digitalWrite(6, LOW);
//  }
//  delay(3000);
}

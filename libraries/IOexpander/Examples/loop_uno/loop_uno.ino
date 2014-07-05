#include <IOexpander.h>
#include <Wire.h>;
#include <inttypes.h>;

IOexpander e(0x20, 14);

int i;

void setup()
{
  e.init();
  for(i = 0; i <= 30; i++)
  {
    e.pinMode(i, OUTPUT);
  }
}

void loop()
{
  for(i = 0; i <= 30; i++)
  {
    e.digitalWrite(i, HIGH);
    delay(100);
  }
  for(i = 30; i >= 0; i--)
  {
    e.digitalWrite(i, LOW);
    delay(100);
  }
  
  delay(500);
}

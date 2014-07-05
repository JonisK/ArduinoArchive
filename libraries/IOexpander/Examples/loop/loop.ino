#include <IOexpander.h>
#include <Wire.h>;
#include <inttypes.h>;

IOexpander e(0x20);

int i;

void setup()
{
  e.init();
}

void loop()
{
  for(i = 0; i <= 15; i++)
  {
    e.digitalWrite(i, HIGH);
    delay(100);
  }
  for(i = 15; i >= 0; i--)
  {
    e.digitalWrite(i, LOW);
    delay(100);
  }
  
  delay(500);
}

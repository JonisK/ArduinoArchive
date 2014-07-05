
#include <Wire.h>;

uint8_t port0 = 0;
uint8_t port1 = 0;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  Serial.println("Starting to read");
  delay(200);
  Wire.beginTransmission(0x21);
  Wire.write(0x00); //select General purpose register
  if(Wire.endTransmission() > 0) Serial.print("false");
  
  Wire.requestFrom(0x21, 2); //request two bytes, register gp1 and 1-2
    if(Wire.available() == 2){
	port0 = Wire.read();  //recv REGISTER_GP0
	port1 = Wire.read();  //recv REGISTER_GP1
        Serial.println(port0);
        Serial.println(port1);
    }
    delay(800);
}

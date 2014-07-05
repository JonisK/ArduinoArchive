#include <IOexpander.h>
#include <Wire.h>
#include <HardwareSerial.h>

IOexpander::IOexpander(uint8_t address)
{
	addr = address;
	temp = 0;
	pinModes0 = 0x00;
	pinModes1 = 0x00;
	pinStates0 = 0x00;
	pinStates1 = 0x00;
	readRegister = 0x02;
	hardStartPin = 0;
}

IOexpander::IOexpander(uint8_t address, uint8_t startPin)
{
	addr = address;
	temp = 0;
	pinModes0 = 0x00;
	pinModes1 = 0x00;
	pinStates0 = 0x00;
	pinStates1 = 0x00;
	readRegister = 0x02;
	hardStartPin = startPin;
}

void IOexpander::init()
{
	Wire.begin();
	setPinModes(pinModes0, pinModes1);
	Serial.begin(9600);
}

void IOexpander::pinMode(uint8_t pin, bool mode)
{
	if(pin < hardStartPin)
	{
		if(mode)
		{
			if(pin > 7)
				DDRB |= (1 << pin - 8);
			else 
				DDRD |= 1 << pin;
		}else 
		{
			if(pin > 7)
				DDRB &= ~(1 << pin - 8);
			else
				DDRD &= ~(1 << pin);
		}
	}else 
	{
		pin -= hardStartPin;
		if(!mode)
		{
			if(pin > 7)
			{
				temp = 1 << (pin - 8);
				pinModes1 |= temp;
			}else 
			{
				temp = 1 << pin;
				pinModes0 |= temp;
			}
	  }else
	  {
	  	if(pin > 7)
			{
				temp = 1 << (pin - 8);
				temp = ~temp;
				pinModes1 &= temp;
			}else 
			{
				temp = 1 << pin;
				temp = ~temp;
				pinModes0 &= temp;
			}
		}
	  
	  setPinModes(pinModes0, pinModes1);
	}
}

void IOexpander::digitalWrite(uint8_t pin, bool value)
{
	if(pin < hardStartPin)
	{
		if(value)
		{
			if(pin > 7)
				PORTB |= (1 << pin - 8);
			else 
				PORTD |= 1 << pin;
		}else 
		{
			if(pin > 7)
				PORTB &= ~(1 << pin - 8);
			else
				PORTD &= ~(1 << pin);
		}
	}else 
	{
		pin -= hardStartPin;
		if(value)
		{
			if(pin > 7)
			{
				temp = 1 << (pin - 8);
				pinStates1 |= temp;
			}else 
			{
				temp = 1 << pin;
				pinStates0 |= temp;
			}
		}else
		{
			if(pin > 7)
			{
				temp = 1 << (pin - 8);
				temp = ~temp;
				pinStates1 &= temp;
			}else 
			{
				temp = 1 << pin;
				temp = ~temp;
				pinStates0 &= temp;
			}
		}
		
		setPinStates(pinStates0, pinStates1);
	}
}

int IOexpander::digitalRead(uint8_t pin)
{
	if(pin < hardStartPin)
	{
		if(pin > 7)
    {
      if((PINB & (1 << pin - 8)) == 1 << pin - 8)
      	return 1;
    }else
    {
      if((PIND & (1 << pin)) == 1 << pin)
      	return 1;
    }
    return 0;
	}else 
	{
		//Serial.println("Hello, it's me!");
		pin -= hardStartPin;
		Wire.requestFrom(addr, readRegister);
		while(Wire.available() < 2)
			;
	  if(Wire.available() == 2)
		{
			port1 = Wire.read();
			port0 = Wire.read();
			
			Serial.println(port1);
			Serial.println(port0);
			
			if(pin > 7)
	    {
	      if((port1 & (1 << pin - 8)) == 1 << pin - 8)
	      	return 1;
	    }else
	    {
	      if((port0 & (1 << pin)) == 1 << pin)
	      	return 1;
	    }
	    return 0;
		}
	}
} 

bool IOexpander::sendData(uint8_t byte1, uint8_t byte2)
{
  Wire.beginTransmission(addr);
  Wire.write(byte1);
  Wire.write(byte2);
  if(Wire.endTransmission() == 0)
		return true;
  else
		return false;
}

void IOexpander::setPinModes(uint8_t pinModesPort0, uint8_t pinModesPort1)
{
	sendData(0x06, pinModesPort0);
	sendData(0x07, pinModesPort1);
}

void IOexpander::setPinStates(uint8_t pinStatesPort0, uint8_t pinStatesPort1)
{
	sendData(0x00, pinStatesPort0);
	sendData(0x01, pinStatesPort1);
}
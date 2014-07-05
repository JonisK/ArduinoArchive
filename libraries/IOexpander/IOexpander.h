
#ifndef IOexpander_h
#define IOexpander_h

#include <inttypes.h>

class IOexpander
{
  public:
  uint8_t addr;
  uint8_t pinModes0;
  uint8_t pinModes1;
  uint8_t pinStates0;
  uint8_t pinStates1;
	bool sendData(uint8_t byte1, uint8_t byte2);
	void setPinModes(uint8_t pinModesPort0, uint8_t pinModesPort1);
	void setPinStates(uint8_t pinStatesPort0, uint8_t pinStatesPort1);
	uint8_t temp;
	uint8_t port0;
	uint8_t port1;
	uint8_t readRegister;
	uint8_t hardStartPin;
	

  IOexpander(uint8_t address);
  IOexpander(uint8_t address, uint8_t startPin);
  void init();
	void pinMode(uint8_t pin, bool mode);
	void digitalWrite(uint8_t pin, bool value);
	int digitalRead(uint8_t pin);
};

#endif


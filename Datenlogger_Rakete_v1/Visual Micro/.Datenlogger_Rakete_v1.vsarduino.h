/* 
	Editor: http://www.visualmicro.com
	        arduino debugger, visual micro +, free forum and wiki
	
	Hardware: Arduino Mega or Mega 2560 w/ ATmega2560 (Mega 2560), Platform=avr, Package=arduino
*/

#define __AVR_ATmega2560__
#define ARDUINO 101
#define ARDUINO_MAIN
#define F_CPU 16000000L
#define __AVR__
#define __cplusplus
extern "C" void __cxa_pure_virtual() {;}

//
//
void writeByte(byte thisAdress, byte thisValue, int thisSS);
void verifiedWrite(byte thisAdress, byte thisValue, int thisSS);
byte readByte(byte thisAdress, int thisSS);
unsigned int readData();

#include "C:\Program Files (x86)\Arduino\hardware\arduino\avr\variants\mega\pins_arduino.h" 
#include "C:\Program Files (x86)\Arduino\hardware\arduino\avr\cores\arduino\arduino.h"
#include "C:\Users\Jonis\Documents\Arduino\Datenlogger_Rakete_v1\Datenlogger_Rakete_v1.ino"

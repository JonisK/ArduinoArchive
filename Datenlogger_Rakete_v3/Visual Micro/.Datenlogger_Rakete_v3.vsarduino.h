/* 
	Editor: http://www.visualmicro.com
	        arduino debugger, visual micro +, free forum and wiki
	
	Hardware: Arduino Nano w/ ATmega328, Platform=avr, Package=arduino
*/

#define __AVR_ATmega328P__
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
int readData();
int dataAvailable();

#include "G:\Programme\Arduino\hardware\arduino\avr\variants\eightanaloginputs\pins_arduino.h" 
#include "G:\Programme\Arduino\hardware\arduino\avr\cores\arduino\arduino.h"
#include "G:\Eigene Dateien\Arduino\Datenlogger_Rakete_v3\Datenlogger_Rakete_v3.ino"

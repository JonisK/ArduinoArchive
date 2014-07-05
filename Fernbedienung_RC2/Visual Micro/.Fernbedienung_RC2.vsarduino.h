/* 
	Editor: http://www.visualmicro.com
	        arduino debugger, visual micro +, free forum and wiki
	
	Hardware: Arduino Duemilanove or Diecimila w/ ATmega328, Platform=avr, Package=arduino
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
void writeBit(byte addr, byte bitnumber, boolean data);
void ereignis();
void encoder();

#include "G:\Programme\Arduino\hardware\arduino\avr\variants\standard\pins_arduino.h" 
#include "G:\Programme\Arduino\hardware\arduino\avr\cores\arduino\arduino.h"
#include "G:\Eigene Dateien\Arduino\Fernbedienung_RC2\Fernbedienung_RC2.ino"
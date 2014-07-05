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

static unsigned long now ();
static void activityLed (byte on);
static void showNibble (byte nibble);
static void showByte (byte value);
static void addCh (char* msg, char c);
static void addInt (char* msg, word v);
static void saveConfig ();
static byte bandToFreq (byte band);
static void ookPulse(int on, int off);
static void fs20sendBits(word data, byte bits);
static void fs20cmd(word house, byte addr, byte cmd);
static void kakuSend(char addr, byte device, byte on);
static byte df_present ();
static void df_enable ();
static void df_disable ();
static byte df_xfer (byte cmd);
void df_command (byte cmd);
static void df_deselect ();
static void df_writeCmd (byte cmd);
void df_read (word block, word off, void* buf, word len);
void df_write (word block, const void* buf);
void df_flush ();
static void df_wipe ();
static void df_erase (word block);
static word df_wrap (word page);
static void df_saveBuf ();
static void df_append (const void* buf, byte len);
static void scanForLastSave ();
static void df_initialize ();
static void discardInput ();
static void df_dump ();
static word scanForMarker (word seqnum, long asof);
static void df_replay (word seqnum, long asof);
static void showString (PGM_P s);
static void showHelp ();
static void handleInput (char c);
void displayVersion(uint8_t newline );
//
//

#include "G:\Programme\Arduino\hardware\arduino\avr\variants\standard\pins_arduino.h" 
#include "G:\Programme\Arduino\hardware\arduino\avr\cores\arduino\arduino.h"
#include "G:\Eigene Dateien\Arduino\libraries\JeeLib\examples\RF12\RF12demo\RF12demo.ino"

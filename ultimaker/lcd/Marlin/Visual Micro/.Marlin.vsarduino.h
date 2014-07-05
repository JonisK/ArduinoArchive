/* 
	Editor: http://www.visualmicro.com
	        arduino debugger, visual micro +, free forum and wiki
	
	Hardware: Arduino Mega ADK, Platform=avr, Package=arduino
*/

#define __AVR_ATmega2560__
#define ARDUINO 101
#define ARDUINO_MAIN
#define F_CPU 16000000L
#define __AVR__
#define __cplusplus
extern "C" void __cxa_pure_virtual() {;}


#include "C:\Program Files (x86)\Arduino\hardware\arduino\avr\variants\mega\pins_arduino.h" 
#include "C:\Program Files (x86)\Arduino\hardware\arduino\avr\cores\arduino\arduino.h"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\lcd\Marlin\Marlin.ino"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\lcd\Marlin\Configuration.h"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\lcd\Marlin\ConfigurationStore.cpp"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\lcd\Marlin\ConfigurationStore.h"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\lcd\Marlin\Configuration_adv.h"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\lcd\Marlin\DOGMbitmaps.h"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\lcd\Marlin\LiquidCrystalRus.cpp"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\lcd\Marlin\LiquidCrystalRus.h"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\lcd\Marlin\Marlin.h"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\lcd\Marlin\MarlinSerial.cpp"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\lcd\Marlin\MarlinSerial.h"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\lcd\Marlin\Marlin_main.cpp"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\lcd\Marlin\Sd2Card.cpp"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\lcd\Marlin\Sd2Card.h"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\lcd\Marlin\Sd2PinMap.h"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\lcd\Marlin\SdBaseFile.cpp"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\lcd\Marlin\SdBaseFile.h"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\lcd\Marlin\SdFatConfig.h"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\lcd\Marlin\SdFatStructs.h"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\lcd\Marlin\SdFatUtil.cpp"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\lcd\Marlin\SdFatUtil.h"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\lcd\Marlin\SdFile.cpp"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\lcd\Marlin\SdFile.h"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\lcd\Marlin\SdInfo.h"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\lcd\Marlin\SdVolume.cpp"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\lcd\Marlin\SdVolume.h"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\lcd\Marlin\Servo.cpp"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\lcd\Marlin\Servo.h"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\lcd\Marlin\cardreader.cpp"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\lcd\Marlin\cardreader.h"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\lcd\Marlin\dogm_font_data_marlin.h"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\lcd\Marlin\dogm_lcd_implementation.h"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\lcd\Marlin\fastio.h"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\lcd\Marlin\language.h"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\lcd\Marlin\motion_control.cpp"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\lcd\Marlin\motion_control.h"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\lcd\Marlin\pins.h"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\lcd\Marlin\planner.cpp"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\lcd\Marlin\planner.h"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\lcd\Marlin\speed_lookuptable.h"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\lcd\Marlin\stepper.cpp"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\lcd\Marlin\stepper.h"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\lcd\Marlin\temperature.cpp"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\lcd\Marlin\temperature.h"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\lcd\Marlin\thermistortables.h"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\lcd\Marlin\ultralcd.cpp"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\lcd\Marlin\ultralcd.h"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\lcd\Marlin\ultralcd_implementation_hitachi_HD44780.h"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\lcd\Marlin\ultralcd_st7920_u8glib_rrd.h"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\lcd\Marlin\watchdog.cpp"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\lcd\Marlin\watchdog.h"

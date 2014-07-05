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


#include "C:\Program Files (x86)\Arduino\hardware\arduino\avr\variants\mega\pins_arduino.h" 
#include "C:\Program Files (x86)\Arduino\hardware\arduino\avr\cores\arduino\arduino.h"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\12864\12864 testfile\Marlin\Marlin.ino"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\12864\12864 testfile\Marlin\Configuration.h"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\12864\12864 testfile\Marlin\ConfigurationStore.cpp"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\12864\12864 testfile\Marlin\ConfigurationStore.h"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\12864\12864 testfile\Marlin\Configuration_adv.h"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\12864\12864 testfile\Marlin\DOGMbitmaps.h"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\12864\12864 testfile\Marlin\LiquidCrystalRus.cpp"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\12864\12864 testfile\Marlin\LiquidCrystalRus.h"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\12864\12864 testfile\Marlin\Marlin.h"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\12864\12864 testfile\Marlin\MarlinSerial.cpp"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\12864\12864 testfile\Marlin\MarlinSerial.h"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\12864\12864 testfile\Marlin\Marlin_main.cpp"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\12864\12864 testfile\Marlin\Sd2Card.cpp"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\12864\12864 testfile\Marlin\Sd2Card.h"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\12864\12864 testfile\Marlin\Sd2PinMap.h"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\12864\12864 testfile\Marlin\SdBaseFile.cpp"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\12864\12864 testfile\Marlin\SdBaseFile.h"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\12864\12864 testfile\Marlin\SdFatConfig.h"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\12864\12864 testfile\Marlin\SdFatStructs.h"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\12864\12864 testfile\Marlin\SdFatUtil.cpp"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\12864\12864 testfile\Marlin\SdFatUtil.h"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\12864\12864 testfile\Marlin\SdFile.cpp"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\12864\12864 testfile\Marlin\SdFile.h"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\12864\12864 testfile\Marlin\SdInfo.h"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\12864\12864 testfile\Marlin\SdVolume.cpp"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\12864\12864 testfile\Marlin\SdVolume.h"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\12864\12864 testfile\Marlin\Servo.cpp"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\12864\12864 testfile\Marlin\Servo.h"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\12864\12864 testfile\Marlin\cardreader.cpp"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\12864\12864 testfile\Marlin\cardreader.h"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\12864\12864 testfile\Marlin\dogm_font_data_marlin.h"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\12864\12864 testfile\Marlin\dogm_lcd_implementation.h"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\12864\12864 testfile\Marlin\fastio.h"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\12864\12864 testfile\Marlin\language.h"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\12864\12864 testfile\Marlin\motion_control.cpp"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\12864\12864 testfile\Marlin\motion_control.h"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\12864\12864 testfile\Marlin\pins.h"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\12864\12864 testfile\Marlin\planner.cpp"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\12864\12864 testfile\Marlin\planner.h"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\12864\12864 testfile\Marlin\speed_lookuptable.h"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\12864\12864 testfile\Marlin\stepper.cpp"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\12864\12864 testfile\Marlin\stepper.h"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\12864\12864 testfile\Marlin\temperature.cpp"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\12864\12864 testfile\Marlin\temperature.h"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\12864\12864 testfile\Marlin\thermistortables.h"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\12864\12864 testfile\Marlin\ultralcd.cpp"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\12864\12864 testfile\Marlin\ultralcd.h"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\12864\12864 testfile\Marlin\ultralcd_implementation_hitachi_HD44780.h"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\12864\12864 testfile\Marlin\ultralcd_st7920_u8glib_rrd.h"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\12864\12864 testfile\Marlin\watchdog.cpp"
#include "C:\Users\Jonis\Documents\Arduino\ultimaker\12864\12864 testfile\Marlin\watchdog.h"

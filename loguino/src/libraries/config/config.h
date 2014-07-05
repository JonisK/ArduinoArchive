/* Copyright 2011 David Irvine
 * 
 * This file is part of Loguino
 *
 * Loguino is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Loguino is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 
 * You should have received a copy of the GNU General Public License
 * along with Loguino.  If not, see <http://www.gnu.org/licenses/>.
 * 
 * $Rev: 123 $:   
 * $Author: irvined $: 
 * $Date: 2012-04-08 23:04:29 +0200 (Sun, 08 Apr 2012) $:  
 
 */
#ifndef CONFIG_H
#define CONFIG_H
#include <Arduino.h>




//! Enable the GPS Poller
#define ENABLE_GPS_POLLER
//! Sets the serial device of the GPS
#define GPS_SERIAL_DEV Serial2

//! Set the BAUD rate of the GPS device
#define GPS_SERIAL_DEV_SPEED 4800


//! Enable the Dummy Poller
#define ENABLE_DUMMY_POLLER




//! Enable the Digital Input Poller
#define ENABLE_DIGITAL_POLLER
//! A list, comma seperated of digital pins that will be read for a value.
#define DIGITAL_PINS 31,32,33,34,35,36
//! A list, comma seperated of pins that will be held high.
#define INVERT_DIGITAL_PINS 32,33




//! Enable the Analog Input Poller
#define ENABLE_ANALOG_POLLER
//! A list, comma seperated of digital pins that will be read for a value.
#define ANALOG_PINS 2,3,4



//! Enable the serial output module
#define ENABLE_SERIAL_OUTPUT
//! Serial Port to use, select 1 of the following:
#define SO_SERIAL_PORT Serial

//! The BAUD rate to log at, default is 115200	
#define SO_SERIAL_PORT_SPEED 115200





//! Enable the ITG 3200 Poller
#define ENABLE_ITG3200_POLLER
//! The I2C Address of the itg3200
#define ITG3200_ADDRESS 0x69




//! Enable the LIS331 Poller
#define ENABLE_LIS331_POLLER
/**
 * The Slave ADdress (SAD) associated to the LIS331HH is 001100xb. SDO/SA0 pad 
 * can be used to modify less significant bit of the device address. If SA0 pad 
 * is connected to voltage supply, LSb is ‘1’ (address 0011001b) else if SA0 pad 
 * is connected to ground, LSb value is ‘0’ (address 0011000b). This solution 
 * permits to connect and address two different accelerometers to the same I2C 
 * lines.
 * 		
 * Bus address is either 24 or 25 
 */
#define LIS_BUS_ADDRESS 25




//! Enable the SD Output Module
#define ENABLE_SD_OUTPUT
//! The pin that the output LED is connected to, this lights up when 
//! the SD card module has found a card, and is writing data to it.
#define SD_ACTIVE_PIN 9

//! Enable the MegaSquirt Poller
#define ENABLE_MS_POLLER
//! The number of polls to skip after a timeout
#define MS_WAIT_TIME 100

//! When the megasquirt is online, this pin will be high.  Used to show a status LED.
#define MS_STATUS_PIN 9


#endif

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
 * $Rev: 127 $:   
 * $Author: irvined $: 
 * $Date: 2012-04-09 10:20:42 +0200 (Mon, 09 Apr 2012) $:  
 
 */
#ifndef DIGITALPOLLER_H
#define DIGITALPOLLER_H

#include <Arduino.h>
#include <config.h>
#ifndef SD_ACTIVE_PIN
#error Define SD_ACTIVE_PIN to the pin that will go high when the SD module is writing to a file.
#endif
#include "SD.h"
#include <message.h>
#include <logger.h>

void SDOut();
void SDOutBegin();
void SDOutFlush();


#endif

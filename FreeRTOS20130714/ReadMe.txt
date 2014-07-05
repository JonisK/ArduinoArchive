You must use Arduino 1.5.2 to run FreeRTOS on the Arduino Due. 

A patch is included for 1.5.1 but it is no longer supported.

The documentation for FreeRTOS is located here:

http://www.freertos.org/

FreeRTOS is version 7.4.2

These libraries were tested with Arduino 1.05 for AVR boards, Arduino 1.5.2
for Due and the 1.15/1.0.5 version of the Teensy 3.0 software.

To install these libraries and run the FreeRTOS examples, copy the
included libraries to your libraries folder.

A version of SdFat is included.  For the current version go to:

http://code.google.com/p/sdfatlib/downloads/list

Please read FreeRTOS.html for more information.

See FreeRTOS_API.html for API documentation.

__malloc_heap_end must be defined to use dynamic memory in AVR tasks.
Add this as the first line of setup():

  // Insure malloc works in tasks
  __malloc_heap_end = (char*)RAMEND;

See: http://www.nongnu.org/avr-libc/user-manual/malloc.html

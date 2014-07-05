/**
 * \file
 * \brief FreeRTOS for AVR Arduino
 */
#include <FreeRTOS_AVR.h>
#include <stdlib.h>
/** current begining of heap */
extern char *__brkval;

#if defined(CORE_TEENSY) || ARDUINO == 104 || ARDUINO == 152
extern char __bss_end;
/** \return free heap size */
size_t freeHeap() {
  return (char*)RAMEND - (__brkval ? __brkval : &__bss_end)+ 1;
}
#else  // CORE_TEENSY
/** \return free heap size */
size_t freeHeap() {
  return (char*)RAMEND - (__brkval ? __brkval : __malloc_heap_start) + 1;
}
#endif  // CORE_TEENSY
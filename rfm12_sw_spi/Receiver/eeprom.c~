/**
 * @file eeprom.c
 * 
 *
 */

#ifdef __16f628a
  #include <pic16f628a.h>
#endif
#ifdef __16f88
#include <pic16f88.h>
#endif

#include "eeprom.h"


/**
 * @fn void eeprom_write
 * @brief writes a string onto EEPROM position
 * @param pos EEPROM position
 * @param str string to be written
 * @param len length of the string
 */
void eeprom_write(int pos,char *str,int len){
  int i;
  
  for(i=0;i<len;i++){     // each char in str
    EEADR=pos++;          // EEPROM position
    EEDATA=str[i];        // set the data to write
    WREN=1;               // enable writes
    EEPROM_WRITE();       // write a byte
    while(WR);            // wait for write to finish
    WREN=0;               // disable writes
  }
}


/**
 * @fn void eeprom_read
 * @brief read a string from EEPROM position
 * @param pos EEPROM position
 * @param str string to be written
 * @param len length of the string
 */
void eeprom_read(int pos,char *str,int len){
  int i;
  
  for(i=0;i<len;i++){             // each char in str
    str[i]=EEPROM_READ(pos++);    // fill str with EEPROM data at position pos
  }
}
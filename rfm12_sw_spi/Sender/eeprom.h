/**
 * @file eeprom.h
 * 
 *
 */

#ifndef EEPROM_H
#define EEPROM_H

/** This EXACT SEQUENCE of instructions is needed, any deviation will
 *  cause the write to FAIL!  The PIC even counts the number of 
 *  instructions to check if you did this right!  This means we need 
 *  inline ASM, C isn't going to get it Just Right(tm).
 */
#define EEPROM_WRITE()  do {        \
      EECON2=0x00;  /* Get in right bank */   \
      __asm MOVLW 0x55    __endasm;   \
      __asm MOVWF EECON2    __endasm;   \
      __asm MOVLW 0xaa    __endasm;   \
      __asm MOVWF EECON2    __endasm;   \
      __asm BSF EECON1,1; __endasm; \
      } while(0)


/**
 * Correct sequence for reading the EEPROM is:
 * @ Set address
 * @ Set RD bit
 * @ Read value from EEDATA
 *
 * This expression does exactly that, first setting EEADR and RD
 * before returning the value of EEDATA.
 */
#define EEPROM_READ(ADDR) (EEADR=ADDR,RD=1,EEDATA)


/*
 * prototypes
 */
extern void eeprom_write(int pos,char *str,int len);
extern void eeprom_read(int pos,char *str,int len);


#endif
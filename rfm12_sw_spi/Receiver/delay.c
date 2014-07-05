/**
 * @file delay.c
 * 
 *
 */

#include "delay.h"


/**
 * @fn void delay_ms (unsigned char cnt)
 * @brief Delay in ms
 * @param cnt ms
 */
void delay_ms (unsigned char cnt) {
  unsigned char i;
  do {
    i = 4;
    do { delay_us(250); } while(--i);
  }
  while (--cnt);
}


/**
 * @fn void delay_s (unsigned char cnt)
 * @brief Delay in s
 * @param cnt s
 */
void delay_s (unsigned char cnt) {
  unsigned char i;
  do {
    i = 4;
    do { delay_ms(250); } while(--i);
  } 
  while (--cnt);
}
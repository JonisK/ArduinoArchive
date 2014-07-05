/**
 * @file delay.h
 * 
 *
 */

#ifndef DELAY_H
#define DELAY_H


#define delay_us(x) { \
  unsigned char cnt; cnt = (x)/(3)|1; while(--cnt != 0) \
  continue; }


extern void delay_ms (unsigned char cnt);
extern void delay_s (unsigned char cnt);

#endif

/**
 * @file macros.h
 * 
 *
 */

#ifndef MACROS_H
#define MACROS_H

/*
 * Bit manipulation macros
 */
#define GET_BIT(X) (1<<(X))
#define MASK_BIT(X) ~GET_BIT(X)
//#define SET_BIT(PORT,BIT) PORT|=GET_BIT(BIT)
#define SET_BIT(PORT,BIT) ((PORT)|=(1<<(BIT)))
//#define CLR_BIT(PORT,BIT) PORT&=~GET_BIT(BIT)
#define CLR_BIT(PORT,BIT) ((PORT)&=~(1<<(BIT)))

/*
 * Bit examination macros
 */
//#define IS_SET(PORT,BIT) ((PORT)&GET_BIT(BIT))
#define IS_SET(PORT,BIT) (((PORT)&(1<<(BIT)))?1:0)
#define NOT_SET(PORT,BIT) (!IS_SET(PORT,BIT))

/*
 *
 */
#define NOP __asm NOP __endasm;

#endif

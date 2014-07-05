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
#define SET_BIT(PORT,BIT) PORT|=GET_BIT(BIT)
#define CLR_BIT(PORT,BIT) PORT&=~GET_BIT(BIT)

/*
 * Bit examination macros
 */
#define IS_SET(PORT,BIT) ((PORT)&GET_BIT(BIT))
#define NOT_SET(PORT,BIT) (!IS_SET(PORT,BIT))

/*
 *
 */
#define NOP __asm NOP __endasm;

#endif

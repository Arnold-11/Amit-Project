#ifndef BIT_MATH_H_
#define BIT_MATH_H_
#define SET_BIT(VAR,BIT_NO)	(VAR |= (1<<BIT_NO))
#define CLR_BIT(VAR,BIT_NO)	(VAR &= (~(1<<BIT_NO)))
#define TOG_BIT(VAR,BIT_NO)	(VAR ^= (1<<BIT_NO))
#define GET_BIT(VAR,BIT_NO)	(((VAR)>>BIT_NO)&1)
//#define	ASSIGN_BIT(VAR,BIT_NO,VAL)	VAR=((VAR | (1<<BIT_NO))& ((~(VAL<<BIT_NO))^ (1<<BIT_NO)))

#define SET(VAR,BIT_NO)	(VAR | (1<<BIT_NO))
#define TOG(VAR,BIT_NO)	(VAR ^ (1<<BIT_NO))
#define	ASSIGN(VAR,BIT_NO,VAL)	VAR=(SET(VAR,BIT_NO)& (TOG((~(VAL<<BIT_NO)),BIT_NO)))
#define ASSIGN_BIT(VAR,BIT_NO,VAL) (VAR=(VAR&(~(1<<BIT_NO)))|(VAL<<BIT_NO))
#endif


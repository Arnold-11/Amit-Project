/***************************************************************************/
/***************************************************************************/
/*********************	Author: Andrew Emad	 *******************************/
/*********************	Date:06/10/2021		 *******************************/
/*********************	Layer: MCAL			 *******************************/
/*********************	Version:1.00		 *******************************/
/***************************************************************************/
/***************************************************************************/

#ifndef ADC_REGISTER_H_
#define ADC_REGISTER_H_

#define ADMUX 			*((volatile uint8*)0x27)	/*ADC Multiplexer selection register*/
#define ADMUX_REFS1		7							/*Reference selection bit 1*/
#define ADMUX_REFS0		6                           /*Reference selection bit 0*/
#define ADMUX_ADLAR		5                           /*Left adjust result*/

#define ADCSRA 			*((volatile uint8*)0x26)	/*ADC Control and status register A*/
#define ADCSRA_ADEN		7							/*ADC enable*/
#define ADCSRA_ADSC		6                           /*ADC start conversion*/
#define ADCSRA_ADATE	5	                        /*Auto trigger enable*/
#define ADCSRA_ADIF		4                           /*ADC interrupt flag*/
#define ADCSRA_ADIE		3                           /*ADC Interrupt enable*/

#define ADCH 			*((volatile uint8*)0x25)	/*Data high register*/
#define ADCL 			*((volatile uint8*)0x24)    /*Data low register*/
#define ADC 			*((volatile uint16*)0x24)    /*Data register 16 bit*/

#endif

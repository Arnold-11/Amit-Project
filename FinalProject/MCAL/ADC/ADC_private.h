/***************************************************************************/
/***************************************************************************/
/*********************	Author: Andrew Emad	 *******************************/
/*********************	Date:06/10/2021		 *******************************/
/*********************	Layer: MCAL			 *******************************/
/*********************	Version:1.00		 *******************************/
/***************************************************************************/
/***************************************************************************/

#ifndef ADC_PRIVATE_H_
#define ADC_PRIVATE_H_

//REF
#define EXT_REF			0
#define	AVCC_REF		1
#define HALF_AVCC_REF   3

//PRE-SCALER
#define DIVISION_BY_2		1
#define DIVISION_BY_4		2
#define DIVISION_BY_8		3
#define DIVISION_BY_16		4
#define DIVISION_BY_32		5
#define DIVISION_BY_64		6
#define DIVISION_BY_128		7

#define EIGHT_BIT	1
#define TEN_BIT		2

#define	IDLE		1
#define BUSY		2

#endif

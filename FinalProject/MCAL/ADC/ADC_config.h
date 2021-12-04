/***************************************************************************/
/***************************************************************************/
/*********************	Author: Andrew Emad	 *******************************/
/*********************	Date:06/10/2021		 *******************************/
/*********************	Layer: MCAL			 *******************************/
/*********************	Version:1.00		 *******************************/
/***************************************************************************/
/***************************************************************************/

#ifndef ADC_CONFIG_H_
#define ADC_CONFIG_H_

/*options are
 * 1-EXT_REF
 * 2-AVCC_REF
 * 3-HALF_AVCC_REF
 */
#define ADC_REF	AVCC_REF

/*options are:
 * 			1-DIVISION_BY_2
 * 			2-DIVISION_BY_4
 * 			3-DIVISION_BY_8
 * 			4-DIVISION_BY_16
 * 			5-DIVISION_BY_32
 * 			6-DIVISION_BY_64
 * 			7-DIVISION_BY_128
 */
#define ADC_u8_PRESCALER DIVISION_BY_128

#define ADC_u32_TIMEOUT		50000

/*OPTIONS ARE:
 * 1- EIGHT_BIT
 * 2- TEN_BIT
 */
#define ADC_u8_RESOLUTION	EIGHT_BIT

#endif

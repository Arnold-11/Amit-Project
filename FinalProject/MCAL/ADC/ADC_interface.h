/***************************************************************************/
/***************************************************************************/
/*********************	Author: Andrew Emad	 *******************************/
/*********************	Date:06/10/2021		 *******************************/
/*********************	Layer: MCAL			 *******************************/
/*********************	Version:1.00		 *******************************/
/***************************************************************************/
/***************************************************************************/

#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

#define ADC_u8_SINGLE_ENDED_CH0	0
#define ADC_u8_SINGLE_ENDED_CH1	1
#define ADC_u8_SINGLE_ENDED_CH2	2
#define ADC_u8_SINGLE_ENDED_CH3	3
#define ADC_u8_SINGLE_ENDED_CH4	4
#define ADC_u8_SINGLE_ENDED_CH5	5
#define ADC_u8_SINGLE_ENDED_CH6	6
#define ADC_u8_SINGLE_ENDED_CH7	7

void ADC_voidInit(void);
uint8 ADC_u8_StartConvSynch(uint8 Copy_u8Channel,uint16* Copy_pu16Result);

//we need to enable global interrupt manually in the Application
uint8 ADC_u8_StartConvASynch(uint8 Copy_u8Channel,uint16* Copy_pu16Result,void(*Copy_pvNotificationFunc)(void));

#endif

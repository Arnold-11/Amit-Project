/***************************************************************************/
/***************************************************************************/
/*********************	Author: Andrew Emad	 *******************************/
/*********************	Date:06/10/2021		 *******************************/
/*********************	Layer: MCAL			 *******************************/
/*********************	Version:1.00		 *******************************/
/***************************************************************************/
/***************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "Err_type.h"
#include "ADC_private.h"
#include "ADC_reg.h"
#include "ADC_interface.h"
#include "ADC_config.h"

//global variables to hold ADC digital result
static uint16* ADC_pu16Result=NULL;
//global variable to hold the ADC asynchronous notification function
static void (*ADC_pvNotificationFunc)(void)=NULL;

static uint8 ADC_u8BusyFlag=IDLE;

void ADC_voidInit()
{
	//REF selection
	ADMUX&=0b00111111;
	ADMUX|=(ADC_REF<<6);
	//ADC Resolution selection
#if ADC_u8_RESOLUTION==EIGHT_BIT
	SET_BIT(ADMUX,ADMUX_ADLAR);
#elif ADC_u8_RESOLUTION==TEN_BIT
	CLR_BIT(ADMUX,ADMUX_ADLAR);
#else
#error "wrong ADC_u8_RESOLUTION configuration option"
#endif
	//Set Pre-scaler
	ADCSRA&=0b11111000;
	ADCSRA|=ADC_u8_PRESCALER;
	//Enable ADC
	SET_BIT(ADCSRA,ADCSRA_ADEN);
}

uint8 ADC_u8_StartConvSynch(uint8 Copy_u8Channel,uint16* Copy_pu16Result)
{
	uint8 Local_u8ErrorState=OK;
	uint32 Local_u32Counter=0;

	if(Copy_pu16Result!=NULL)
	{
		//check ADC is IDLE
		if(ADC_u8BusyFlag==IDLE)
		{
			ADC_u8BusyFlag=BUSY;
			//Set channel
			ADMUX&=0b11100000;
			ADMUX|=Copy_u8Channel;
			//start conversion
			SET_BIT(ADCSRA,ADCSRA_ADSC);
			//Polling
			while((GET_BIT(ADCSRA,ADCSRA_ADIF)==0) /*&& (Local_u32Counter != ADC_u32_TIMEOUT)*/)
			{
				Local_u32Counter++;
			}
			//check about the reason why the loop is finished
			if(Local_u32Counter==ADC_u32_TIMEOUT)
			{
				//loop is finished because timeout has passed
				Local_u8ErrorState=TIMEOUT_ERR;
			}
			else
			{
				//clear interrupt flag
				SET_BIT(ADCSRA,ADCSRA_ADIF);
				//show result
#if ADC_u8_RESOLUTION==EIGHT_BIT
				*Copy_pu16Result=ADCH;
#elif ADC_u8_RESOLUTION==TEN_BIT
				*Copy_pu16Result=ADC;
#else
#error "wrong ADC_u8_RESOLUTION configuration option"
#endif
			}
			//ADC is now IDLE
			ADC_u8BusyFlag=IDLE;
		}
		else
		{
			Local_u8ErrorState=BUSY_ERR;
		}
	}
	else
	{
		Local_u8ErrorState=NULL_POINTER;
	}
	return Local_u8ErrorState;
}

uint8 ADC_u8_StartConvASynch(uint8 Copy_u8Channel,uint16* Copy_pu16Result,void(*Copy_pvNotificationFunc)(void))
{
	uint8 Local_u8ErrorState=OK;
	if((Copy_pu16Result!=NULL) && (Copy_pvNotificationFunc!=NULL))
	{
		if(ADC_u8BusyFlag==IDLE)
		{
			ADC_u8BusyFlag=BUSY;
			//initialize the ADC result Pointer globally
			ADC_pu16Result=Copy_pu16Result;
			//initialize the ADC notification function Pointer globally
			ADC_pvNotificationFunc=Copy_pvNotificationFunc;

			//Set channel
			ADMUX&=0b11100000;
			ADMUX|=Copy_u8Channel;
			//start conversion
			SET_BIT(ADCSRA,ADCSRA_ADSC);

			//ADC conversion complete interrupt enable
			SET_BIT(ADCSRA,ADCSRA_ADIE);
		}
		else
		{
			Local_u8ErrorState=BUSY_ERR;
		}
	}
	else
	{
		Local_u8ErrorState=NULL_POINTER;
	}
	return Local_u8ErrorState;
}

//ADC ISR
void __vector_16 (void)	__attribute__((signal));
void __vector_16 (void)
{
	//read the result
#if ADC_u8_RESOLUTION==EIGHT_BIT
	*ADC_pu16Result=ADCH;
#elif ADC_u8_RESOLUTION==TEN_BIT
	*ADC_pu16Result=ADC;
#else
#error "wrong ADC_u8_RESOLUTION configuration option"
#endif

	//Disable the ADC conversion complete interrupt enable
	CLR_BIT(ADCSRA,ADCSRA_ADIE);

	//ADC is now Idle
	ADC_u8BusyFlag=IDLE;

	//invoke the call back notification function
	if(ADC_pvNotificationFunc != NULL)
	{
		ADC_pvNotificationFunc();
	}
	else
	{
		//do nothing
	}
}





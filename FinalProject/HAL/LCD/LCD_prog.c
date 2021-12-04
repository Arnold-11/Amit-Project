/***************************************************************************/
/***************************************************************************/
/*********************	Author: Andrew Emad			  **********************/
/*********************	Date:23/9/2021				  **********************/
/*********************	Layer: Hal					  **********************/
/*********************	Version:1.00				  **********************/
/***************************************************************************/
/***************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "Err_type.h"
#include <util/delay.h>
#include "DIO_interface.h"
#include "LCD_private.h"
#include "LCD_config.h"
#include "LCD_interface.h"

static void SendEnablePulse(void)
{
	DIO_u8SetPinValue(LCD_CTRL_PORT,LCD_E_PIN,DIO_u8_PIN_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(LCD_CTRL_PORT,LCD_E_PIN,DIO_u8_PIN_LOW);
}

static void SetHalfDataPort(uint8 Copy_u8Data)
{
	uint8 Local_u8DataPins[4]={LCD_DATA_PIN4,LCD_DATA_PIN5,LCD_DATA_PIN6,LCD_DATA_PIN7};
	uint8 Local_u8Iterator;
	for(Local_u8Iterator=0;Local_u8Iterator<4;Local_u8Iterator++)
	{
		if(Local_u8Iterator==0)
		{
			DIO_u8SetPinValue(LCD_CTRL_PORT,Local_u8DataPins[Local_u8Iterator],(GET_BIT(Copy_u8Data,Local_u8Iterator)));
		}
		else
		{
			DIO_u8SetPinValue(LCD_DATA_PORT,Local_u8DataPins[Local_u8Iterator],(GET_BIT(Copy_u8Data,Local_u8Iterator)));
		}
	}
}

void LCD_VoidSendCommand(uint8 Copy_u8Command)
{
	DIO_u8SetPinValue(LCD_CTRL_PORT,LCD_RS_PIN,DIO_u8_PIN_LOW);
	DIO_u8SetPinValue(LCD_CTRL_PORT,LCD_RW_PIN,DIO_u8_PIN_LOW);
#if LCD_u8_BIT_MODE == EIGHT_BIT
	DIO_u8SetPortValue(LCD_DATA_PORT,Copy_u8Command);
	SendEnablePulse();
#elif LCD_u8_BIT_MODE == FOUR_BIT
	SetHalfDataPort(Copy_u8Command>>4);
	SendEnablePulse();
	SetHalfDataPort(Copy_u8Command);
	SendEnablePulse();
#endif
}

void LCD_VoidSendData(uint8 Copy_u8Data)
{
	DIO_u8SetPinValue(LCD_CTRL_PORT,LCD_RS_PIN,DIO_u8_PIN_HIGH);
	DIO_u8SetPinValue(LCD_CTRL_PORT,LCD_RW_PIN,DIO_u8_PIN_LOW);
#if LCD_u8_BIT_MODE == EIGHT_BIT
	DIO_u8SetPortValue(LCD_DATA_PORT,Copy_u8Data);
	SendEnablePulse();
#elif LCD_u8_BIT_MODE == FOUR_BIT
	SetHalfDataPort(Copy_u8Data>>4);
	SendEnablePulse();
	SetHalfDataPort(Copy_u8Data);
	SendEnablePulse();
#endif

}

void LCD_VoidInit(void)
{
	_delay_ms(40);
#if LCD_u8_BIT_MODE == EIGHT_BIT
	LCD_VoidSendCommand(0b00111000);
#elif LCD_u8_BIT_MODE == FOUR_BIT
	SetHalfDataPort(0b0010);
	SendEnablePulse();
	SetHalfDataPort(0b0010);
	SendEnablePulse();
	SetHalfDataPort(0b1000);
	SendEnablePulse();
#endif
	LCD_VoidSendCommand(0B00001100);
	LCD_VoidSendCommand(1);

}

uint8 LCD_u8SendString(const char* Copy_pchString)
{
	uint8 Local_u8ErrorState= OK;
	uint8 Local_u8Counter=0;
	if(Copy_pchString != NULL)
	{
		while(Copy_pchString[Local_u8Counter]!='\0')
		{
			LCD_VoidSendData(Copy_pchString[Local_u8Counter]);
			Local_u8Counter++;
		}
	}
	else
	{
		Local_u8ErrorState=NULL_POINTER;
	}
	return Local_u8ErrorState;
}

uint8 LCD_voidGoToXY(uint8 Copy_u8XPos, uint8 Copy_u8YPos)
{
	uint8 Local_u8ErrorState= OK;
	uint8 Local_u8DDRamAdd;
	switch(Copy_u8YPos)
	{
	case 0:Local_u8DDRamAdd= Copy_u8XPos; break;
	case 1:Local_u8DDRamAdd= Copy_u8XPos+0x40;break;
	default:Local_u8ErrorState= NOK;break;
	}
	//Local_u8ErrorState= Copy_u8YPos*0x40 + Copy_u8XPos;
	SET_BIT(Local_u8DDRamAdd,7);
	LCD_VoidSendCommand(Local_u8DDRamAdd);

	return Local_u8ErrorState;
}

void LCD_voidSendSpecialChar(uint8* Copy_pu8CharArr,uint8 Copy_u8BlockNum,uint8 Copy_u8XPos,uint8 Copy_u8YPos)
{
	uint8 Local_u8Iterator;
	uint8 Local_u8CGRamAdd=Copy_u8BlockNum*8;
	SET_BIT(Local_u8CGRamAdd,6);
	//go to CGRam
	LCD_VoidSendCommand(Local_u8CGRamAdd);
	for(Local_u8Iterator=0;Local_u8Iterator<8;Local_u8Iterator++)
	{
		LCD_VoidSendData(Copy_pu8CharArr[Local_u8Iterator]);
	}
	//Go back to DDRam
	LCD_voidGoToXY(Copy_u8XPos,Copy_u8YPos);
	LCD_VoidSendData(Copy_u8BlockNum);
}

void LCD_voidSendNumber(uint32 Copy_u32Number)
{
	uint8 Copy_u8Remaining;
	uint32 Copy_u32RevNum=0;
	uint8 Count=0;
	if(Copy_u32Number==0)
	{
		LCD_VoidSendData('0');
	}
	while(Copy_u32Number!=0)
	{
		Copy_u8Remaining=Copy_u32Number%10;
		Copy_u32RevNum=(Copy_u32RevNum*10)+Copy_u8Remaining;
		Copy_u32Number=Copy_u32Number/10;
		Count++;
	}
	while(Count!=0)
	{
		Copy_u8Remaining=Copy_u32RevNum%10;
		LCD_VoidSendData(Copy_u8Remaining+'0');
		Copy_u32RevNum=Copy_u32RevNum/10;
		Count--;
	}
}

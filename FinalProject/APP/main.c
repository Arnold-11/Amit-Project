#include "STD_TYPES.h"
#include "util/delay.h"

#include "PORT_interface.h"
#include "ADC_interface.h"

#include "LCD_interface.h"

#define VCC					4.2

#define	YOU					0b00000001
#define	I_LOVE_YOU			0b00000010
#define	HELP				0b00000011
#define	I_AM_WATCHING_YOU	0b00000100
#define	THANK_YOU			0b00000101
#define	GREAT_WORK			0b00000110
#define YOUR_OPINION		0b00000111
#define PROMISE				0b00001000
#define EAT					0b00001001
#define DRINK				0b00001010
#define	SLEEP				0b00001011
#define HOT                 0b00001100
#define COLD                0b00001101
#define WHAT_IS_YOUR_NAME   0b00001110
#define HOW_ARE_YOU         0b00001111

//5:20 , 4:25-15 , 3:30-10 , 2:30-10 , 1:30-10
//5:20-40 , 4:20-50 3:20-55 , 2:20-60 , 1:30-60
int main()
{
	PORT_voidInit();
	ADC_voidInit();
	LCD_VoidInit();

	uint8 Iterator;
	uint8 Word;
	uint16 Local_u16FlexInput[5]={0};
	uint8 Local_u8ADCChannel[5]={ADC_u8_SINGLE_ENDED_CH0,ADC_u8_SINGLE_ENDED_CH2,ADC_u8_SINGLE_ENDED_CH3,ADC_u8_SINGLE_ENDED_CH6,ADC_u8_SINGLE_ENDED_CH4};
	uint8 alpha[][8]={{0b00000110,0b00001100,0b00000100,0b00000100,0b00000100,0,0,0},//ALFHAMZA
			{0,0,0,0b00010001,0b00011111,0,0b00000100,0},//BEH
			{0,0,0b00001010,0b00010001,0b00011111,0,0,0},//TEH
			{0,0b00001000,0b00000100,0b00000010,0b00011111,0,0,0},//7AH
			{0,0,0b00000100,0b00000001,0b00011111,0,0,0},//NON
			{0,0,0,0b00000010,0b00000100,0b00001000,0b00010000,0},//REH
			{0b00000101,0,0b00000111,0b00000101,0b00011111,0,0,0},//KKAF
			{0,0b00000100,0b00000100,0b00000100,0b00000100,0,0,0},//ALF
			{0,0,0,0b00000010,0b00011110,0,0b00001100,0},//YEH
			{0,0,0b00000111,0b00000101,0b00011111,0,0,0},//MEM
			{0,0,0b00001110,0b00001000,0b00011111,0,0,0},//3EN
			{0,0,0b00000111,0b00000001,0b00000111,0,0,0},//DAL
			{0,0,0,0b00000110,0b00001110,0b00001000,0b00001000,0},//MEM
			{0,0b00000010,0b00000101,0b00000011,0b00011111,0,0},//HEH
			{0,0b00000001,0b00000001,0b00000001,0b00000101,0b00000101,0b00000010,0},//LAM
			{0,0,0b00001100,0b00000010,0b00011111,0b00000100,0,0},//GEM
			{0b00001101,0b00011001,0b00000001,0b00010001,0b00011111,0,0,0},//KAF
			{0,0,0b00010101,0b00010101,0b00011111,0,0,0},//SEN
			{0,0b00001010,0b00000100,0b00001010,0b00001110,0,0,0},//TEHMARBOTA
			{0b00010101,0,0b00010101,0b00010101,0b00011111,0,0,0},//SHEN
			{0b00000001,0b00000010,0b00000100,0b00000010,0b00011111,0,0,0},//KAFNOSKALAM
			{0b00000100,0b00001010,0b00001000,0b00000100,0b00000100,0,0b00000100,0},//QUESTIONMARK
			{0,0,0b00000111,0b00000101,0b00000111,0b00000001,0b00000010,0},//WAW
			{0b00000100,0,0b00001100,0b00000010,0b00011111,0,0,0},//KHAH
			{0,0,0b00000100,0b00010001,0b00011111,0,0,0},//NONFELAKHER
			{0b00000010,0,0b00000111,0b00000101,0b00011111,0,0,0}};//FEH
	while(1)
	{
		LCD_VoidSendCommand(1);
		uint16 Local_u16FlexInput[5]={0};
		ADC_u8_StartConvSynch(Local_u8ADCChannel[ADC_u8_SINGLE_ENDED_CH4],&Local_u16FlexInput[ADC_u8_SINGLE_ENDED_CH4]);
		Local_u16FlexInput[ADC_u8_SINGLE_ENDED_CH4]=((float)Local_u16FlexInput[ADC_u8_SINGLE_ENDED_CH4]/20);
		LCD_voidGoToXY(0,0);
		LCD_voidSendNumber(Local_u16FlexInput[ADC_u8_SINGLE_ENDED_CH4]);
		_delay_ms(2000);
		if(Local_u16FlexInput[ADC_u8_SINGLE_ENDED_CH4]>0)
		{
			LCD_voidGoToXY(0,0);
			LCD_u8SendString("Make your word");
			_delay_ms(2000);
			Word=0b00000000;
			LCD_VoidSendCommand(1);
			for(Iterator=0;Iterator<4;Iterator++)
			{
				ADC_u8_StartConvSynch(Local_u8ADCChannel[Iterator],&Local_u16FlexInput[Iterator]);
				Local_u16FlexInput[Iterator]=((float)Local_u16FlexInput[Iterator]/20.0);
				LCD_voidSendNumber(Local_u16FlexInput[Iterator]);
				_delay_ms(1000);
				if(Iterator==0 || Iterator==2)
				{
					if(Local_u16FlexInput[Iterator]>1)
					{
						Word |= 1<<Iterator;
					}
				}
				else
				{
					if(Local_u16FlexInput[Iterator]>0)
					{
						Word |= 1<<Iterator;
					}
				}
			}
			LCD_VoidSendCommand(1);
			LCD_voidSendNumber(Word);
			_delay_ms(1000);
			switch(Word)
			{
			case YOU:{LCD_VoidSendCommand(1); LCD_voidGoToXY(0,0);
			LCD_voidSendSpecialChar(alpha[0],0,8,0);
			LCD_voidSendSpecialChar(alpha[4],1,7,0);
			LCD_voidSendSpecialChar(alpha[2],2,6,0);
			_delay_ms(2000);
			break;}
			case I_LOVE_YOU:{LCD_VoidSendCommand(1); LCD_voidGoToXY(0,0);
			LCD_voidSendSpecialChar(alpha[0],0,9,0);
			LCD_voidSendSpecialChar(alpha[3],1,8,0);
			LCD_voidSendSpecialChar(alpha[1],2,7,0);
			LCD_voidSendSpecialChar(alpha[16],3,6,0);
			_delay_ms(2000);
			break;}
			case HELP:{LCD_VoidSendCommand(1); LCD_voidGoToXY(0,0);
			LCD_voidSendSpecialChar(alpha[9],0,10,0);
			LCD_voidSendSpecialChar(alpha[17],1,9,0);
			LCD_voidSendSpecialChar(alpha[7],2,8,0);
			LCD_voidSendSpecialChar(alpha[10],3,7,0);
			LCD_voidSendSpecialChar(alpha[11],4,6,0);
			LCD_voidSendSpecialChar(alpha[18],5,5,0);
			LCD_voidSendSpecialChar(alpha[21],6,4,0);
			_delay_ms(2000);
			break;
			case I_AM_WATCHING_YOU:{LCD_VoidSendCommand(1); LCD_voidGoToXY(0,0);
			LCD_voidSendSpecialChar(alpha[0],0,10,0);
			LCD_voidSendSpecialChar(alpha[5],1,9,0);
			LCD_voidSendSpecialChar(alpha[7],2,8,0);
			LCD_voidSendSpecialChar(alpha[6],3,7,0);
			LCD_voidSendSpecialChar(alpha[1],4,6,0);
			LCD_voidSendSpecialChar(alpha[16],5,5,0);
			_delay_ms(2000);
			break;}
			case THANK_YOU:{LCD_VoidSendCommand(1); LCD_voidGoToXY(0,0);
			LCD_voidSendSpecialChar(alpha[19],0,9,0);
			LCD_voidSendSpecialChar(alpha[20],1,8,0);
			LCD_voidSendSpecialChar(alpha[5],2,7,0);
			LCD_voidSendSpecialChar(alpha[7],3,6,0);
			_delay_ms(2000);
			break;}
			}
			case GREAT_WORK:{LCD_VoidSendCommand(1); LCD_voidGoToXY(0,0);
			LCD_voidSendSpecialChar(alpha[2],0,9,0);
			LCD_voidSendSpecialChar(alpha[9],1,8,0);
			LCD_voidSendSpecialChar(alpha[7],2,7,0);
			LCD_voidSendSpecialChar(alpha[12],3,6,0);
			_delay_ms(2000);
			break;}
			case YOUR_OPINION:{LCD_VoidSendCommand(1); LCD_voidGoToXY(0,0);
			LCD_voidSendSpecialChar(alpha[9],7,11,0);
			LCD_voidSendSpecialChar(alpha[7],0,10,0);

			LCD_voidSendSpecialChar(alpha[5],2,8,0);
			LCD_voidSendSpecialChar(alpha[0],3,7,0);
			LCD_voidSendSpecialChar(alpha[8],4,6,0);
			LCD_voidSendSpecialChar(alpha[16],5,5,0);
			LCD_voidSendSpecialChar(alpha[21],6,4,0);
			_delay_ms(2000);
			break;}
			case PROMISE:{LCD_VoidSendCommand(1); LCD_voidGoToXY(0,0);
			LCD_voidSendSpecialChar(alpha[22],0,8,0);
			LCD_voidSendSpecialChar(alpha[10],1,7,0);
			LCD_voidSendSpecialChar(alpha[11],2,6,0);
			_delay_ms(2000);
			break;}
			case EAT:{LCD_VoidSendCommand(1); LCD_voidGoToXY(0,0);
			LCD_voidSendSpecialChar(alpha[0],0,8,0);
			LCD_voidSendSpecialChar(alpha[20],1,7,0);
			LCD_voidSendSpecialChar(alpha[14],2,6,0);
			LCD_voidSendSpecialChar(alpha[21],3,5,0);
			_delay_ms(2000);
			break;}
			case DRINK:{LCD_VoidSendCommand(1); LCD_voidGoToXY(0,0);
			LCD_voidSendSpecialChar(alpha[19],0,8,0);
			LCD_voidSendSpecialChar(alpha[5],1,7,0);
			LCD_voidSendSpecialChar(alpha[1],2,6,0);
			LCD_voidSendSpecialChar(alpha[21],3,5,0);
			_delay_ms(2000);
			break;}
			case SLEEP:{LCD_VoidSendCommand(1); LCD_voidGoToXY(0,0);
			LCD_voidSendSpecialChar(alpha[4],0,8,0);
			LCD_voidSendSpecialChar(alpha[22],1,7,0);
			LCD_voidSendSpecialChar(alpha[12],2,6,0);
			LCD_voidSendSpecialChar(alpha[21],3,5,0);
			_delay_ms(2000);
			break;}
			case HOT:{LCD_VoidSendCommand(1); LCD_voidGoToXY(0,0);
			LCD_voidSendSpecialChar(alpha[17],0,9,0);
			LCD_voidSendSpecialChar(alpha[7],1,8,0);
			LCD_voidSendSpecialChar(alpha[23],2,7,0);
			LCD_voidSendSpecialChar(alpha[24],3,6,0);
			LCD_voidSendSpecialChar(alpha[21],4,5,0);
			_delay_ms(2000);
			break;}
			case COLD:{LCD_VoidSendCommand(1); LCD_voidGoToXY(0,0);
			LCD_voidSendSpecialChar(alpha[1],0,9,0);
			LCD_voidSendSpecialChar(alpha[7],1,8,0);
			LCD_voidSendSpecialChar(alpha[5],2,7,0);
			LCD_voidSendSpecialChar(alpha[11],3,6,0);
			LCD_voidSendSpecialChar(alpha[21],4,5,0);
			_delay_ms(2000);
			break;}
			case WHAT_IS_YOUR_NAME:{LCD_VoidSendCommand(1); LCD_voidGoToXY(0,0);
			LCD_voidSendSpecialChar(alpha[9],0,11,0);
			LCD_voidSendSpecialChar(alpha[7],1,10,0);
			LCD_voidSendSpecialChar(alpha[0],2,8,0);
			LCD_voidSendSpecialChar(alpha[17],3,7,0);
			LCD_voidSendSpecialChar(alpha[9],4,6,0);
			LCD_voidSendSpecialChar(alpha[16],5,5,0);
			LCD_voidSendSpecialChar(alpha[21],6,4,0);
			_delay_ms(2000);
			break;}
			case HOW_ARE_YOU:{LCD_VoidSendCommand(1); LCD_voidGoToXY(0,0);
			LCD_voidSendSpecialChar(alpha[16],0,12,0);
			LCD_voidSendSpecialChar(alpha[8],1,11,0);
			LCD_voidSendSpecialChar(alpha[25],2,10,0);
			LCD_voidSendSpecialChar(alpha[3],3,8,0);
			LCD_voidSendSpecialChar(alpha[7],4,7,0);
			LCD_voidSendSpecialChar(alpha[14],5,6,0);
			LCD_voidSendSpecialChar(alpha[16],6,5,0);
			LCD_voidSendSpecialChar(alpha[21],7,4,0);
			_delay_ms(2000);
			break;}
			default:{LCD_VoidSendCommand(1); LCD_voidGoToXY(0,0);LCD_u8SendString("No choice");_delay_ms(2000);break;}
			}
		}
	}
}


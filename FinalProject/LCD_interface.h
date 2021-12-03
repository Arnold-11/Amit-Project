/***************************************************************************/
/***************************************************************************/
/*********************	Author: Andrew Emad			  **********************/
/*********************	Date:23/9/2021				  **********************/
/*********************	Layer: Hal					  **********************/
/*********************	Version:1.00				  **********************/
/***************************************************************************/
/***************************************************************************/

#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_

void LCD_VoidSendCommand(uint8 Copy_u8Command);
void LCD_VoidSendData(uint8 Copy_u8Data);
void LCD_VoidInit(void);
uint8 LCD_u8SendString(const char* Copy_pchString);
void LCD_voidSendNumber(uint32 Copy_u32Number);
uint8 LCD_voidGoToXY(uint8 Copy_u8XPos, uint8 Copy_u8YPos);
void LCD_voidSendSpecialChar(uint8* Copy_pu8CharArr,uint8 Copy_u8BlockNum,uint8 Copy_u8XPos,uint8 Copy_u8YPos);

#endif

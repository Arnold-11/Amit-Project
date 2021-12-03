/***************************************************************************/
/***************************************************************************/
/*********************	Author: Andrew Emad			  **********************/
/*********************	Date:23/9/2021				  **********************/
/*********************	Layer: Hal					  **********************/
/*********************	Version:1.00				  **********************/
/***************************************************************************/
/***************************************************************************/

#ifndef LCD_CONFIG_H_
#define LCD_CONFIG_H_

/*Options:
 * 	1-FOUR_BIT
 * 	2-EIGHT_BIT
 */
#define LCD_u8_BIT_MODE	FOUR_BIT

#if LCD_u8_BIT_MODE == FOUR_BIT
#define LCD_DATA_PIN4	DIO_u8_PIN7
#define LCD_DATA_PIN5	DIO_u8_PIN5
#define LCD_DATA_PIN6	DIO_u8_PIN6
#define LCD_DATA_PIN7	DIO_u8_PIN7
#endif

#define LCD_DATA_PORT	DIO_u8_PORTA
#define LCD_CTRL_PORT	DIO_u8_PORTB
#define LCD_RS_PIN		DIO_u8_PIN1
#define LCD_RW_PIN		DIO_u8_PIN2
#define LCD_E_PIN		DIO_u8_PIN3

#endif

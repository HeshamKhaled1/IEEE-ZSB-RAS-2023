#ifndef HAL_LCD_LCD_H_
#define HAL_LCD_LCD_H_

#include "lcd_config.h"
#include "../../MCAL/Dio/Dio.h"
#include <util/delay.h>
#include <stdbool.h>

#define _LCD_CLEAR									0X01
#define _LCD_RETURN_HOME							0x02
#define _LCD_ENTRY_MODE_DEC_SHIFT_OFF				0x04
#define _LCD_ENTRY_MODE_DEC_SHIFT_ON				0x05
#define _LCD_ENTRY_MODE_INC_SHIFT_OFF				0x06
#define _LCD_ENTRY_MODE_INC_SHIFT_ON				0x07
#define _LCD_CURSOR_MOVE_SHIFT_LEFT					0x10
#define _LCD_CURSOR_MOVE_SHIFT_RIGHT				0x14
#define _LCD_DISPLAY_SHIFT_LEFT						0x18
#define _LCD_DISPLAY_SHIFT_RIGHT					0x1C
#define _LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_OFF	0x0C
#define _LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_ON		0x0D
#define _LCD_DISPLAY_ON_UNDERLINE_ON_CURSOR_OFF		0x0E
#define _LCD_DISPLAY_ON_UNDERLINE_ON_CURSOR_ON		0x0F
#define _LCD_DISPLAY_OFF_CURSOR_OFF					0x08
#define _LCD_8BIT_MODE_2_LINE						0x38
#define _LCD_4BIT_MODE_1_LINE						0x33
#define _LCD_4BIT_MODE_2_LINE						0x42
#define _LCD_4BIT_MODE_3_LINE						0x28

#define _LCD_CGRAM_START							0x40
#define _LCD_DDRAM_START							0x80

void LCD_Init(void);
void LCD_Send_Command(u8 command);
void LCD_Send_Char(u8 _char);
void LCD_Send_Char_Pos(u8 _char, u8 row, u8 column);
void LCD_Send_String(u8 *string);
void LCD_Send_String_Pos(u8 *string, u8 row, u8 column);
void LCD_Send_Number(u32 num);
void LCD_Send_Number_Pos(u32 num, u8 row, u8 column);


#endif /* HAL_LCD_LCD_H_ */

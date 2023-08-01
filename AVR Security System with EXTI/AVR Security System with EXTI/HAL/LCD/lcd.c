/*
 * lcd.c
 *
 * Updated: 2023-08-01 11:22:40 PM
 *  Author: Deebo
 */ 

/* ----------------- Includes -----------------*/
#include "lcd.h"

/* ----------------- Software Interfaces Declarations -----------------*/
static void Trigger_Enable();
static void Set_Cursor_Pos(u8 row, u8 column);

/* ----------------- Software Interfaces definition -----------------*/
 void LCD_Init(void)
{
	Dio_PinMode(LCD_DATA4_PIN, OUTPUT);
	Dio_PinMode(LCD_DATA5_PIN, OUTPUT);
	Dio_PinMode(LCD_DATA6_PIN, OUTPUT);
	Dio_PinMode(LCD_DATA7_PIN, OUTPUT);
	Dio_PinMode(LCD_RS_PIN, OUTPUT);
	Dio_PinMode(LCD_EN_PIN, OUTPUT);
	Dio_PinMode(LCD_RW_PIN, OUTPUT);
	Dio_PinWrite(LCD_RW_PIN, LOW);

    _delay_ms(100);

    LCD_Send_Command(_LCD_4BIT_MODE_1_LINE);
    LCD_Send_Command(_LCD_4BIT_MODE_2_LINE);
    LCD_Send_Command(_LCD_4BIT_MODE_3_LINE);
    LCD_Send_Command(_LCD_DISPLAY_ON_UNDERLINE_ON_CURSOR_OFF);
    LCD_Send_Command(_LCD_CLEAR);
    LCD_Send_Command(_LCD_RETURN_HOME);
}

void LCD_Send_Command(u8 command)
{
	Dio_PinWrite(LCD_RS_PIN, LOW);

    (Get_bit(command, 7)) ? Dio_PinWrite(LCD_DATA7_PIN, HIGH) : Dio_PinWrite(LCD_DATA7_PIN, LOW);
    (Get_bit(command, 6)) ? Dio_PinWrite(LCD_DATA6_PIN, HIGH) : Dio_PinWrite(LCD_DATA6_PIN, LOW);
    (Get_bit(command, 5)) ? Dio_PinWrite(LCD_DATA5_PIN, HIGH) : Dio_PinWrite(LCD_DATA5_PIN, LOW);
    (Get_bit(command, 4)) ? Dio_PinWrite(LCD_DATA4_PIN, HIGH) : Dio_PinWrite(LCD_DATA4_PIN, LOW);
    // Trigger Enable
    Trigger_Enable();
    (Get_bit(command, 3)) ? Dio_PinWrite(LCD_DATA7_PIN, HIGH) : Dio_PinWrite(LCD_DATA7_PIN, LOW);
    (Get_bit(command, 2)) ? Dio_PinWrite(LCD_DATA6_PIN, HIGH) : Dio_PinWrite(LCD_DATA6_PIN, LOW);
    (Get_bit(command, 1)) ? Dio_PinWrite(LCD_DATA5_PIN, HIGH) : Dio_PinWrite(LCD_DATA5_PIN, LOW);
    (Get_bit(command, 0)) ? Dio_PinWrite(LCD_DATA4_PIN, HIGH) : Dio_PinWrite(LCD_DATA4_PIN, LOW);
    // Trigger Enable
    Trigger_Enable();
}
void LCD_Send_Char(u8 _char)
{
	Dio_PinWrite(LCD_RS_PIN, HIGH);

    (Get_bit(_char, 7)) ? Dio_PinWrite(LCD_DATA7_PIN, HIGH) : Dio_PinWrite(LCD_DATA7_PIN, LOW);
    (Get_bit(_char, 6)) ? Dio_PinWrite(LCD_DATA6_PIN, HIGH) : Dio_PinWrite(LCD_DATA6_PIN, LOW);
    (Get_bit(_char, 5)) ? Dio_PinWrite(LCD_DATA5_PIN, HIGH) : Dio_PinWrite(LCD_DATA5_PIN, LOW);
    (Get_bit(_char, 4)) ? Dio_PinWrite(LCD_DATA4_PIN, HIGH) : Dio_PinWrite(LCD_DATA4_PIN, LOW);
    // Trigger Enable
    Trigger_Enable();
    (Get_bit(_char, 3)) ? Dio_PinWrite(LCD_DATA7_PIN, HIGH) : Dio_PinWrite(LCD_DATA7_PIN, LOW);
    (Get_bit(_char, 2)) ? Dio_PinWrite(LCD_DATA6_PIN, HIGH) : Dio_PinWrite(LCD_DATA6_PIN, LOW);
    (Get_bit(_char, 1)) ? Dio_PinWrite(LCD_DATA5_PIN, HIGH) : Dio_PinWrite(LCD_DATA5_PIN, LOW);
    (Get_bit(_char, 0)) ? Dio_PinWrite(LCD_DATA4_PIN, HIGH) : Dio_PinWrite(LCD_DATA4_PIN, LOW);
    // Trigger Enable
    Trigger_Enable();
}
void LCD_Send_Char_Pos(u8 c, u8 row, u8 column)
{
    Set_Cursor_Pos(row, column);
    LCD_Send_Char(c);
}
void LCD_Send_String(u8 *string)
{
    while (*string != '\0')
    {
        LCD_Send_Char(*string++);
    }
}
void LCD_Send_String_Pos(u8 *string, u8 row, u8 column)
{
    Set_Cursor_Pos(row, column);
    LCD_Send_String(string);
}

void LCD_Send_Number(u32 num)
{
	u8 arr[10], i = 0, j = 0;
    if (num == 0)
    {
        LCD_Send_Char('0');
    }
    else
    {
        while (num)
        {
            arr[i] = num % 10 + '0';
            num /= 10;
            i++;
        }
        for (j = i; j > 0; j--)
        {
            LCD_Send_Char(arr[j - 1]);
        }
    }
}
void LCD_Send_Number_Pos(u32 num, u8 row, u8 column)
{
    Set_Cursor_Pos(row, column);
    LCD_Send_Number(num);
}

static void Trigger_Enable()
{
	Dio_PinWrite(LCD_EN_PIN, HIGH);
    _delay_us(10);
    Dio_PinWrite(LCD_EN_PIN, LOW);
    _delay_us(2000 );
}
static void Set_Cursor_Pos(u8 row, u8 column)
{
    column--;
    switch (row)
    {
    case 1:
        LCD_Send_Command((0x80 + column));
        break;
    case 2:
        LCD_Send_Command((0xc0 + column));
        break;
    default:;
    }
}

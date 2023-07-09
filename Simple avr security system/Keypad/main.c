/*
 * main.c
 *
 * Created: 7/9/2023 6:10:10 PM
 * Author : Deebo
 */

#include "MCAL/Dio/Dio.h"
#include "HAL/LCD/lcd.h"
#include "HAL/KEYPAD/KeyPad.h"
#include <util/delay.h>

#define PASSWORD_LENGTH 4
#define MAX_ATTEMPTS 3

int main()
{
	u8 password[PASSWORD_LENGTH] = {'1', '2', '3', '4'};
	u8 enteredPassword[PASSWORD_LENGTH] = {0};
	u8 attemptCount = 0;
	
	KP_init(); // Initialize KEYPAD;
	LCD_Init(); // Initialize LCD;
	
	while (1)
	{
		LCD_Send_String("Enter Password:");

		// Read user input
		u8 key = 0;
		u8 keyIndex = 0;
		do
		{
			key = KP_GetPressed();
			_delay_us(1);
			if (key != 255 && key != '=')
			{
				enteredPassword[keyIndex] = key;
				keyIndex++;
				LCD_Send_Char('*');  // Mask entered characters with '*'
			}

		} while (key != '=' && keyIndex < PASSWORD_LENGTH);
		
		// Verify the password
		int flag = 1;
		for(short i = 0; i < PASSWORD_LENGTH; i++){
			if(password[i] != enteredPassword[i]){
				flag = 0;
			}
		}
		
		if (flag)
		{
			LCD_Send_Command(_LCD_CLEAR);
			LCD_Send_String("Correct Password");
			_delay_ms(1000);
			LCD_Send_Command(_LCD_CLEAR);
			break;
		}
		else
		{
			LCD_Send_Command(_LCD_CLEAR);
			LCD_Send_String_Pos((u8 *)"Incorrect", 1, 1);
			LCD_Send_String_Pos((u8 *)"Password", 2, 1);
			_delay_ms(1000);
			LCD_Send_Command(_LCD_CLEAR);

			attemptCount++;
			if (attemptCount >= MAX_ATTEMPTS)
			{
				LCD_Send_String_Pos((u8 *)"You reached the", 1, 1);
				LCD_Send_String_Pos((u8 *)"maximum attempts!", 2, 1);
				_delay_ms(2000);
				LCD_Send_Command(_LCD_CLEAR);
				break;
			}
		}
	}
	return 0;
}
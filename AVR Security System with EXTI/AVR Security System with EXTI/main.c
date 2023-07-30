/*
 * main.c
 *
 * Created: 2023-07-29 4:01:47 PM
 *  Author: Deebo
 */ 

#include <xc.h>
#include <util/delay.h>
#include "MCAL/EXTI/EXTI.h"
#include "MCAL/EXTI/EXTI_Configuration.h"
#include "MCAL/GI/GI.h"
#include "MCAL/DIO/Dio.h"
#include "HAL/LCD/lcd.h"
#include "HAL/KEYPAD/KeyPad.h"
#include "HAL/Stepper Motor/stepper.h"
#include "HAL/DC Motor/DC Motor.h"
#include "Bit_math.h"

# define F_CPU 8000000UL
#define PASSWORD_LENGTH 4
#define MAX_ATTEMPTS 3

int angle = 0;

void login(void);

int main(void)
{
	dio_init();
	/* Enable global Interrupt (Bit 7 or I-Bit) in SREG Register */
	GI_Enable();							// Enable EXTI0
	EXTI_Enable(EXTI0, EXTI_RISING_EDGE);
	
	Set_bit(EXTI_SREG,7);
	EXTI_SetCallBack(&login,EXTI0);
    while(1);
	return 0;
}

void dio_init()
{
	Dio_PinMode(_PD2, INPUT);		// EXTI0 as input from a switch
}

void login()
{
	u8 password[PASSWORD_LENGTH] = {'1', '2', '3', '4'};
	u8 enteredPassword[PASSWORD_LENGTH] = {0};
	u8 attemptCount = 0;
	
	KP_init(); // Initialize KEYPAD;
	LCD_Init(); // Initialize LCD;
	
	while (1)
	{
		// Read user input
		u8 key = 0;
		u8 keyIndex = 0;
		print_enter_pass();
		do
		{
			key = KP_GetPressed();
			_delay_us(1);
			if (key != 255 && key != '=')
			{
				enteredPassword[keyIndex] = key;
				keyIndex++;
				LCD_Send_Char_Pos('*', 2, keyIndex); // Mask entered characters with '*'
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
			print_correct_pass();
			_delay_ms(1000);
			LCD_Send_Command(_LCD_CLEAR);
			choose_motor();
			get_angle();
			break;
		}
		else
		{
			LCD_Send_Command(_LCD_CLEAR);
			print_incorrect_pass();
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

void print_enter_pass()
{
	LCD_Send_Char_Pos('E',1,1);
	LCD_Send_Char_Pos('n',1,2);
	LCD_Send_Char_Pos('t',1,3);
	LCD_Send_Char_Pos('e',1,4);
	LCD_Send_Char_Pos('r',1,5);
	
	LCD_Send_Char_Pos('P',1,7);
	LCD_Send_Char_Pos('a',1,8);
	LCD_Send_Char_Pos('s',1,9);
	LCD_Send_Char_Pos('s',1,10);
	LCD_Send_Char_Pos('w',1,11);
	LCD_Send_Char_Pos('o',1,12);
	LCD_Send_Char_Pos('r',1,13);
	LCD_Send_Char_Pos('d',1,14);
	LCD_Send_Char_Pos(':',1,15);
}

void print_correct_pass(){
	LCD_Send_Char_Pos('C',1,1);
	LCD_Send_Char_Pos('o',1,2);
	LCD_Send_Char_Pos('r',1,3);
	LCD_Send_Char_Pos('r',1,4);
	LCD_Send_Char_Pos('e',1,5);
	LCD_Send_Char_Pos('c',1,6);
	LCD_Send_Char_Pos('t',1,7);
	
	LCD_Send_Char_Pos('P',1,9);
	LCD_Send_Char_Pos('a',1,10);
	LCD_Send_Char_Pos('s',1,11);
	LCD_Send_Char_Pos('s',1,12);
	LCD_Send_Char_Pos('w',1,13);
	LCD_Send_Char_Pos('o',1,14);
	LCD_Send_Char_Pos('r',1,15);
	LCD_Send_Char_Pos('d',1,16);
}

void print_incorrect_pass(){
	LCD_Send_Char_Pos('I',1,1);
	LCD_Send_Char_Pos('n',1,2);
	LCD_Send_Char_Pos('C',1,3);
	LCD_Send_Char_Pos('o',1,4);
	LCD_Send_Char_Pos('r',1,5);
	LCD_Send_Char_Pos('r',1,6);
	LCD_Send_Char_Pos('e',1,7);
	LCD_Send_Char_Pos('c',1,8);
	LCD_Send_Char_Pos('t',1,9);
	
	LCD_Send_Char_Pos('P',2,1);
	LCD_Send_Char_Pos('a',2,2);
	LCD_Send_Char_Pos('s',2,3);
	LCD_Send_Char_Pos('s',2,4);
	LCD_Send_Char_Pos('w',2,5);
	LCD_Send_Char_Pos('o',2,6);
	LCD_Send_Char_Pos('r',2,7);
	LCD_Send_Char_Pos('d',2,8);
}

void print_loading(){
	LCD_Send_Char_Pos('L', 1, 1);
	LCD_Send_Char_Pos('o', 1, 2);
	LCD_Send_Char_Pos('a', 1, 3);
	LCD_Send_Char_Pos('d', 1, 4);
	LCD_Send_Char_Pos('i', 1, 5);
	LCD_Send_Char_Pos('n', 1, 6);
	LCD_Send_Char_Pos('g', 1, 7);
	LCD_Send_Char_Pos('.', 1, 8);
	LCD_Send_Char_Pos('.', 1, 9);
	LCD_Send_Char_Pos('.', 1, 10);
}

void print_done(){
	LCD_Send_Char_Pos('D', 1, 1);
	LCD_Send_Char_Pos('o', 1, 2);
	LCD_Send_Char_Pos('n', 1, 3);
	LCD_Send_Char_Pos('e', 1, 4);
}

choose_motor(){
	/* 1- DC Motor */
	LCD_Send_Char_Pos('1',1,1);
	LCD_Send_Char_Pos('-',1,2);
	LCD_Send_Char_Pos('D',1,3);
	LCD_Send_Char_Pos('C',1,4);
	LCD_Send_Char_Pos('M',1,5);
	LCD_Send_Char_Pos('o',1,6);
	LCD_Send_Char_Pos('t',1,7);
	LCD_Send_Char_Pos('o',1,8);
	LCD_Send_Char_Pos('r',1,9);
	/* 3- EXIT */
	LCD_Send_Char_Pos('3',1,11);
	LCD_Send_Char_Pos('-',1,12);
	LCD_Send_Char_Pos('E',1,13);
	LCD_Send_Char_Pos('X',1,14);
	LCD_Send_Char_Pos('I',1,15);
	LCD_Send_Char_Pos('T',1,16);
	/* 2- Stepper Motor */
	LCD_Send_Char_Pos('2',2,1);
	LCD_Send_Char_Pos('-',2,2);
	LCD_Send_Char_Pos('S',2,3);
	LCD_Send_Char_Pos('t',2,4);
	LCD_Send_Char_Pos('e',2,5);
	LCD_Send_Char_Pos('p',2,6);
	LCD_Send_Char_Pos('p',2,7);
	LCD_Send_Char_Pos('e',2,8);
	LCD_Send_Char_Pos('r',2,9);
	LCD_Send_Char_Pos(' ',2,10);
	LCD_Send_Char_Pos('M',2,11);
	LCD_Send_Char_Pos('o',2,12);
	LCD_Send_Char_Pos('t',2,13);
	LCD_Send_Char_Pos('o',2,14);
	LCD_Send_Char_Pos('r',2,15);
	
	/* Next Step 'Make Decision' */
	
	u8 key = 0;
	do
	{
		key = KP_GetPressed();
		_delay_us(1);
		if (key == '2')   // Stepper Motor
		{
			LCD_Send_Command(_LCD_CLEAR);
			choose_angle();
			break;
		}else if(key == '1')	// DC Motor
		{
			LCD_Send_Command(_LCD_CLEAR);
			dc_motor();
		}else if(key == '3')
		{
			LCD_Send_Command(_LCD_CLEAR);
			print_done();
		}
	} while (key != '=');
}

choose_angle(){
	/* Angle? */
	LCD_Send_Char_Pos('A',1,1);
	LCD_Send_Char_Pos('n',1,2);
	LCD_Send_Char_Pos('g',1,3);
	LCD_Send_Char_Pos('l',1,4);
	LCD_Send_Char_Pos('e',1,5);
	LCD_Send_Char_Pos('?',1,6);
	/* 1-30 */
	LCD_Send_Char_Pos('1',1,8);
	LCD_Send_Char_Pos('-',1,9);
	LCD_Send_Char_Pos('1',1,10);
	LCD_Send_Char_Pos('5',1,11);
	/* 2-45 */
	LCD_Send_Char_Pos('2',1,13);
	LCD_Send_Char_Pos('-',1,14);
	LCD_Send_Char_Pos('3',1,15);
	LCD_Send_Char_Pos('0',1,16);
	/* 3-60 */
	LCD_Send_Char_Pos('3',2,1);
	LCD_Send_Char_Pos('-',2,2);
	LCD_Send_Char_Pos('4',2,3);
	LCD_Send_Char_Pos('5',2,4);
	/* 4-90 */
	LCD_Send_Char_Pos('4',2,6);
	LCD_Send_Char_Pos('-',2,7);
	LCD_Send_Char_Pos('6',2,8);
	LCD_Send_Char_Pos('0',2,9);
	/* 5-135 */
	LCD_Send_Char_Pos('5',2,11);
	LCD_Send_Char_Pos('-',2,12);
	LCD_Send_Char_Pos('9',2,13);
	LCD_Send_Char_Pos('0',2,14);
	
	/* Next Step 'Make Decision' */
		get_angle();
}

choose_direction(){
	/* Direction: CW */
	LCD_Send_Char_Pos('1',1,1);
	LCD_Send_Char_Pos('-',1,2);
	LCD_Send_Char_Pos('D',1,3);
	LCD_Send_Char_Pos('i',1,4);
	LCD_Send_Char_Pos('r',1,5);
	LCD_Send_Char_Pos('e',1,6);
	LCD_Send_Char_Pos('c',1,7);
	LCD_Send_Char_Pos('t',1,8);
	LCD_Send_Char_Pos('i',1,9);
	LCD_Send_Char_Pos('o',1,10);
	LCD_Send_Char_Pos('n',1,11);
	LCD_Send_Char_Pos(':',1,12);
	LCD_Send_Char_Pos('C',1,14);
	LCD_Send_Char_Pos('W',1,15);
	/* Direction: ACW */
	LCD_Send_Char_Pos('2',2,1);
	LCD_Send_Char_Pos('-',2,2);
	LCD_Send_Char_Pos('D',2,3);
	LCD_Send_Char_Pos('i',2,4);
	LCD_Send_Char_Pos('r',2,5);
	LCD_Send_Char_Pos('e',2,6);
	LCD_Send_Char_Pos('c',2,7);
	LCD_Send_Char_Pos('t',2,8);
	LCD_Send_Char_Pos('i',2,9);
	LCD_Send_Char_Pos('o',2,10);
	LCD_Send_Char_Pos('n',2,11);
	LCD_Send_Char_Pos(':',2,12);
	LCD_Send_Char_Pos('A',2,14);
	LCD_Send_Char_Pos('C',2,15);
	LCD_Send_Char_Pos('W',2,16);
}

void get_angle(){
	u8 key = 0;
	/*
		angle = 1 >> 15
		angle = 2 >> 30
		angle = 3 >> 45
		angle = 4 >> 60
		angle = 5 >> 90
	*/
	int i = 0;
	do
	{
		key = KP_GetPressed();
		_delay_us(1);
		if (key == '1')
		{
			angle = 15;
			LCD_Send_Command(_LCD_CLEAR);
			stepper_direction();
			i++;
			break;
		}else if (key == '2')
		{
			angle = 30;
			LCD_Send_Command(_LCD_CLEAR);
			stepper_direction();
			i++;
			break;
		}else if (key == '3')
		{
			angle = 45;
			LCD_Send_Command(_LCD_CLEAR);
			stepper_direction();
			i++;
			break;
		}else if (key == '4')
		{
			angle = 60;
			LCD_Send_Command(_LCD_CLEAR);
			stepper_direction();
			i++;
			break;
		}else if (key == '5')
		{
			angle = 90;
			LCD_Send_Command(_LCD_CLEAR);
			stepper_direction();
			i++;
			break;
		}
	} while (key != '=' && i <= 1);
}

void stepper_direction(){
	u8 key = 0;
	choose_direction();
	do
	{
		key = KP_GetPressed();
		_delay_us(1);
		if (key == '1')
		{
			LCD_Send_Command(_LCD_CLEAR);
			print_loading();
			Stepper_Init();
			full_step(CW, angle);
			LCD_Send_Command(_LCD_CLEAR);
			print_done();
			break;
		}else if(key == '2'){
			LCD_Send_Command(_LCD_CLEAR);
			print_loading();
			Stepper_Init();
			full_step(ACW, angle);
			LCD_Send_Command(_LCD_CLEAR);
			print_done();
			break;
		}

	} while (key != '=');
}

void dc_motor()
{	
			u8 key = 0;
			choose_direction();
			do
			{
				key = KP_GetPressed();
				_delay_us(1);
				if (key == '1')		// Clockwise
				{
					LCD_Send_Command(_LCD_CLEAR);
					print_loading();
					dc_motor_init();
					dc_motor_move_right();
					_delay_ms(5000);
					dc_motor_stop();
					LCD_Send_Command(_LCD_CLEAR);
					print_done();
					break;
					}else if(key == '2'){		// Anti-Clockwise
					LCD_Send_Command(_LCD_CLEAR);
					print_loading();
					dc_motor_init();
					dc_motor_move_left();
					_delay_ms(5000);
					dc_motor_stop();
					LCD_Send_Command(_LCD_CLEAR);
					print_done();
					break;
				}

			} while (key != '=');
}
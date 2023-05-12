#include "MCAL/Dio/Dio.h"
#include "HAL/LCD/lcd.h"
#include <util/delay.h>

short column_counter = 1;
short row_counter = 1;

u8 Character1[8] = { 0x00, 0x0A, 0x15, 0x11, 0x0A, 0x04, 0x00, 0x00 };  /* Custom char set for alphanumeric LCD Module */
u8 Character2[8] = { 0x04, 0x1F, 0x11, 0x11, 0x1F, 0x1F, 0x1F, 0x1F };
u8 Character3[8] = { 0x04, 0x0E, 0x0E, 0x0E, 0x1F, 0x00, 0x04, 0x00 };
u8 Character4[8] = { 0x01, 0x03, 0x07, 0x1F, 0x1F, 0x07, 0x03, 0x01 };
u8 Character5[8] = { 0x01, 0x03, 0x05, 0x09, 0x09, 0x0B, 0x1B, 0x18 };
u8 Character6[8] = { 0x0A, 0x0A, 0x1F, 0x11, 0x11, 0x0E, 0x04, 0x04 };
u8 Character7[8] = { 0x00, 0x00, 0x0A, 0x00, 0x04, 0x11, 0x0E, 0x00 };
u8 Character8[8] = { 0x00, 0x0A, 0x1F, 0x1F, 0x0E, 0x04, 0x00, 0x00 };


void pins_init(void){
	Dio_PinMode(_PC0, INPUT);
	Dio_PinMode(_PC1, INPUT);
	Dio_PinMode(_PC2, INPUT);
	Dio_PinMode(_PC3, INPUT);
	Dio_PinMode(_PC4, INPUT);
	Dio_PinMode(_PC5, INPUT);
	Dio_PinMode(_PC6, INPUT);
	Dio_PinMode(_PC7, INPUT);
}

int main()
{
	LCD_Init(); // Initialize LCD;
	pins_init(); // Initialize switches pins;
	
	/* print Hello */
	LCD_Send_String_Pos((u8 *)"Hello", 1 , 1);
	
	/* print 3 dots after Hello */
	for (u8 counter = 0; counter < 3; counter++)
	{
		LCD_Send_Char_Pos('.', 1, counter + 6);
		_delay_ms(10);
	}
	
	_delay_ms(500);
	LCD_Send_Command(_LCD_CLEAR);
	
	/* print "Let's Start!" */
	LCD_Send_String_Pos((u8 *)"Let's Start!", 1 , 1);
	_delay_ms(1000);
	LCD_Send_Command(_LCD_CLEAR);
	
	while(1){
		if(row_counter == 2 && column_counter == 15){
			LCD_Send_Command(_LCD_CLEAR);
			column_counter = 1;
			row_counter = 1;
		}
	
		if(column_counter == 16){
			row_counter++;
			column_counter = 1;
		}
	
		if(Dio_PinRead(_PC0) == HIGH){
			first_char();
		}
	
		if(Dio_PinRead(_PC1) == HIGH){
			second_char();
		}
	
		if(Dio_PinRead(_PC2) == HIGH){
			third_char();
		}
	
		if(Dio_PinRead(_PC3) == HIGH){
			fourth_char();
		}
		if(Dio_PinRead(_PC4) == HIGH){
			fifth_char();
		}
		if(Dio_PinRead(_PC5) == HIGH){
			sixth_char();
		}
		if(Dio_PinRead(_PC6) == HIGH){
			seventh_char();
		}
		if(Dio_PinRead(_PC7) == HIGH){
			eighth_char();
		}
	}

}

void first_char(void){
	CreateCustomCharacter(Character1,0); /*Create heart pattern at location 0 of CGRAM*/
	LCD_Send_Char_Pos(0, row_counter, column_counter);
	_delay_ms(300);
	column_counter++;
}

void second_char(void){
	CreateCustomCharacter(Character2,1); /*Create battery pattern at location 1 of CGRAM*/
	LCD_Send_Char_Pos(1, row_counter, column_counter);
	_delay_ms(300);
	column_counter++;
}

void third_char(void){
	CreateCustomCharacter(Character3,2); /*Create bill pattern at location 2 of CGRAM*/
	LCD_Send_Char_Pos(2, row_counter, column_counter);
	_delay_ms(300);
	column_counter++;
}

void fourth_char(void){
	CreateCustomCharacter(Character4,3); /*Create speaker pattern at location 3 of CGRAM*/
	LCD_Send_Char_Pos(3, row_counter, column_counter);
	_delay_ms(300);
	column_counter++;
}

void fifth_char(void){
	CreateCustomCharacter(Character5,4); /*Create music pattern at location 4 of CGRAM*/
	LCD_Send_Char_Pos(4, row_counter, column_counter);
	_delay_ms(300);
	column_counter++;
}

void sixth_char(void){
	CreateCustomCharacter(Character6,5); /*Create heart2 pattern at location 5 of CGRAM*/
	LCD_Send_Char_Pos(5, row_counter, column_counter);
	_delay_ms(300);
	column_counter++;
}

void seventh_char(void){
	CreateCustomCharacter(Character7,6); /*Create smile pattern at location 6 of CGRAM*/
	LCD_Send_Char_Pos(6, row_counter, column_counter);
	_delay_ms(300);
	column_counter++;
}

void eighth_char(void){
	CreateCustomCharacter(Character8,7); /*Create heart3 pattern at location 7 of CGRAM*/
	LCD_Send_Char_Pos(7, row_counter, column_counter);
	_delay_ms(300);
	column_counter++;
}
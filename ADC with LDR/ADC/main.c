/*
 * main.c
 *
 * Created: 2023-08-02 1:13:18 PM
 *  Author: Deebo
 */ 

#include "main.h"


//void ADC_callBack(u16 digitalValue);

int main(void)
{
	u16 digitalValue = 0 ; 
	u16 analogValue = 0;
	//u16 tempValue = 0;
	u32 res = 0;
	
	dio_init();
	LCD_Init(); // Initialize LCD;
	
	/* Print Hello for 1s */
	print_hello();
	
	/* Enable global Interrupt */
	ADC_init();

	while(1){
		ADC_getDigitalValue(ADC_CHANNEL0, &digitalValue);
		/* converting digitalValue from 0 > 1023 to 0 > 5000mV */
		analogValue = (u16)((digitalValue * 5000UL) / 1024);
		res = ((10000*1024UL)/digitalValue) - 10000;
		
		// print voltage
		print_voltage();
		LCD_Send_Number_Pos(analogValue,1,10);
		print_mv();
		// print resistor
		print_resistor();
		LCD_Send_Number_Pos(res, 2,6);
		print_ohm();
		_delay_ms(1000);
		LCD_Send_Command(_LCD_CLEAR);
		
		/* LDR Code */
		if(res < 1000)
		{
			Dio_PinWrite(LED_GREEN, HIGH);
			Dio_PinWrite(LED_YELLOW, LOW);
			Dio_PinWrite(LED_RED, LOW);
		} else if(res < 2500)
		{
			Dio_PinWrite(LED_GREEN, LOW);
			Dio_PinWrite(LED_YELLOW, HIGH);
			Dio_PinWrite(LED_RED, LOW);
		}
		else
		{
			Dio_PinWrite(LED_GREEN, LOW);
			Dio_PinWrite(LED_YELLOW, LOW);
			Dio_PinWrite(LED_RED, HIGH);
		}
	}
}

void dio_init()
{
	Dio_PinMode(LED_RED, OUTPUT);
	Dio_PinMode(LED_YELLOW, OUTPUT);
	Dio_PinMode(LED_GREEN, OUTPUT);
	Dio_PinMode(LM35, INPUT);
	
	Dio_PinWrite(LED_RED, LOW);
	Dio_PinWrite(LED_YELLOW, LOW);
	Dio_PinWrite(LED_GREEN, LOW);
}

/* When ADC ends conversion it will call this function (ISR) */
/* This function calls a function named ADC_getRegValue which updates the digital value to the register value */
/* Or pass value to the digital value */
/*void ADC_callBack(u16 ADC_value)
{
	// ADC_getRegValue(&digitalValue);
	digitalValue = ADC_value;
}*/

void print_voltage()
{
	LCD_Send_Char_Pos('V',1,1);
	LCD_Send_Char_Pos('o',1,2);
	LCD_Send_Char_Pos('l',1,3);
	LCD_Send_Char_Pos('t',1,4);
	LCD_Send_Char_Pos('a',1,5);
	LCD_Send_Char_Pos('g',1,6);
	LCD_Send_Char_Pos('e',1,7);
	LCD_Send_Char_Pos(':',1,8);
}

void print_mv()
{
	LCD_Send_Char_Pos('m',1,14);
	LCD_Send_Char_Pos('v',1,15);
}

void print_resistor()
{
	LCD_Send_Char_Pos('R',2,1);
	LCD_Send_Char_Pos('e',2,2);
	LCD_Send_Char_Pos('s',2,3);
	LCD_Send_Char_Pos(':',2,4);
	// LCD_Send_Char_Pos('i',2,4);
	// LCD_Send_Char_Pos('s',2,5);
	// LCD_Send_Char_Pos('t',2,6);
	// LCD_Send_Char_Pos('o',2,7);
	// LCD_Send_Char_Pos('r',2,8);
}

void print_ohm()
{
	LCD_Send_Char_Pos('o',2,11);
	LCD_Send_Char_Pos('h',2,12);
	LCD_Send_Char_Pos('m',2,13);
}

void print_hello()
{
	LCD_Send_Char_Pos('H',1,1);
	LCD_Send_Char_Pos('E',1,2);
	LCD_Send_Char_Pos('L',1,3);
	LCD_Send_Char_Pos('L',1,4);
	LCD_Send_Char_Pos('O',1,5);
	_delay_ms(1000);
	LCD_Send_Command(_LCD_CLEAR);
}
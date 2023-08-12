/*
 * main.c
 *
 * Created: 2023-08-11 6:30:20 PM
 *  Author: Deebo
 */ 
#include "main.h"

#define F_CPU 8000000UL
void app_toggleLED();
int main(void)
{
	dio_init();
	/* Enable Global Interrupt */
	GI_Enable();
	/* Set call back */
	Timer0_setCallBack_CTC(&app_toggleLED);
	/* Start Timer */
	Timer0_init();
    while(1);
	return 0;
}

void dio_init()
{
	Dio_PinMode(_PB0, OUTPUT);
	Dio_PinWrite(_PB0, LOW);
}

void app_toggleLED()
{
	static u8 flag = 0;
	if(flag == 0)
	{
		Dio_PinWrite(_PB0, HIGH);
		flag = 1;
	}
	else
	{
		Dio_PinWrite(_PB0, LOW);
		flag = 0;
	}
}
/*
 * stepper.c
 *
 * Created: 2023-07-22 4:25:08 PM
 *  Author: Deebo
 */ 

#include "stepper.h"
#include "Stepper_Config.h"
#define STEPPER_DELAY 100

void Stepper_Init()
{
	Dio_PinMode(BLUE, OUTPUT);
	Dio_PinMode(PINK, OUTPUT);
	Dio_PinMode(YELLOW, OUTPUT);
	Dio_PinMode(ORANGE, OUTPUT);
}

/* Full step anti-clockwise rotation */
void full_step(u8 dir, f32 degree)
{
	/* Control ULN 2003 */
	f32 steps = (degree * 2048) / 360;			// calculate number of steps of stepper motor
	u16 iterations = steps / 4;					// calculate number of iterations of for loop (divided by four as it is a full step)
	
	if(dir == ACW){
		for(short i = 0; i < iterations; i++){
			/* First Step */
			Dio_PinWrite(BLUE, LOW);
			Dio_PinWrite(PINK, HIGH);
			Dio_PinWrite(YELLOW, HIGH);
			Dio_PinWrite(ORANGE, HIGH);
			_delay_ms(STEPPER_DELAY);
			/* Second Step */
			Dio_PinWrite(BLUE, HIGH);
			Dio_PinWrite(PINK, LOW);
			Dio_PinWrite(YELLOW, HIGH);
			Dio_PinWrite(ORANGE, HIGH);
			_delay_ms(STEPPER_DELAY);
			/* Third Step */
			Dio_PinWrite(BLUE, HIGH);
			Dio_PinWrite(PINK, HIGH);
			Dio_PinWrite(YELLOW, LOW);
			Dio_PinWrite(ORANGE, HIGH);
			_delay_ms(STEPPER_DELAY);
			/* Fourth Step */
			Dio_PinWrite(BLUE, HIGH);
			Dio_PinWrite(PINK, HIGH);
			Dio_PinWrite(YELLOW, HIGH);
			Dio_PinWrite(ORANGE, LOW);
			_delay_ms(STEPPER_DELAY);
		}
	}
	else
	{
		for(short i = 0; i < iterations; i++){
			/* First Step */
			Dio_PinWrite(BLUE, HIGH);
			Dio_PinWrite(PINK, HIGH);
			Dio_PinWrite(YELLOW, HIGH);
			Dio_PinWrite(ORANGE, LOW);
			_delay_ms(STEPPER_DELAY);
			/* Second Step */
			Dio_PinWrite(BLUE, HIGH);
			Dio_PinWrite(PINK, HIGH);
			Dio_PinWrite(YELLOW, LOW);
			Dio_PinWrite(ORANGE, HIGH);
			_delay_ms(STEPPER_DELAY);
			
			/* Third Step */
			Dio_PinWrite(BLUE, HIGH);
			Dio_PinWrite(PINK, LOW);
			Dio_PinWrite(YELLOW, HIGH);
			Dio_PinWrite(ORANGE, HIGH);
			_delay_ms(STEPPER_DELAY);
			/* Fourth Step */
			Dio_PinWrite(BLUE, LOW);
			Dio_PinWrite(PINK, HIGH);
			Dio_PinWrite(YELLOW, HIGH);
			Dio_PinWrite(ORANGE, HIGH);
			_delay_ms(STEPPER_DELAY);
		}
	}
}

/* Half step anti-clockwise rotation */
void half_step(u8 dir, f32 degree)
{
	/* Control ULN 2003 */
	f32 steps = (degree * 2048) / 360;			// calculate number of steps of stepper motor
	u16 iterations = steps / 8;					// calculate number of iterations of for loop (divided by eight as it is a half step)
	if(dir == ACW){
		for(short i = 0; i < iterations; i++){
			/* 1st Step */
			Dio_PinWrite(BLUE, LOW);
			Dio_PinWrite(PINK, HIGH);
			Dio_PinWrite(YELLOW, HIGH);
			Dio_PinWrite(ORANGE, LOW);
			_delay_ms(STEPPER_DELAY);
			/* 2nd Step */
			Dio_PinWrite(BLUE, LOW);
			Dio_PinWrite(PINK, HIGH);
			Dio_PinWrite(YELLOW, HIGH);
			Dio_PinWrite(ORANGE, HIGH);
			_delay_ms(STEPPER_DELAY);
			/* 3rd Step */
			Dio_PinWrite(BLUE, LOW);
			Dio_PinWrite(PINK, LOW);
			Dio_PinWrite(YELLOW, HIGH);
			Dio_PinWrite(ORANGE, HIGH);
			_delay_ms(STEPPER_DELAY);
			/* 4th Step */
			Dio_PinWrite(BLUE, HIGH);
			Dio_PinWrite(PINK, LOW);
			Dio_PinWrite(YELLOW, HIGH);
			Dio_PinWrite(ORANGE, HIGH);
			_delay_ms(STEPPER_DELAY);
			/* 5th Step */
			Dio_PinWrite(BLUE, HIGH);
			Dio_PinWrite(PINK, LOW);
			Dio_PinWrite(YELLOW, LOW);
			Dio_PinWrite(ORANGE, HIGH);
			_delay_ms(STEPPER_DELAY);
			/* 6th Step */
			Dio_PinWrite(BLUE, HIGH);
			Dio_PinWrite(PINK, HIGH);
			Dio_PinWrite(YELLOW, LOW);
			Dio_PinWrite(ORANGE, HIGH);
			_delay_ms(STEPPER_DELAY);
			/* 7th Step */
			Dio_PinWrite(BLUE, HIGH);
			Dio_PinWrite(PINK, HIGH);
			Dio_PinWrite(YELLOW, LOW);
			Dio_PinWrite(ORANGE, LOW);
			_delay_ms(STEPPER_DELAY);
			/* 8th Step */
			Dio_PinWrite(BLUE, HIGH);
			Dio_PinWrite(PINK, HIGH);
			Dio_PinWrite(YELLOW, HIGH);
			Dio_PinWrite(ORANGE, LOW);
			_delay_ms(STEPPER_DELAY);
		}
	}
	else
	{
		for(short i = 0; i < iterations; i++){
			/* 1st Step */
			Dio_PinWrite(BLUE, HIGH);
			Dio_PinWrite(PINK, HIGH);
			Dio_PinWrite(YELLOW, HIGH);
			Dio_PinWrite(ORANGE, LOW);
			_delay_ms(STEPPER_DELAY);
			/* 2nd Step */
			Dio_PinWrite(BLUE, HIGH);
			Dio_PinWrite(PINK, HIGH);
			Dio_PinWrite(YELLOW, LOW);
			Dio_PinWrite(ORANGE, LOW);
			_delay_ms(STEPPER_DELAY);
			/* 3rd Step */
			Dio_PinWrite(BLUE, HIGH);
			Dio_PinWrite(PINK, HIGH);
			Dio_PinWrite(YELLOW, LOW);
			Dio_PinWrite(ORANGE, HIGH);
			_delay_ms(STEPPER_DELAY);
			/* 4th Step */
			Dio_PinWrite(BLUE, HIGH);
			Dio_PinWrite(PINK, LOW);
			Dio_PinWrite(YELLOW, LOW);
			Dio_PinWrite(ORANGE, HIGH);
			_delay_ms(STEPPER_DELAY);
			/* 5th Step */
			Dio_PinWrite(BLUE, HIGH);
			Dio_PinWrite(PINK, LOW);
			Dio_PinWrite(YELLOW, HIGH);
			Dio_PinWrite(ORANGE, HIGH);
			_delay_ms(STEPPER_DELAY);
			/* 6th Step */
			Dio_PinWrite(BLUE, LOW);
			Dio_PinWrite(PINK, LOW);
			Dio_PinWrite(YELLOW, HIGH);
			Dio_PinWrite(ORANGE, HIGH);
			_delay_ms(STEPPER_DELAY);
			/* 7th Step */
			Dio_PinWrite(BLUE, LOW);
			Dio_PinWrite(PINK, HIGH);
			Dio_PinWrite(YELLOW, HIGH);
			Dio_PinWrite(ORANGE, HIGH);
			_delay_ms(STEPPER_DELAY);
			/* 8th Step */
			Dio_PinWrite(BLUE, LOW);
			Dio_PinWrite(PINK, HIGH);
			Dio_PinWrite(YELLOW, HIGH);
			Dio_PinWrite(ORANGE, LOW);
			_delay_ms(STEPPER_DELAY);
		}
	}
}
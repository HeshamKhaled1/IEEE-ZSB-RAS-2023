/*
 * main.h
 *
 * Created: 2023-08-04 4:35:47 PM
 *  Author: Deebo
 */ 


#ifndef MAIN_H_
#define MAIN_H_

/* ----------------- Includes -----------------*/
#include <xc.h>

#include "LIBRARIES/Bit_math.h"
#include "LIBRARIES/std_types.h"

#include "MCAL/DIO/Dio.h"
#include "MCAL/ADC/ADC.h"

#include "HAL/LCD/lcd.h"
#include <util/delay.h>
/* ----------------- Macro Declarations -----------------*/
#define F_CPU							8000000UL

#define LM35							_PA0
#define LED_RED							_PD0
#define LED_YELLOW						_PD1
#define LED_GREEN						_PD2

#define initial_digital_value			0

/* ----------------- Software Interfaces Declarations -----------------*/
void dio_init();

#endif /* MAIN_H_ */
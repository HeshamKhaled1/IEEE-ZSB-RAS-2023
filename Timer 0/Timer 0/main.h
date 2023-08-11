/*
 * main.h
 *
 * Created: 2023-08-11 8:24:09 PM
 *  Author: Deebo
 */ 


#ifndef MAIN_H_
#define MAIN_H_
#include <util/delay.h>
#include <xc.h>

#include "LIBRARIES/std_types.h"
#include "LIBRARIES/Bit_math.h"

#include "MCAL/DIO/Dio.h"
#include "MCAL/GI/GI.h"
#include "MCAL/Timer 0/Timer0.h"

void app_toggleLED();
void dio_init();


#endif /* MAIN_H_ */
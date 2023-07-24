/*
 * stepper.h
 *
 * Created: 2023-07-22 4:24:55 PM
 *  Author: Deebo
 */ 


#ifndef STEPPER_H_
#define STEPPER_H_

#include "../../MCAL/Dio/Dio.h"
#include <util/delay.h>


#define ACW 1
#define CW 0

void Stepper_Init();
void full_step(u8 dir, f32 degree);
void half_step(u8 dir, f32 degree);

#endif /* STEPPER_H_ */
/*
 * DC_Motor.c
 *
 * Created: 2023-07-24 10:45:24 PM
 *  Author: Deebo
 */ 

#include "DC Motor.h"

u8 dc_motor_init()
{
	Dio_PinMode(DC_MOTOR_PIN1, OUTPUT);
	Dio_PinMode(DC_MOTOR_PIN2, OUTPUT);
	Dio_PinWrite(DC_MOTOR_PIN1, LOW);
	Dio_PinWrite(DC_MOTOR_PIN2, LOW);
	return E_OK;
}

u8 dc_motor_move_right()
{
	Dio_PinWrite(DC_MOTOR_PIN1, HIGH);
	Dio_PinWrite(DC_MOTOR_PIN2, LOW);
	return E_OK;
}

u8 dc_motor_move_left()
{
	Dio_PinWrite(DC_MOTOR_PIN1, LOW);
	Dio_PinWrite(DC_MOTOR_PIN2, HIGH);
	return E_OK;
}

u8 dc_motor_stop()
{
	Dio_PinWrite(DC_MOTOR_PIN1, LOW);
	Dio_PinWrite(DC_MOTOR_PIN2, LOW);
	return E_OK;
}
/*
 * DC_Motor.h
 *
 * Created: 2023-07-24 10:45:14 PM
 *  Author: Deebo
 */ 


#ifndef DC MOTOR_H_
#define DC MOTOR_H_

/* ----------------- Includes -----------------*/
#include "DC Motor_configuration.h"
#include "../../MCAL/DIO/Dio.h"
#include "../../LIBRARIES/std_types.h"

/* ----------------- Macro Declarations -----------------*/
#define DC_MOTOR_ON_STATUS  0x01U
#define DC_MOTOR_OFF_STATUS 0x00U

/* ----------------- Software Interfaces Declarations -----------------*/

return_type dc_motor_init();
return_type dc_motor_move_right();
return_type dc_motor_move_left();
return_type dc_motor_stop();

#endif /* DC MOTOR_H_ */
/*
 * Timer_0.h
 *
 * Created: 2023-08-11 6:37:02 PM
 *  Author: Deebo
 */ 


#ifndef TIMER0_H_
#define TIMER0_H_

/* ----------------- Includes -----------------*/
#include <stddef.h>

#include "Timer0_config.h"
#include "../DIO/Dio.h"
#include "../../LIBRARIES//std_types.h"
#include "../../LIBRARIES/Bit_math.h"

/* ----------------- Macro Declarations -----------------*/


/* ----------------- Software Interfaces Declarations -----------------*/
void Timer0_init();
u8	 Timer0_setCallBack_OVF(void(*pf)(void));
u8	 Timer0_setCallBack_CTC(void(*pf)(void));


#endif /* TIMER 0_H_ */
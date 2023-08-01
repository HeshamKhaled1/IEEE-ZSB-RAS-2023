/*
 * EXTI.h
 *
 * Created: 2023-07-29 4:04:28 PM
 *  Author: Deebo
 */ 


#ifndef EXTI_H_
#define EXTI_H_

/* ----------------- Includes -----------------*/
#include "../../LIBRARIES/std_types.h"

/* ----------------- Macro Declarations -----------------*/
#define EXTI0						0
#define EXTI1						1
#define EXTI2						2

#define EXTI_RISING_EDGE			0
#define EXTI_FALLING_EDGE			1
#define EXTI_ANY_LOGICAL_CHANGE		2
#define EXTI_LOW_LEVEL				3

#define EXTI_EXTI0_ISC01			1
#define EXTI_EXTI0_ISC00			0
#define EXTI_EXTI1_ISC11			3
#define EXTI_EXTI1_ISC10			2
#define EXTI_EXTI2_ISC2				6

#define EXTI0_PIN6					6
#define EXTI1_PIN7					7
#define EXTI2_PIN5					5

#define Number_OF_ISR_FUN           3

/* ----------------- Software Interfaces Declarations -----------------*/
u8 EXTI_Enable(u8 EXTI_Index, u8 EXTI_Edge);
u8 EXTI_Disable(u8 EXTI_Index);

#endif /* EXTI_H_ */
/*
 * EXTI_Configuration.h
 *
 * Created: 2023-07-29 4:05:04 PM
 *  Author: Deebo
 */ 

/* ----------------- Includes -----------------*/
#include "../../LIBRARIES/std_types.h"

/* ----------------- Macro Declarations -----------------*/
#define EXTI_MCUCR			*((volatile u8*)0x55)		// MCU Control Register
#define EXTI_MCUCSR			*((volatile u8*)0x54)		// MCU Control and Status Register
#define EXTI_GICR			*((volatile u8*)0x5B)		// enable/disable external interrupts by the GICR register
#define EXTI_GIFR			*((volatile u8*)0x5A)
#define EXTI_SREG           *((volatile u8*)0x5F)		// SREG to set I-BIT (Bit 7 in it) which is the global interrupt
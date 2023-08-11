/*
 * GI.h
 *
 * Created: 2023-07-30 11:48:14 AM
 *  Author: Deebo
 */ 

#ifndef GI_H_
#define GI_H_

/* ----------------- Macro Declarations -----------------*/
#define EXTI_SREG           *((volatile u8*)0x5F)		// SREG to set I-BIT (Bit 7 in it) which is the global interrupt
#define I_BIT				7

/* ----------------- Software Interfaces Declarations -----------------*/
void GI_Enable();
void GI_Disable();

#endif /* GI_H_ */
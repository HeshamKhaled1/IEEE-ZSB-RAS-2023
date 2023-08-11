/*
 * Timer_0_config.h
 *
 * Created: 2023-08-11 6:37:13 PM
 *  Author: Deebo
 */ 


#ifndef TIMER0_CONFIG_H_
#define TIMER0_CONFIG_H_

/* ----------------- Macro Declarations -----------------*/

#define TIMER_MODE				MODE_CTC
#define TIMER_INTERRUPT			INTERRUPT_CTC
#define TIMER_PRESCALER			CLK_8
#define TIMER0_PRELOAD_VALUE    192
#define TIMER0_COMPARE_VALUE	99


/* TCCR0 */
#define CS00					0
#define CS01					1
#define CS02					2
#define WGM01					3
#define COM00					4
#define COM01					5
#define WGM00					6
#define FOC0					7

/* TIMSK */
#define TOIE0					0
#define OCIE0					1
#define TOIE1					2
#define OCIE1B					3
#define OCIE1A					4
#define TICIE1					5
#define TOIE2					6
#define OCIE2					7

/* Modes */
#define MODE_NORMAL				0
#define	MODE_PWM				1
#define MODE_CTC				2
#define MODE_FAST_PWM			3

/* Interrupts */
#define INTERRUPT_OVERFLOW		0
#define	INTERRUPT_CTC			1

/* prescaler */
#define CLK_1					1
#define CLK_8					8
#define CLK_64					64
#define CLK_256					256
#define CLK_1024				1024

/* ----------------- Registers definition -----------------*/
#define TIMERS_TIMSK			*((volatile u8*)0x59)
#define TIMERS_TIFR				*((volatile u8*)0x58)
#define TIMERS_TCCR0			*((volatile u8*)0x54)
#define TIMERS_TCNT0			*((volatile u8*)0x52)
#define TIMERS_OCR0				*((volatile u8*)0x5C)

#endif /* TIMER 0_CONFIG_H_ */
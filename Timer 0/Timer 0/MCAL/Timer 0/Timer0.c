/*
 * Timer_0.c
 *
 * Created: 2023-08-11 6:33:45 PM
 *  Author: Deebo
 */ 

/* ----------------- Includes -----------------*/
#include "Timer0.h"

/* Global pointer to function of Timer0 OVF */
static void(*Timer0_pfOVF)(void) = NULL;
static void(*Timer0_pfCTC)(void) = NULL;
#define F_CPU 16000000UL

/* ----------------- Software Interfaces definition -----------------*/
void Timer0_init()
{
	/* Select Mode */
	#if TIMER_MODE == MODE_NORMAL
		Clr_bit(TIMERS_TCCR0, WGM00);
		Clr_bit(TIMERS_TCCR0, WGM01);
	#elif TIMER_MODE == MODE_PWM
		Set_bit(TIMERS_TCCR0, WGM00);
		Clr_bit(TIMERS_TCCR0, WGM01);
	#elif TIMER_MODE == MODE_CTC
		Clr_bit(TIMERS_TCCR0, WGM00);
		Set_bit(TIMERS_TCCR0, WGM01);
	#elif TIMER_MODE == MODE_FAST_PWM
		Set_bit(TIMERS_TCCR0, WGM00);
		Set_bit(TIMERS_TCCR0, WGM01);
	#endif

	/* Enable Interrupt */
	#if TIMER_INTERRUPT == INTERRUPT_OVERFLOW
		Set_bit(TIMERS_TIMSK, TOIE0);
	#elif TIMER_INTERRUPT == INTERRUPT_CTC
		Set_bit(TIMERS_TIMSK, OCIE0);
	#endif

	/*	F.CPU = 8MHZ
		Prescaler = 8
		Timer freq. = F.CPU / Prescaler = 1MHZ
		Timer tick time = 1 Micro sec.
		Time of overflow = 2^(resolution) * Tick time = 256 * 1 = 256 Micro sec.
		If desired time = 1 sec
		Number of overflows = Desired time / Time of overflow = 1M / 256 = 3906.25 overflows
		Number of ticks for 0.25 overflow = 025 * 256 = 64 ticks
		Preload_value = 256 - 64 = 192
		So >>> 3907 overflows & preload_value = 192 in the 3907th
	*/
	/* Set compare match register */
	TIMERS_OCR0 = TIMER0_COMPARE_VALUE;
	
	/* Set preload value */
	TIMERS_TCNT0 = TIMER0_PRELOAD_VALUE;
	
	/* Set prescaler value */
	#if TIMER_PRESCALER == CLK_1
		Clr_bit(TIMERS_TCCR0, CS02);
		Clr_bit(TIMERS_TCCR0, CS01);
		Set_bit(TIMERS_TIMSK, CS00);
	#elif TIMER_PRESCALER == CLK_8
		Clr_bit(TIMERS_TCCR0, CS02);
		Set_bit(TIMERS_TCCR0, CS01);
		Clr_bit(TIMERS_TIMSK, CS00);
	#elif TIMER_PRESCALER == CLK_64
		Clr_bit(TIMERS_TCCR0, CS02);
		Set_bit(TIMERS_TCCR0, CS01);
		Set_bit(TIMERS_TIMSK, CS00);
	#elif TIMER_PRESCALER == CLK_256
		Set_bit(TIMERS_TCCR0, CS02);
		Clr_bit(TIMERS_TCCR0, CS01);
		Clr_bit(TIMERS_TIMSK, CS00);
	#elif TIMER_PRESCALER == CLK_1024
		Set_bit(TIMERS_TCCR0, CS02);
		Clr_bit(TIMERS_TCCR0, CS01);
		Set_bit(TIMERS_TIMSK, CS00);
	#endif
}

u8 Timer0_setCallBack_CTC(void(*pf)(void))
{
	u8 ret = E_OK;
	
	if(pf != NULL)
	{
		Timer0_pfCTC = pf;
	}
	else
	{
		ret = E_NOT_OK;
	}
	
	return ret;
}

u8 Timer0_setCallBack_OVF(void(*pf)(void))
{
	u8 ret = E_OK;
	
	if(pf != NULL)
	{
		Timer0_pfOVF = pf;
	}
	else
	{
		ret = E_NOT_OK;
	}
	
	return ret;
}

/* Prototype for ISR of Timer0 OVF */
void __vector_11(void)	__attribute__((signal));
void __vector_11(void)
{
	static u16 Counter_OVF = 0;
	Counter_OVF++;
	if(Counter_OVF == 3907)
	{
		/* update preload value */
		TIMERS_TCNT0 = TIMER0_PRELOAD_VALUE;
		/* Clear OVF Counter */
		Counter_OVF = 0;
		/* Call application function */
		if(Timer0_pfOVF != NULL)
		{
			Timer0_pfOVF();
		}
	}
}

/* Prototype for ISR of Timer0 CTC */
void __vector_10(void)	__attribute__((signal));
void __vector_10(void)
{
	static u16 Counter_CTC = 0;
	Counter_CTC++;
	if(Counter_CTC == 1000)
	{
		/* Clear counter */
		Counter_CTC = 0;
		/* Call callback function */
		if(Timer0_pfCTC != NULL)
		{
			Timer0_pfCTC();
		}
	}
}
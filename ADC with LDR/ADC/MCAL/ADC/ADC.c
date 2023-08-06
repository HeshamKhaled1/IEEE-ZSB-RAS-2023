/*
 * ADC.c
 *
 * Created: 2023-08-02 1:16:17 PM
 *  Author: Deebo
 */ 


/* ----------------- Includes -----------------*/
#include <stddef.h>
#include "../../LIBRARIES/std_types.h"
#include "../../LIBRARIES/Bit_math.h"
#include "ADC.h"
#include "ADC_config.h"

static void(*ADC_pfNotification)(u16) = NULL;
/* ADC busy flag */
static u8 ADC_busyFlag = 0;

/* ----------------- Software Interfaces definition -----------------*/
void ADC_init()
{
	/*  1- Select Vref
		2- Right Adjust (whole 10 bits)
		3- Disable AutoTrigger
		4- select CLK (recommended: 50KHZ to 200KHZ) -> divide prescalur (8MHZ) by 8 = 125 KHZ
		5- Enable DC
	*/
	
	/* Step one: Select Vref */
	#if (ADC_VREF == AVCC)
	Clr_bit(ADC_ADMUX,REFS1);
	Set_bit(ADC_ADMUX,REFS0);
	#elif (ADC_VREF == AREF)
	Clr_bit(ADC_ADMUX,REFS1);
	Clr_bit(ADC_ADMUX,REFS0);
	#elif (ADC_VREF == INTERNAL_VOLTAGE_REF )
	Set_bit(ADC_ADMUX,REFS1);
	Set_bit(ADC_ADMUX,REFS0);
	#endif
	
	/* Step two: Adjust */
	#if (ADC_ADJUST == RIGHT_ADJUST)
	Clr_bit(ADC_ADMUX,ADLAR);
	#elif (ADC_ADJUST == LEFT_ADJUST)
	Set_bit(ADC_ADMUX,ADLAR);
	#endif
	
	/* Step three: Disable AutoTrigger */
	#if ADC_CONVERSION_MODE == START_CONVERSION
	Clr_bit(ADC_ADCSRA,ADATE);
	#elif ADC_CONVERSION_MODE == FREE_RUNNING_MODE
	Set_bit(ADC_ADCSRA,ADATE);
	Clr_bit(ADC_SFIOR,ADTS2);
	Clr_bit(ADC_SFIOR,ADTS1);
	Clr_bit(ADC_SFIOR,ADTS0);
	#elif ADC_CONVERSION_MODE == EXTERNAL_INTERRUPT
	Set_bit(ADC_ADCSRA,ADATE);
	Clr_bit(ADC_SFIOR,ADTS2);
	Set_bit(ADC_SFIOR,ADTS1);
	Clr_bit(ADC_SFIOR,ADTS0);
	#endif
	
	/* Step four: select CLK */
	#if DEVISION_FACTOR == DIV_BY_2
	Clr_bit(ADC_ADCSRA, ADPS2);
	Clr_bit(ADC_ADCSRA, ADPS1);
	Set_bit(ADC_ADCSRA, ADPS0);
	#elif DEVISION_FACTOR == DIV_BY_4
	Clr_bit(ADC_ADCSRA, ADPS2);
	Set_bit(ADC_ADCSRA, ADPS1);
	Clr_bit(ADC_ADCSRA, ADPS0);
	#elif DEVISION_FACTOR == DIV_BY_8
	Clr_bit(ADC_ADCSRA, ADPS2);
	Set_bit(ADC_ADCSRA, ADPS1);
	Set_bit(ADC_ADCSRA, ADPS0);
	#elif DEVISION_FACTOR == DIV_BY_16
	Set_bit(ADC_ADCSRA, ADPS2);
	Clr_bit(ADC_ADCSRA, ADPS1);
	Clr_bit(ADC_ADCSRA, ADPS0);
	#elif DEVISION_FACTOR == DIV_BY_32
	Set_bit(ADC_ADCSRA, ADPS2);
	Clr_bit(ADC_ADCSRA, ADPS1);
	Set_bit(ADC_ADCSRA, ADPS0);
	#elif DEVISION_FACTOR == DIV_BY_64
	Set_bit(ADC_ADCSRA, ADPS2);
	Set_bit(ADC_ADCSRA, ADPS1);
	Clr_bit(ADC_ADCSRA, ADPS0);
	#elif DEVISION_FACTOR == DIV_BY_128
	Set_bit(ADC_ADCSRA, ADPS2);
	Set_bit(ADC_ADCSRA, ADPS1);
	Set_bit(ADC_ADCSRA, ADPS0);
	#endif
	
	/* Step five: Enable DC */
	Set_bit(ADC_ADCSRA, ADEN);
}

u8 ADC_getDigitalValue(u8 channelNumber, u16 *digitalValue)		// Synchronous & non-blocking mechanism
{
	return_type ret = E_OK;
	u32 timeOutCounter = 0;
	if((channelNumber < 32) && (digitalValue != NULL) && (ADC_busyFlag == 0))
	{
		/* Set flag to make ADC busy */
		ADC_busyFlag = 1;
		/* Clear MUX (pins 4 > 0) */
		ADC_ADMUX &= CHANNEL_PINS;		// clear first 5 pins (channel pins) to avoid conflicting with old channel in the register.
		/* Select Channel */
		ADC_ADMUX |= channelNumber;
		/* Start Conversion */
		Set_bit(ADC_ADCSRA, ADSC);
		/* Wait until interrupt flag = 1 */
		while((Get_bit(ADC_ADCSRA, ADIF) == 0 ) && (timeOutCounter < TIME_OUT_MAX_VALUE))
		{
			timeOutCounter++;
		} 
		if ((Get_bit(ADC_ADCSRA, ADIF) != 0)) // if flag is equal to 1 then ADC ended it's job.
		{
			/* Clear Interrupt Flag */
			Set_bit(ADC_ADCSRA, ADIF);
			ADC_busyFlag = 0;
			/* Read the digital value */
			*digitalValue = ADC_REG;
		}
		else
		{
			ret = E_NOT_OK;
		}
	}
	else
	{
		ret = E_NOT_OK;
	}
	
	return ret;
}

u8 ADC_getDigitalValueAsynchronous(u8 channelNumber, void(*pfNotification)(u16))
{
	u8 ret = E_OK;
	
	if((channelNumber < 32) && (pfNotification != NULL) && (ADC_busyFlag == 0 ) )
	{
		/* Set flag to make ADC busy */
		ADC_busyFlag = 1;
		/* update global interrupt to a function */
		ADC_pfNotification = pfNotification;
		/* Enable ADC Interrupt */
		Set_bit(ADC_ADCSRA, ADIE);
		/* Clear MUX (pins 4 > 0) */
		ADC_ADMUX &= CHANNEL_PINS;		// clear first 5 pins (channel pins) to avoid conflicting with old channel in the register.
		/* Select Channel */
		ADC_ADMUX |= channelNumber;
		/* Start Conversion */
		Set_bit(ADC_ADCSRA, ADSC);
	}
	else
	{
		ret = E_NOT_OK;
	}
	
	return ret;
}

/* Function to read digital value of ADC */

u8 ADC_getRegValue(u16 *ADC_value)
{
	u8 ret = E_OK;
	
	if(ADC_value != NULL)
	{
		/* read ADC Register */
		ADC_value = ADC_REG;
	}
	else
	{
		ret = E_NOT_OK;
	}
	return ret;
}

/* ADC ISR */
void __vector_16(void)		__attribute__((signal));
void __vector_16(void)
{
	if(ADC_pfNotification != NULL) // Make sure that there is an address in the pointer
	{
		/* Clear busy flag */
		ADC_busyFlag = 0;
		/* Clear PIE of ADC */
		Clr_bit(ADC_ADCSRA, ADIE);
		/* Calling notification function */
		ADC_pfNotification(ADC_REG);
	}
}
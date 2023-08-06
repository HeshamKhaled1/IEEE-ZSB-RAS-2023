/*
 * ADC.h
 *
 * Created: 2023-08-02 1:16:06 PM
 *  Author: Deebo
 */ 


#ifndef ADC_H_
#define ADC_H_

/* ----------------- Macro Declarations -----------------*/
#define ADC_CHANNEL0			0
#define ADC_CHANNEL1			1
#define ADC_CHANNEL2			2
#define ADC_CHANNEL3			3
#define ADC_CHANNEL4			4
#define ADC_CHANNEL5			5
#define ADC_CHANNEL6			6
#define ADC_CHANNEL7			7


/* ----------------- Software Interfaces Declarations -----------------*/
void ADC_init();
u8 ADC_getDigitalValue(u8 channelNumber, u16 *digitalValue);

u8 ADC_getDigitalValueAsynchronous(u8 channelNumber, void(*pfNotification)(u16));

u8 ADC_getRegValue(u16 *ADC_value);

#endif /* ADC_H_ */
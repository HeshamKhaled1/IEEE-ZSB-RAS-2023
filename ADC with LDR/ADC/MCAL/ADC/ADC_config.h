/*
 * ADC_config.h
 *
 * Created: 2023-08-02 1:17:18 PM
 *  Author: Deebo
 */ 


#ifndef ADC_CONFIG_H_
#define ADC_CONFIG_H_

/* ----------------- Includes -----------------*/
#include "../../LIBRARIES/std_types.h"

/* ----------------- Macro Declarations -----------------*/
#define ADC_ADMUX						*((volatile u8 *)0x27)
#define ADC_ADCSRA						*((volatile u8 *)0x26)
#define ADC_ADCH						*((volatile u8 *)0x25)
#define ADC_ADCL						*((volatile u8 *)0x24)

/* If I want to read the whole 10 bits then I will read ADC register but if I want to read only 8 bits then I will shift left and read from high register */
/* We read low first then high as low reg. may be updated after I read high.
   So, we read low (it will be blocked from updating and by the way high reg. is also blocked then read high reg. => accurate reading) */

#define ADC_REG							*((volatile u16 *)0x24) // we take 2 bytes not only one to take Low register and High register (16 = 8 + 8) as we must take low reg first then high.

#define ADC_SFIOR						*((volatile u8 *)0x50)

#define ADC_CONVERSION_COMPLEATE		16

/* ADCSRA */
#define ADEN							7	// ADC Enable
#define ADSC							6	// Start Conversion
#define ADATE							5
#define ADIF							4	// Interrupt Flag
#define ADIE							3	// Interrupt Enable
#define ADPS2							2	// ADC prescaler 2
#define ADPS1							1	// ADC prescaler 1
#define ADPS0							0	// ADC prescaler 0

/* ADMUX */
#define REFS1							7
#define REFS0							6
#define ADLAR							5
#define MUX4							4
#define MUX3							3
#define MUX2							2
#define MUX1							1
#define MUX0							0

#define CHANNEL_PINS	        		0b11100000


/*************************************************/
#define TIME_OUT_MAX_VALUE	           	50000
#define DEVISION_FACTOR               DIV_BY_64
#define ADC_ADJUST				      RIGHT_ADJUST
#define ADC_CONVERSION_MODE		      START_CONVERSION
#define ADC_VREF				      AVCC

#define AREF                              0
#define AVCC                              1
#define INTERNAL_VOLTAGE_REF              2

#define RIGHT_ADJUST                      0
#define LEFT_ADJUST                       1

#define FREE_RUNNING_MODE                 0
#define START_CONVERSION                  1
#define EXTERNAL_INTERRUPT                2

#define DIV_BY_2                          0
#define DIV_BY_4                          1
#define DIV_BY_8                          2
#define DIV_BY_16                         3
#define DIV_BY_32                         4
#define DIV_BY_64                         5
#define DIV_BY_128                        6

#endif /* ADC_CONFIG_H_ */
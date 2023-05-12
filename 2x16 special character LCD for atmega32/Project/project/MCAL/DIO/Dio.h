#ifndef DIO_H_
#define DIO_H_

#include <avr/io.h>
#include <util/delay.h>
#include "../../Bit_math.h"
#include "../../std_types.h"
#include "Reg.h"

#define OUTPUT		1
#define INPUT		2
#define HIGH		1
#define LOW			2
#define ENABLE		1
#define DISABLE		2

#define A			1
#define B			2
#define C			3
#define D			4

#define _PA0		10
#define _PA1		11
#define _PA2		12
#define _PA3		13
#define _PA4		14
#define _PA5		15
#define _PA6		16
#define _PA7		17

#define _PB0		20
#define _PB1		21
#define _PB2		22
#define _PB3		23
#define _PB4		24
#define _PB5		25
#define _PB6		26
#define _PB7		27

#define _PC0		30
#define _PC1		31
#define _PC2		32
#define _PC3		33
#define _PC4		34
#define _PC5		35
#define _PC6		36
#define _PC7		37

#define _PD0		40
#define _PD1		41
#define _PD2		42
#define _PD3		43
#define _PD4		44
#define _PD5		45
#define _PD6		46
#define _PD7		47


void Dio_PinMode(u8 ch, u8 Mode);
void Dio_PortMode(u8 Port , u8 Mode);
void Dio_PinWrite(u8 ch, u8 Mode);
void Dio_PortWrite(u8 Port, u8 value);
void Dio_PinTog(u8 ch);
u8 Dio_PinRead(u8 ch);
void Dio_PinPullUpRes(u8 ch, u8 Mode);

#endif

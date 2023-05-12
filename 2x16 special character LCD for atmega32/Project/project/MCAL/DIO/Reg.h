#ifndef REGISTERS_H_
#define REGISTERS_H_

#include "../../std_types.h"
/* Port A */
#define _PINA	*( (volatile u8 *) 0x39 )
#define _DDRA	*( (volatile u8 *) 0x3A )
#define _PORTA	*( (volatile u8 *) 0x3B )

/* Port B */
#define _PINB	*( (volatile u8 *) 0x36 )
#define _DDRB	*( (volatile u8 *) 0x37 )
#define _PORTB	*( (volatile u8 *) 0x38 )

/* Port C */
#define _PINC	*( (volatile u8 *) 0x33 )
#define _DDRC	*( (volatile u8 *) 0x34 )
#define _PORTC	*( (volatile u8 *) 0x35 )

/* Port D */
#define _PIND	*( (volatile u8 *) 0x30 )
#define _DDRD	*( (volatile u8 *) 0x31 )
#define _PORTD	*( (volatile u8 *) 0x32 )

#endif /* REGISTERS_H_ */

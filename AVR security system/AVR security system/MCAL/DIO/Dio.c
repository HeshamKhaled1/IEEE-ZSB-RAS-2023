#include "Dio.h"


void Dio_PinMode(u8 ch, u8 Mode)
{
	u8	port	= ch / 10;
	u8	pin		= ch % 10;

	switch (Mode){
		case OUTPUT:
			switch(port){
				case 1: Set_bit(DDRA, pin);	break;
				case 2: Set_bit(DDRB, pin);	break;
				case 3: Set_bit(DDRC, pin);	break;
				case 4: Set_bit(DDRD, pin);	break;
				default:					break;
			}
			break;
		case INPUT:
			switch(port){
				case 1: Clr_bit(DDRA, pin);	break;
				case 2: Clr_bit(DDRB, pin);	break;
				case 3: Clr_bit(DDRC, pin);	break;
				case 4: Clr_bit(DDRD, pin);	break;
				default:					break;
			}
			break;
		default: break;
	}
}

void Dio_PortMode(u8 Port , u8 Mode)
{

	switch (Mode){

		case OUTPUT:
			switch(Port){
				case 1: DDRA = 0xFF;	break;
				case 2: DDRB = 0xFF;	break;
				case 3: DDRC = 0xFF;	break;
				case 4: DDRD = 0xFF;	break;
				default:				break;
			}
			break;
		case INPUT:
			switch(Port){
				case 1: DDRA = 0x00;	break;
				case 2: DDRB = 0x00;	break;
				case 3: DDRC = 0x00;	break;
				case 4: DDRD = 0x00;	break;
				default:					break;
			}
			break;
		default: break;
	}
}

void Dio_PinWrite(u8 ch, u8 Mode)
{
	u8	port	= ch / 10;
	u8	pin		= ch % 10;

	switch (Mode){
		case HIGH:
			switch(port){
				case 1: Set_bit(PORTA, pin);	break;
				case 2: Set_bit(PORTB, pin);	break;
				case 3: Set_bit(PORTC, pin);	break;
				case 4: Set_bit(PORTD, pin);	break;
				default:						break;
			}
			break;
		case LOW:
			switch(port){
				case 1: Clr_bit(PORTA, pin);	break;
				case 2: Clr_bit(PORTB, pin);	break;
				case 3: Clr_bit(PORTC, pin);	break;
				case 4: Clr_bit(PORTD, pin);	break;
				default:						break;
			}
			break;

		default: break;
	}
}

void Dio_PortWrite(u8 Port, u8 value)
{
	switch(Port){
		case 1: PORTA = value;	break;
		case 2: PORTB = value;	break;
		case 3: PORTC = value;	break;
		case 4: PORTD = value;	break;
		default:						break;
	}
}

void Dio_PinTog(u8 ch){

	u8	port	= ch / 10;
	u8	pin		= ch % 10;

	switch(port){
		case 1: Tog_bit(PORTA, pin);	break;
		case 2: Tog_bit(PORTB, pin);	break;
		case 3: Tog_bit(PORTC, pin);	break;
		case 4: Tog_bit(PORTD, pin);	break;
		default:						break;
	}
}

u8 Dio_PinRead(u8 ch)
{
	u8	port	= ch / 10;
	u8	pin		= ch % 10;

	u8 PinReading = 0;

	switch(port){
		case 1: PinReading = Get_bit(PINA, pin);	break;
		case 2: PinReading = Get_bit(PINB, pin);	break;
		case 3: PinReading = Get_bit(PINC, pin);	break;
		case 4: PinReading = Get_bit(PIND, pin);	break;
		default:									break;
	}
	return PinReading;
}

void Dio_PinPullUpRes(u8 ch, u8 Mode)
{
	u8	port	= ch / 10;
	u8	pin		= ch % 10;

	switch (Mode){

		case ENABLE:
			switch(port){
				case 1: Set_bit(PORTA, pin);	break;
				case 2: Set_bit(PORTB, pin);	break;
				case 3: Set_bit(PORTC, pin);	break;
				case 4: Set_bit(PORTD, pin);	break;
				default:						break;
			}
			break;

		case DISABLE:
			switch(port){
				case 1: Clr_bit(PORTA, pin);	break;
				case 2: Clr_bit(PORTB, pin);	break;
				case 3: Clr_bit(PORTC, pin);	break;
				case 4: Clr_bit(PORTD, pin);	break;
				default:						break;
			}
			break;

		default: break;
	}
}

#ifndef BIT_MATH_H_
#define BIT_MATH_H_



#define Set_bit(Reg, Bit)	(Reg |= (1 << Bit) )
#define Clr_bit(Reg, Bit)	(Reg &= ~(1 << Bit))
#define Tog_bit(Reg, Bit)	(Reg ^= (1 << Bit) )
#define Get_bit(Reg, Bit)	( 1 & (Reg >> Bit) )

#endif /* BIT_MATH_H_ */
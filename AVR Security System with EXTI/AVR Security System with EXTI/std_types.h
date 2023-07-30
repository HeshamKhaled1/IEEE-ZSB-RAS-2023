/*
 * std_types.h
 *
 * Created: 5/8/2023 4:30:36 PM
 * Author : Deebo
 */ 

#ifndef STD_TYPES_H
#define	STD_TYPES_H

/* Section: Data Type Declarations */
typedef unsigned char			u8;
typedef signed char				s8;

typedef unsigned short int		u16;
typedef signed short int		s16;

typedef unsigned long int		u32;
typedef signed long int			s32;

typedef unsigned long int		u64;
typedef signed long long int	s64;

typedef float					f32;
typedef double					d32;

typedef enum{
	E_OK ,
	E_NOT_OK
}return_type;

/* Section: Macro Declarations */
/*
#define E_OK         (u8)0x01
#define E_NOT_OK     (u8)0x00

#define ZERO_INIT 0
*/

#endif	/* STD_TYPES_H */

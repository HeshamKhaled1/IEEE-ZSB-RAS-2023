/*
 * EXTI.c
 *
 * Created: 2023-07-29 4:04:44 PM
 *  Author: Deebo
 */ 

/* ----------------- Includes -----------------*/
#include <stddef.h>
#include "../../std_types.h"
#include "../../Bit_math.h"
#include "EXTI.h"
#include "EXTI_Configuration.h"

//Global pointer to function
static void (*EXTI_Apf[Number_OF_ISR_FUN])(void)={NULL,NULL,NULL};
	
/* ----------------- Software Interfaces Declarations -----------------*/

u8 EXTI_Enable(u8 EXTI_Index, u8 EXTI_Edge)
{
	u8 ret = E_OK;
	switch (EXTI_Index)
	{
		case EXTI0:
			switch (EXTI_Edge)
			{
				case EXTI_RISING_EDGE:
					Set_bit(EXTI_MCUCR  ,EXTI_EXTI0_ISC01);
					Set_bit(EXTI_MCUCR  ,EXTI_EXTI0_ISC00);
					/* Enable EXTI0 */
					Set_bit(EXTI_GICR ,EXTI0_PIN6);
				break;
				
				case EXTI_FALLING_EDGE:
					Set_bit(EXTI_MCUCR  ,EXTI_EXTI0_ISC01);
					Clr_bit(EXTI_MCUCR  ,EXTI_EXTI0_ISC00);
					/* Enable EXTI0 */
					Set_bit(EXTI_GICR ,EXTI0_PIN6);
				break;
					
				case EXTI_ANY_LOGICAL_CHANGE:
					Clr_bit(EXTI_MCUCR  ,EXTI_EXTI0_ISC01);
					Set_bit(EXTI_MCUCR  ,EXTI_EXTI0_ISC00);
					/* Enable EXTI0 */
					Set_bit(EXTI_GICR ,EXTI0_PIN6);
				break;
				
				case EXTI_LOW_LEVEL:
					Clr_bit(EXTI_MCUCR  ,EXTI_EXTI0_ISC01);
					Clr_bit(EXTI_MCUCR  ,EXTI_EXTI0_ISC00);
					/* Enable EXTI0 */
					Set_bit(EXTI_GICR ,EXTI0_PIN6 );
				break;
				
				default: ret = E_NOT_OK;
			}
		break;
		
		case EXTI1:
			switch(EXTI_Edge)
			{
				case EXTI_RISING_EDGE :
				Set_bit(EXTI_MCUCR  ,EXTI_EXTI1_ISC11);
				Set_bit(EXTI_MCUCR  ,EXTI_EXTI1_ISC10);
				/* Enable EXTI1 */
				Set_bit(EXTI_GICR ,EXTI1_PIN7);
				break;
				case EXTI_FALLING_EDGE :
				Set_bit(EXTI_MCUCR  ,EXTI_EXTI1_ISC11);
				Clr_bit(EXTI_MCUCR  ,EXTI_EXTI1_ISC10);
				/* Enable EXTI1 */
				Set_bit(EXTI_GICR ,EXTI1_PIN7);
				break;
				case EXTI_ANY_LOGICAL_CHANGE :
				Clr_bit(EXTI_MCUCR  ,EXTI_EXTI1_ISC11);
				Set_bit(EXTI_MCUCR  ,EXTI_EXTI1_ISC10);
				/* Enable EXTI1 */
				Set_bit(EXTI_GICR ,EXTI1_PIN7);
				break;
				case EXTI_LOW_LEVEL :
				Clr_bit(EXTI_MCUCR  ,EXTI_EXTI1_ISC11);
				Clr_bit(EXTI_MCUCR  ,EXTI_EXTI1_ISC10);
				/* Enable EXTI1 */
				Set_bit(EXTI_GICR ,EXTI1_PIN7);
				break;
				default: ret = E_NOT_OK;
			}
		break;
		
		case EXTI2 :
			switch(EXTI_Edge)
			{
				case EXTI_RISING_EDGE :
				Set_bit(EXTI_MCUCSR  ,EXTI_EXTI2_ISC2);
				/* Enable EXTI2 */
				Set_bit(EXTI_GICR ,EXTI2_PIN5 );
				break;
				case EXTI_FALLING_EDGE :
				Clr_bit(EXTI_MCUCSR  ,EXTI_EXTI2_ISC2);
				/* Enable EXTI2 */
				Set_bit(EXTI_GICR ,EXTI2_PIN5);
				break;
				default: ret = E_NOT_OK ;
			}
		break;
		default: ret = E_NOT_OK ;
	}
	
	return ret;
}


u8  EXTI_SetCallBack(void(*pf_ISR)(void), u8 EXTI_Index)
{
	u8 ret = E_OK ;
	if((EXTI_Index <= EXTI2) && (pf_ISR != NULL))
	{
		EXTI_Apf[EXTI_Index]=pf_ISR;
	}
	else
	{
		ret = E_NOT_OK ;
	}
	return ret ;
}
/*****************************************************************/

u8 EXTI_Disable(u8 EXTI_Index)
{
	u8 ret = E_OK ;
	if((EXTI_Index <= EXTI2))
	{
		switch(EXTI_Index)
		{
			case EXTI0 :
			Clr_bit(EXTI_GICR ,EXTI0_PIN6);
			break;
			case EXTI1 :
			Clr_bit(EXTI_GICR ,EXTI1_PIN7);
			break;
			case EXTI2 :
			Clr_bit(EXTI_GICR ,EXTI2_PIN5);
			break;
			default : ret = E_NOT_OK ;
		}
	}
	else
	{
		ret = E_NOT_OK ;
	}
	return  ret;
}

/****************************************************************/

/* toggling functions */

// ISR EXTI0
void __vector_1(void)  __attribute__((signal));
void __vector_1(void)
{
	if(EXTI_Apf[EXTI0] != NULL)
	{
		EXTI_Apf[EXTI0]();
	}
}

// ISR EXTI1
void __vector_2(void)  __attribute__((signal));
void __vector_2(void)
{
	if(EXTI_Apf[EXTI1] != NULL)
	{
		EXTI_Apf[EXTI1]();
	}
}

// ISR EXTI2
void __vector_3(void)  __attribute__((signal));
void __vector_3(void)
{
	if(EXTI_Apf[EXTI2] != NULL)
	{
		EXTI_Apf[EXTI2]();
	}
}
/*
 * GI.c
 *
 * Created: 2023-07-30 11:48:50 AM
 *  Author: Deebo
 */ 

/* ----------------- Includes -----------------*/
#include "../../std_types.h"
#include "../../Bit_math.h"
#include "GI.h"

/* ----------------- Software Interfaces definition -----------------*/

void GI_Enable()
{
    Set_bit(EXTI_SREG,7);
}



void GI_Disable()
{
    Clr_bit(EXTI_SREG, 7);
}
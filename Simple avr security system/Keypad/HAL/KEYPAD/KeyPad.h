#ifndef HAL_KEYPAD_KEYPAD_H_
#define HAL_KEYPAD_KEYPAD_H_

#include "../../MCAL/Dio/Dio.h"
#include "KeyPad_Config.h"

void KP_init(void);
u8 KP_GetPressed();

#endif /* HAL_KEYPAD_KEYPAD_H_ */

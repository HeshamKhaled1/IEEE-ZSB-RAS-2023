#include "KeyPad.h"
#include <util/delay.h>

static const u8 KP_Maparr[KEYPAD_ROWS][KEYPAD_COLUMNS] = {
	{'7', '8', '9', '/'},
	{'4', '5', '6', 'x'},
	{'1', '2', '3', '-'},
	{'C', '0', '=', '+'}};

	void KP_init(void){
		Dio_PinMode(KEYPAD_ROW_1, OUTPUT);
		Dio_PinMode(KEYPAD_ROW_2, OUTPUT);
		Dio_PinMode(KEYPAD_ROW_3, OUTPUT);
		Dio_PinMode(KEYPAD_ROW_4, OUTPUT);

		Dio_PinMode(KEYPAD_COLUMNS_1, INPUT);
		Dio_PinMode(KEYPAD_COLUMNS_2, INPUT);
		Dio_PinMode(KEYPAD_COLUMNS_3, INPUT);
		Dio_PinMode(KEYPAD_COLUMNS_4, INPUT);

		Dio_PortWrite(C,0XFF); // 1111 1111
	}
	u8 KP_GetPressed()
	{
		u8 LRowConter		= 0;
		u8 LColumnConter	= 0;
		u8 Btn = 255;
		for (LRowConter = KEYPAD_ROW_1; LRowConter <= KEYPAD_ROW_4; LRowConter++)
		{
			Dio_PinWrite(LRowConter, LOW);
			for (LColumnConter = KEYPAD_COLUMNS_1; LColumnConter <= KEYPAD_COLUMNS_4; LColumnConter++)
			{
				if (Dio_PinRead(LColumnConter) == 0)
				{
					_delay_ms(5);
					if (Dio_PinRead(LColumnConter) == 0){
						while(Dio_PinRead(LColumnConter) == 0);
						Btn = KP_Maparr[LRowConter - KEYPAD_ROW_1 ][LColumnConter - KEYPAD_COLUMNS_1];
					}
				}
			}
			Dio_PinWrite(LRowConter, HIGH);
		}
		return Btn;
	}
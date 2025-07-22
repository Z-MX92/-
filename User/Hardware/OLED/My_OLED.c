#include "My_OLED.h"

void OLED_Process_Line(void)
{
	uint8_t i;
	for(i = 0; i < 120; i += 10)
			{
				OLED_ShowImage(i, 30, 16, 16, Diode);
				OLED_Update();
				OLED_Clear();
				delay_ms(100);
			}
}



void Zhanshuang(void)
{
	OLED_ShowImage(5, 18, 128, 64, ZhanShuang);
	OLED_Update();
}







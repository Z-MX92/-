#include "Buzzer.h"

void Buzzer_Config(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef Buzzer_InitStructure;
	Buzzer_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	Buzzer_InitStructure.GPIO_Pin = GPIO_Pin_4;
	Buzzer_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &Buzzer_InitStructure);
	
	GPIO_SetBits(GPIOA, GPIO_Pin_4);
}

void BEEP_ON(void)
{
	GPIO_ResetBits(GPIOA, GPIO_Pin_4);
//	delay_ms(500);
//	GPIO_SetBits(GPIOA, GPIO_Pin_4);
//	delay_ms(200);
}

void BEEP_OFF(void)
{
//	GPIO_ResetBits(GPIOA, GPIO_Pin_4);
//	delay_ms(500);
	GPIO_SetBits(GPIOA, GPIO_Pin_4);
//	delay_ms(200);
}

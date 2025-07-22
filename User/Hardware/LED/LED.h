#ifndef __LED_H_
#define __LED_H_

#include "stm32f10x.h"                  // Device header

#define LED_red(x) (x)?(GPIO_ResetBits(GPIOA, GPIO_Pin_1)):(GPIO_SetBits(GPIOA, GPIO_Pin_1))
#define LED_blue(x) (x)?(GPIO_ResetBits(GPIOA, GPIO_Pin_5)):(GPIO_SetBits(GPIOA, GPIO_Pin_5))

void LED_Config(void);



#endif

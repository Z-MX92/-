#ifndef __BUZZER_H_
#define __BUZZER_H_

#include "stm32f10x.h"                  // Device header
#include "delay.h"
#include "LED.h"
#include "KEY.h"


void Buzzer_Config(void);
void BEEP_ON(void);
void BEEP_OFF(void);



#endif


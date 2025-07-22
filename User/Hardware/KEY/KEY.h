#ifndef __KEY_H_
#define __KEY_H_



#include "stm32f10x.h"                  // Device header
#include "delay.h"
#include "LED.h"



void Key_Init(void);
uint8_t Key_GetNum(void);

#endif    

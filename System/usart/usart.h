#ifndef _USART_H_
#define _USART_H_


#include "stm32f10x.h"
#include "esp8266.h"

#define USART_DEBUG		USART1		//调试打印所使用的串口组


void Usart1_Init(unsigned int baud);

void Usart2_Init(unsigned int baud);

void USART2_SendData(u8 data);
void USART2_SendStr(char * p);
void USART2_SendArray(u8 Arr[] ,u16 DataLenth);

void Usart_SendString(USART_TypeDef *USARTx, unsigned char *str, unsigned short len);

void UsartPrintf(USART_TypeDef *USARTx, char *fmt,...);

#endif

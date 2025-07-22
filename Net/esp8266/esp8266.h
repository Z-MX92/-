#ifndef _ESP8266_H
#define _ESP8266_H

#include "stm32f10x.h"

#include "stdio.h"
#include "delay.h"
#include "string.h"
#include "stdlib.h"
#include "Buzzer.h"
#include "usart.h"
#include "LED.h"
#include "KEY.h"
#include "Menu.h"

//体温检测模块
#include "MLX90614.h"
//心率血氧
#include "max30102.h" 
#include "maxiic.h"
//血压
#include "xgz6847a.h"
#include "xgz6847a_bp.h"

//陀螺仪
#include "MPU6050.h"
#include "MPU_IIC.h"



#define MQTT_AT "aAT\r\n"			
#define MQTT_RST "AT+RST\r\n"
#define MQTT_CWMODE "AT+CWMODE=1\r\n"
#define MQTT_CWDHCP "AT+CWDHCP=1,1\r\n"
#define MQTT_CWJAP "AT+CWJAP=\"zmx\",\"123456789\"\r\n"

#define MQTT_CIPMODE "AT+CIPMODE=1\r\n"
#define MQTT_CNN "AT+CIPSTART=\"TCP\",\"www.bemfa.com\",8344\r\n"
#define MQTT_CIPSEND "AT+CIPSEND\r\n"
#define MQTT_SEND "cmd=2&uid=d311330c76795c8b2135f995e17ed468&topic=temp&msg=#32\r\n"


int ESP8266_Init(void);
void ESP8266_SendData(void);

#endif

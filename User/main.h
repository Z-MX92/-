#ifndef __MAIN_H_
#define __MAIN_H_


#include "OLED.h"
#include "delay.h"
#include "LED.h"
#include "KEY.h"
#include "My_OLED.h"
#include "Buzzer.h"
#include "sys.h"
#include "usart.h"
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
//c库
#include <math.h>
#include <string.h>
#include <stdio.h>
//wifi
#include "esp8266.h"



void Hardware_Init(void);




#endif


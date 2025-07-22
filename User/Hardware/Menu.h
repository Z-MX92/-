#ifndef __MENU_H_
#define __MENU_H_

#include "stm32f10x.h"                  // Device header
#include "KEY.h"
#include "OLED.h"
#include "Buzzer.h"
#include "MyRTC.h"

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

//wifi
#include "esp8266.h"


extern float Pitch,Roll,Yaw;

int menu1(void);
int menu2_Temp(void);
int menu2_Pressure(void);
int menu2_MAX30102(void);
int menu2_MPU6050(void);
int menu2_Clock(void);
int menu2_Location(void);



//void menu(float Pitch,float Roll);
//void menu0(void);//人体健康检测系统
//void menu1(void);//体温检测
//void menu2(void);//心率检测
//void menu3(void);//血氧检测
//void menu4(void);//血压检测
//void menu5(float Pitch, float Roll);
#endif

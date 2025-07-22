#ifndef __XGZ6847A_H
#define __XGZ6847A_H

#include "stm32f10x.h"
#include "xgz6847a_bp.h"
#include "OLED.h"

// 引脚定义
#define XGZ6847A_SCK_PIN    GPIO_Pin_0   // PB0
#define XGZ6847A_OUT_PIN    GPIO_Pin_1   // PB1
#define XGZ6847A_GPIO_PORT  GPIOB
#define XGZ6847A_RCC_CLK    RCC_APB2Periph_GPIOB

// 函数声明
void XGZ6847A_Init(void);
float XGZ6847A_ReadPressure(void);
void BloodPr_Show(float *systolic, float *diastolic);
#endif /* __XGZ6847A_H */

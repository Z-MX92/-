#ifndef __MPU_IIC_H
#define __MPU_IIC_H

#include "stm32f10x.h"

// 初始化I2C接口
void MPU_I2C_Init(void);
// 读取I2C数据
void MPU_I2C_ReadBytes(uint8_t addr, uint8_t reg, uint8_t *data, uint8_t len);
// 写入I2C数据
void MPU_I2C_WriteBytes(uint8_t addr, uint8_t reg, uint8_t *data, uint8_t len);

#endif




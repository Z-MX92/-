#ifndef __MPU6050_H
#define __MPU6050_H

#include "stm32f10x.h"

// MPU6050 I2C地址
#define MPU6050_ADDR 0xD0

#define M_PI 3.14159265358979323846

// MPU6050寄存器地址
#define MPU6050_PWR_MGMT_1 0x6B
#define MPU6050_ACCEL_XOUT_H 0x3B
#define MPU6050_GYRO_XOUT_H 0x43

#define SLIDING_WINDOW_SIZE 16

// 初始化MPU6050
void MPU6050_Init(void);
// 读取MPU6050寄存器数据
uint8_t MPU6050_Read_Byte(uint8_t reg);
// 写入MPU6050寄存器数据
void MPU6050_Write_Byte(uint8_t reg, uint8_t data);
// 读取MPU6050加速度数据
void MPU6050_Read_Accel(int16_t *ax, int16_t *ay, int16_t *az);
// 读取MPU6050角速度数据
void MPU6050_Read_Gyro(int16_t *gx, int16_t *gy, int16_t *gz);
// 跌倒检测函数
uint8_t MPU6050_Fall_Detection(int16_t ax, int16_t ay, int16_t az, int16_t gx, int16_t gy, int16_t gz);
// 滑动平均滤波函数
int16_t MPU6050_Sliding_Average_Filter(int16_t new_data, int16_t *window, uint8_t *index, int32_t *sum);
// 一阶互补滤波函数
void MPU6050_Complementary_Filter(int16_t ax, int16_t ay, int16_t az, int16_t gx, int16_t gy, int16_t gz, float *pitch, float *roll);
// 计算Pitch、Roll和Yaw
void MPU6050_CalculateAngles(int16_t ax, int16_t ay, int16_t az, int16_t gx, int16_t gy, int16_t gz, float *pitch, float *roll, float *yaw);

#endif




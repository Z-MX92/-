#include "MPU6050.h"
#include "MPU_IIC.h"
#include <math.h>

// 全局变量，用于存储上次的角度值
static float prev_pitch = 0;
static float prev_roll = 0;
static float prev_yaw = 0;

// 初始化MPU6050
void MPU6050_Init(void)
{
    MPU_I2C_Init();  // 初始化I2C接口

    // 唤醒MPU6050
    MPU6050_Write_Byte(MPU6050_PWR_MGMT_1, 0x00);
}

// 读取MPU6050寄存器数据
uint8_t MPU6050_Read_Byte(uint8_t reg)
{
    uint8_t data;
    MPU_I2C_ReadBytes(MPU6050_ADDR, reg, &data, 1);
    return data;
}

// 写入MPU6050寄存器数据
void MPU6050_Write_Byte(uint8_t reg, uint8_t data)
{
    MPU_I2C_WriteBytes(MPU6050_ADDR, reg, &data, 1);
}

// 读取MPU6050加速度数据
void MPU6050_Read_Accel(int16_t *ax, int16_t *ay, int16_t *az)
{
    uint8_t buf[6];
    MPU_I2C_ReadBytes(MPU6050_ADDR, MPU6050_ACCEL_XOUT_H, buf, 6);
    *ax = (buf[0] << 8) | buf[1];
    *ay = (buf[2] << 8) | buf[3];
    *az = (buf[4] << 8) | buf[5];
}

// 读取MPU6050角速度数据
void MPU6050_Read_Gyro(int16_t *gx, int16_t *gy, int16_t *gz)
{
    uint8_t buf[6];
    MPU_I2C_ReadBytes(MPU6050_ADDR, MPU6050_GYRO_XOUT_H, buf, 6);
    *gx = (buf[0] << 8) | buf[1];
    *gy = (buf[2] << 8) | buf[3];
    *gz = (buf[4] << 8) | buf[5];
}

// 滑动平均滤波函数
int16_t MPU6050_Sliding_Average_Filter(int16_t new_data, int16_t *window, uint8_t *index, int32_t *sum)
{
    if (SLIDING_WINDOW_SIZE == 0) {
        return new_data; // 如果窗口大小为0，直接返回新数据
    }

    *sum -= window[*index];
    window[*index] = new_data;
    *sum += new_data;
    (*index) = ((*index) + 1) % SLIDING_WINDOW_SIZE;

    return (int16_t)(*sum / SLIDING_WINDOW_SIZE);
}

// 一阶互补滤波函数
void MPU6050_Complementary_Filter(int16_t ax, int16_t ay, int16_t az, int16_t gx, int16_t gy, int16_t gz, float *pitch, float *roll)
{
    float alpha = 0.98;  // 互补滤波系数
    float dt = 0.01;     // 采样时间

    // 计算加速度计的角度
    float accel_pitch = atan2(ax, az) * 180 / M_PI;
    float accel_roll = atan2(ay, az) * 180 / M_PI;

    // 计算陀螺仪的角度变化
    *pitch = alpha * (*pitch + (gx / 131.0) * dt) + (1 - alpha) * accel_pitch;
    *roll = alpha * (*roll + (gy / 131.0) * dt) + (1 - alpha) * accel_roll;
}

// 计算Pitch、Roll和Yaw
void MPU6050_CalculateAngles(int16_t ax, int16_t ay, int16_t az, int16_t gx, int16_t gy, int16_t gz, float *pitch, float *roll, float *yaw)
{
    float alpha = 0.98;  // 互补滤波系数
    float dt = 0.01;     // 采样时间

    // 计算加速度计的角度
    float accel_pitch = atan2(ax, az) * 180 / M_PI;
    float accel_roll = atan2(ay, az) * 180 / M_PI;

    // 计算陀螺仪的角度变化
    *pitch = alpha * (prev_pitch + (gx / 131.0) * dt) + (1 - alpha) * accel_pitch;
    *roll = alpha * (prev_roll + (gy / 131.0) * dt) + (1 - alpha) * accel_roll;
    *yaw = prev_yaw + (gz / 131.0) * dt;

    // 更新上次的角度值
    prev_pitch = *pitch;
    prev_roll = *roll;
    prev_yaw = *yaw;
}

// 跌倒检测函数
uint8_t MPU6050_Fall_Detection(int16_t ax, int16_t ay, int16_t az, int16_t gx, int16_t gy, int16_t gz)
{
    static int16_t ax_window[SLIDING_WINDOW_SIZE] = {0};
    static int16_t ay_window[SLIDING_WINDOW_SIZE] = {0};
    static int16_t az_window[SLIDING_WINDOW_SIZE] = {0};
    static uint8_t ax_index = 0;
    static uint8_t ay_index = 0;
    static uint8_t az_index = 0;
	static int32_t ax_sum = 0, ay_sum = 0, az_sum = 0;
    // 进行滑动平均滤波
    ax = MPU6050_Sliding_Average_Filter(ax, ax_window, &ax_index, &ax_sum);
    ay = MPU6050_Sliding_Average_Filter(ay, ay_window, &ay_index, &ay_sum);
    az = MPU6050_Sliding_Average_Filter(az, az_window, &az_index, &az_sum);

    // 一阶互补滤波
    float pitch, roll;
    MPU6050_Complementary_Filter(ax, ay, az, gx, gy, gz, &pitch, &roll);

    // 计算合加速度
    float accel = (float)(ax * ax + ay * ay + az * az) / (16384.0 * 16384.0);
    accel = sqrt(accel);

    return 0;
}








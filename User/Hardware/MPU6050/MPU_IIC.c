#include "MPU_IIC.h"

// 初始化I2C接口
void MPU_I2C_Init(void)
{
    I2C_InitTypeDef I2C_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

    // 使能I2C1和对应GPIO端口（这里假设使用GPIOB）的时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    // 配置I2C1的SCL（PB6）和SDA（PB7）引脚
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
    // 配置为复用开漏输出模式，适用于I2C通信
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD; 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    // 配置I2C1的工作模式和参数
    I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
    // 配置I2C的占空比，这里选择2:1
    I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2; 
    // 主机自身地址，这里设置为0x00
    I2C_InitStructure.I2C_OwnAddress1 = 0x00; 
    // 使能应答信号
    I2C_InitStructure.I2C_Ack = I2C_Ack_Enable; 
    // 使用7位地址模式
    I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit; 
    // 设置I2C的时钟速度为400kHz
    I2C_InitStructure.I2C_ClockSpeed = 400000; 
    I2C_Init(I2C1, &I2C_InitStructure);

    // 使能I2C1外设
    I2C_Cmd(I2C1, ENABLE);
}

// 等待I2C总线空闲
static void MPU_I2C_WaitForIdle(void)
{
    // 循环等待直到I2C总线不忙
    while (I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY)); 
}

// 发起I2C起始信号
static void MPU_I2C_Start(void)
{
    // 生成起始信号
    I2C_GenerateSTART(I2C1, ENABLE); 
    // 等待起始信号发送成功
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT)); 
}

// 发送I2C设备地址
static void MPU_I2C_SendAddress(uint8_t addr, uint8_t direction)
{
    // 发送7位设备地址和读写方向
    I2C_Send7bitAddress(I2C1, addr, direction); 
    if (direction == I2C_Direction_Transmitter)
    {
        // 等待发送地址后进入发送模式
        while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)); 
    }
    else
    {
        // 等待发送地址后进入接收模式
        while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED)); 
    }
}

// 发送I2C数据
static void MPU_I2C_SendData(uint8_t data)
{
    // 发送数据
    I2C_SendData(I2C1, data); 
    // 等待数据发送完成
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED)); 
}

// 接收I2C数据
static uint8_t MPU_I2C_ReceiveData(void)
{
    // 等待数据接收完成
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED)); 
    // 返回接收到的数据
    return I2C_ReceiveData(I2C1); 
}

// 生成I2C停止信号
static void MPU_I2C_Stop(void)
{
    // 生成停止信号
    I2C_GenerateSTOP(I2C1, ENABLE); 
}

// 读取I2C数据
void MPU_I2C_ReadBytes(uint8_t addr, uint8_t reg, uint8_t *data, uint8_t len)
{
    // 等待I2C总线空闲
    MPU_I2C_WaitForIdle();
    // 发起起始信号
    MPU_I2C_Start();
    // 发送设备地址，设置为写方向
    MPU_I2C_SendAddress(addr, I2C_Direction_Transmitter);
    // 发送要读取的寄存器地址
    MPU_I2C_SendData(reg);

    // 再次发起起始信号以切换到读模式
    MPU_I2C_Start();
    // 发送设备地址，设置为读方向
    MPU_I2C_SendAddress(addr, I2C_Direction_Receiver);

    while (len > 0)
    {
        if (len == 1)
        {
            // 当只剩下最后一个字节时，禁止应答信号并发送停止信号
            I2C_AcknowledgeConfig(I2C1, DISABLE);
            MPU_I2C_Stop();
        }
        // 接收数据
        *data++ = MPU_I2C_ReceiveData();
        len--;
    }
    // 恢复应答信号使能
    I2C_AcknowledgeConfig(I2C1, ENABLE);
}

// 写入I2C数据
void MPU_I2C_WriteBytes(uint8_t addr, uint8_t reg, uint8_t *data, uint8_t len)
{
    // 等待I2C总线空闲
    MPU_I2C_WaitForIdle();
    // 发起起始信号
    MPU_I2C_Start();
    // 发送设备地址，设置为写方向
    MPU_I2C_SendAddress(addr, I2C_Direction_Transmitter);
    // 发送要写入的寄存器地址
    //MPU_I2C_SendData(reg);

    while (len > 0)
    {
        // 发送数据
        MPU_I2C_SendData(*data++);
        len--;
    }
    // 发送停止信号
    MPU_I2C_Stop();
}





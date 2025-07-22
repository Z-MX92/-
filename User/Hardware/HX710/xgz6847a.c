#include "xgz6847a.h"
#include "delay.h"

/**
  * @brief  初始化XGZ6847A压力传感器
  * @param  无
  * @retval 无
  */
void XGZ6847A_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    // 使能GPIOB时钟
    RCC_APB2PeriphClockCmd(XGZ6847A_RCC_CLK, ENABLE);
    
    // 配置SCK为推挽输出
    GPIO_InitStructure.GPIO_Pin = XGZ6847A_SCK_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(XGZ6847A_GPIO_PORT, &GPIO_InitStructure);
    
    // 配置OUT为浮空输入
    GPIO_InitStructure.GPIO_Pin = XGZ6847A_OUT_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(XGZ6847A_GPIO_PORT, &GPIO_InitStructure);
    
    // 初始时钟线置低
    GPIO_ResetBits(XGZ6847A_GPIO_PORT, XGZ6847A_SCK_PIN);
}

/**
  * @brief  读取压力值(kPa)
  * @param  无
  * @retval 压力值(kPa)
  */
float XGZ6847A_ReadPressure(void)
{
    uint32_t data = 0;
    uint8_t i;
    
    // 确保SCK初始为低
    GPIO_ResetBits(XGZ6847A_GPIO_PORT, XGZ6847A_SCK_PIN);
    delay_us(10);
    
    // 读取24位数据
    for(i = 0; i < 24; i++)
    {
        GPIO_SetBits(XGZ6847A_GPIO_PORT, XGZ6847A_SCK_PIN);
        delay_us(10);
        
        data <<= 1;
        if(GPIO_ReadInputDataBit(XGZ6847A_GPIO_PORT, XGZ6847A_OUT_PIN))
        {
            data |= 0x01;
        }
        
        GPIO_ResetBits(XGZ6847A_GPIO_PORT, XGZ6847A_SCK_PIN);
        delay_us(10);
    }
    
    // 转换为压力值 (假设传感器量程为0-40kPa, 输出0x000000-0xFFFFFF)
    // 注意: 需要根据实际传感器规格调整转换公式
    float pressure = (data / 16777215.0f) * 40.0f; // 16777215 = 2^24 - 1
    
    return pressure;
}

void BloodPr_Show(float *systolic, float *diastolic)
{
	// 读取原始压力值
    float pressure = XGZ6847A_ReadPressure();
    float pulse;
    // 模拟血压测量
    //float systolic, diastolic, pulse;
	
    XGZ6847A_SimulateBP(systolic, diastolic, &pulse);
	
	
    delay_ms(200);  // 每200ms测量一次
}


#include "KEY.h"


void Key_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//打开GPIOA时钟
	
	GPIO_InitTypeDef GPIO_InitStructure;				//定义结构体变量
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;		//上拉输入
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_11 | GPIO_Pin_12;//用B1口和B11口
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//输出速度,但输入用不上,写50没影响
	GPIO_Init(GPIOA,&GPIO_InitStructure);				//GPIOB初始化
	
}

/**
  * @brief 获取按键值
  * @param  无
  * @retval KeyNum,要读取的按键值
  */
uint8_t Key_GetNum(void)
{
	uint8_t KeyNum = 0;							//默认为0,没有按键按下返回0
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6) == 0)//读取A6口的输入,如果按下(0)
	{
		delay_ms(20);							//按键消抖
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_6) == 0);//直到松手往下走
		delay_ms(20);							//按键消抖
		KeyNum = 1;								//返回键码1
	}
	
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7) == 0)//读取A7口的输入,如果按下(0)
	{
		delay_ms(20);							//按键消抖
		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7) == 0);//直到松手往下走
		delay_ms(20);							//按键消抖
		KeyNum = 2;								//返回键码2
	}

	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_11) == 0)//读取A11口的输入,如果按下(0)
	{
		delay_ms(20);							//按键消抖
		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_11) == 0);//直到松手往下走
		delay_ms(20);							//按键消抖
		KeyNum = 3;								//返回键码3
	}

	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_12) == 0)//读取A12口的输入,如果按下(0)
	{
		delay_ms(20);							//按键消抖
		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_12) == 0);//直到松手往下走
		delay_ms(20);							//按键消抖
		KeyNum = 4;								//返回键码4
	}
	return KeyNum;
}






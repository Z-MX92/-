#include "stm32f10x.h" 
#include "main.h"



int main(void)
{
	int menu2;
    Hardware_Init();
	ESP8266_Init(); // 初始化ESP8266
	while (Key_GetNum() != 4)
	{
		OLED_Printf(1, 10,OLED_8X16, "人体健康检测系统");
		OLED_Update();
	}
    while (1)
    {
		menu2 = menu1();
		if(menu2 == 1){menu2_Temp();}
		if(menu2 == 2){menu2_Pressure();}
		if(menu2 == 3){menu2_MAX30102();}
		if(menu2 == 4){menu2_MPU6050();}
		if(menu2 == 5){menu2_Location();}			
		if(menu2 == 6)
		{
			unsigned short timeCount = 0;//发送间隔变量
			OLED_Printf(1, 10,OLED_8X16, "Send Data ...");
			OLED_Update();
			while (1)
			{
				if(++timeCount >= 50)//上传
				{
					if (Key_GetNum() == 4) break;
					ESP8266_SendData();
					timeCount = 0;
				}
			}
		}
		if(menu2 == 7){menu2_Clock();}
		if(menu2 == 8){}
		
		
    }
}    
void Hardware_Init(void)
{
	OLED_Init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//中断控制器分组设置
	Key_Init();
	Buzzer_Config();
	LED_Config();
    delay_init();             // 延时函数初始化	
    SMBus_Init();
	max30102_init();
	MAX30102_data_set();
	MPU_I2C_Init();
	MPU6050_Init();
	Usart1_Init(115200);							//串口1，打印信息用	
	Usart2_Init(115200);							//串口2，驱动ESP8266用 
	OLED_Printf(1,10,OLED_8X16,"Hardware Init OK"); 
	OLED_Update();
	delay_ms(1000);
	OLED_Clear();
	OLED_Update();
}




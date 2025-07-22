#include "esp8266.h"

unsigned char esp8266_buf[512];
unsigned short esp8266_cnt = 0;


int ESP8266_Init(void)
{
	GPIO_InitTypeDef GPIO_Initure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	//ESP8266复位引脚
	GPIO_Initure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Initure.GPIO_Pin = GPIO_Pin_14;					//GPIOC14-复位
	GPIO_Initure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_Initure);
	
	GPIO_WriteBit(GPIOC, GPIO_Pin_14, Bit_RESET);
	delay_ms(500);
	GPIO_WriteBit(GPIOC, GPIO_Pin_14, Bit_SET);
	delay_ms(500);
	
	Usart_SendString(USART2, (unsigned char *)MQTT_AT,strlen((const char *)MQTT_AT));
	delay_ms(5000);
	Usart_SendString(USART2, (unsigned char *)MQTT_RST,strlen((const char *)MQTT_RST));
	delay_ms(5000);
	Usart_SendString(USART2, (unsigned char *)MQTT_CWMODE,strlen((const char *)MQTT_CWMODE));
	delay_ms(5000);	
	Usart_SendString(USART2, (unsigned char *)MQTT_CWDHCP,strlen((const char *)MQTT_CWDHCP));
	delay_ms(5000);
	Usart_SendString(USART2, (unsigned char *)MQTT_CWJAP,strlen((const char *)MQTT_CWJAP));
	delay_ms(5000);	
	Usart_SendString(USART2, (unsigned char *)MQTT_CIPMODE,strlen((const char *)MQTT_CIPMODE));
	delay_ms(5000);
	Usart_SendString(USART2, (unsigned char *)MQTT_CNN,strlen((const char *)MQTT_CNN));
		OLED_Printf(1, 10,OLED_8X16, "连接云平台 OK!");
		OLED_Update();
	delay_ms(5000);
		OLED_Clear();
		OLED_Update();	
	Usart_SendString(USART2, (unsigned char *)MQTT_CIPSEND,strlen((const char *)MQTT_CIPSEND));
		OLED_Printf(1, 10,OLED_8X16, "透传模式 OK!");
		OLED_Update();
	delay_ms(5000);
		OLED_Update();
		OLED_Clear();	
	OLED_Printf(1,10, OLED_8X16, "ESP8266 Init OK...");
	OLED_Update();
	
	delay_ms(1000);
	OLED_Clear();
	return 0;
}
void ESP8266_SendData(void)
{
	int16_t ax, ay, az;
	int16_t gx, gy, gz;
	float Pitch, Roll, Yaw;
	float body_temp;
	float systolic, diastolic;//收缩压，舒张压
	u8 hr, spo2;
	BloodPr_Show(&systolic,&diastolic);
	
	body_temp = Temp_Show();
	
	MAX30102_get(&hr, &spo2);
	
	MPU6050_Read_Accel(&ax, &ay, &az);
	MPU6050_Read_Gyro(&gx, &gy, &gz);//读取加速度和角速度数据	
	MPU6050_CalculateAngles(ax, ay, az, gx, gy, gz, &Pitch, &Roll, &Yaw);//计算角度

	if (Roll<-70 || Roll>70 ||Pitch<-70 || Pitch>70)
	{
		UsartPrintf(USART2, "cmd=2&uid=d311330c76795c8b2135f995e17ed468&topic=fallStatus&msg=#老人跌倒\r\n");
	}else 
	UsartPrintf(USART2, "cmd=2&uid=d311330c76795c8b2135f995e17ed468&topic=fallStatus&msg=#\r\n");
	UsartPrintf(USART2, "cmd=2&uid=d311330c76795c8b2135f995e17ed468&topic=temp&msg=#%.2f\r\n", body_temp);
	UsartPrintf(USART2, "cmd=2&uid=d311330c76795c8b2135f995e17ed468&topic=Systolic&msg=#%.2f\r\n", systolic);
	UsartPrintf(USART2, "cmd=2&uid=d311330c76795c8b2135f995e17ed468&topic=Diastolic&msg=#%.2f\r\n", diastolic);
	UsartPrintf(USART2, "cmd=2&uid=d311330c76795c8b2135f995e17ed468&topic=HeartRate&msg=#%d\r\n", hr);
	UsartPrintf(USART2, "cmd=2&uid=d311330c76795c8b2135f995e17ed468&topic=SPO2&msg=#%d\r\n", spo2);
	LED_blue(1);
	delay_ms(100);
	LED_blue(0);
	delay_ms(100);
}
/*
************************************************************
*	函数名称：	USART2_IRQHandler
*
*	函数功能：	串口2收发中断
*
*	入口参数：	无
*
*	返回参数：	无
*
*	说明：		
************************************************************
*/
void USART2_IRQHandler(void)
{

	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET) //接收中断
	{
		if(esp8266_cnt >= sizeof(esp8266_buf))	esp8266_cnt = 0; //防止串口被刷爆
		esp8266_buf[esp8266_cnt++] = USART2->DR;
		
		USART_ClearFlag(USART2, USART_FLAG_RXNE);
	}

}

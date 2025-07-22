#include "Menu.h"


uint8_t KeyNum;					//用于存储键码值
uint8_t D=2;					//用于存储目前按键是上还是下,默认下一项

/*把一级菜单的flag放到全局变量,静态存储,不会丢失数据,所以从二级菜单回来以后
仍能回到那一行,而不是每次都回到第一行*/
uint8_t flag = 1;

/*-----------------------------------------一级菜单----------------------------------------------*/
/**
  * @brief 一级菜单函数,用于显示一级菜单八行选项
  * @param  无
  * @retval 返回当前行是第几行
  */
int menu1(void)
{
	OLED_Clear();
	OLED_Update();
	OLED_ShowString(0, 0, "体温            ", OLED_8X16);
	OLED_ShowString(0, 16, "血压            ", OLED_8X16);
	OLED_ShowString(0, 32, "心率血氧        ", OLED_8X16);
	OLED_ShowString(0, 48, "MPU6050         ", OLED_8X16);
	OLED_Update();
	while(1)
	{
		KeyNum = Key_GetNum();
		if(KeyNum == 1)//上一项
		{
			flag --;
			if(flag == 0){flag = 8;}
			D = 1;//上一项标志
			OLED_AnimUpdate();//按下按钮,刷新一次动画效果
		}
		if(KeyNum == 3)//下一项
		{
			flag ++;
			if(flag == 9){flag = 1;}
			D = 2;//下一项标志
			OLED_AnimUpdate();//按下按钮,刷新一次动画效果
		}
		if(KeyNum == 2)//确认
		{
			OLED_Clear();
			OLED_Update();
			OLED_AnimUpdate();//按下按钮,刷新一次动画效果
			return flag;
		}
		switch(flag)
		{
			case 1:
			{
				OLED_ShowString(0, 0, "体温            ", OLED_8X16);//
				OLED_ShowString(0, 16, "血压            ", OLED_8X16);
				OLED_ShowString(0, 32, "心率血氧        ", OLED_8X16);
				OLED_ShowString(0, 48, "MPU6050         ", OLED_8X16);
				if(D==2){OLED_Animation(0,0,0,0,0,0,32,16);}//下
				if(D==1){OLED_Animation(0,16,32,16,0,0,32,16);}//上
				break;
			}
			case 2:
			{
				OLED_ShowString(0, 0, "体温            ", OLED_8X16);
				OLED_ShowString(0, 16, "血压            ", OLED_8X16);//
				OLED_ShowString(0, 32, "心率血氧        ", OLED_8X16);
				OLED_ShowString(0, 48, "MPU6050         ", OLED_8X16);
				if(D==2){OLED_Animation(0,0,32,16,0,16,32,16);}
				if(D==1){OLED_Animation(0,32,64,16,0,16,32,16);}
				break;
			}
			case 3:
			{
				OLED_ShowString(0, 0, "体温            ", OLED_8X16);
				OLED_ShowString(0, 16, "血压            ", OLED_8X16);
				OLED_ShowString(0, 32, "心率血氧        ", OLED_8X16);//
				OLED_ShowString(0, 48, "MPU6050         ", OLED_8X16);
				if(D==2){OLED_Animation(0,16,32,16,0,32,64,16);}
				if(D==1){OLED_Animation(0,48,56,16,0,32,64,16);}
				break;
			}
			case 4:
			{
				OLED_ShowString(0, 0, "体温            ", OLED_8X16);
				OLED_ShowString(0, 16, "血压            ", OLED_8X16);
				OLED_ShowString(0, 32, "心率血氧        ", OLED_8X16);
				OLED_ShowString(0, 48, "MPU6050         ", OLED_8X16);//
				if(D==2){OLED_Animation(0,32,64,16,0,48,56,16);}//下
				if(D==1){OLED_Animation(0,0,24,16,0,48,64,16);}//上
				break;
			}
			case 5:
			{
				OLED_ShowString(0, 0, "GPS             ", OLED_8X16);//
				OLED_ShowString(0, 16, "WIFI            ", OLED_8X16);
				OLED_ShowString(0, 32, "Time            ", OLED_8X16);
				OLED_ShowString(0, 48, "Seting            ", OLED_8X16);
				if(D==2){OLED_Animation(0,0,0,0,0,0,24,16);}
				if(D==1){OLED_Animation(0,16,32,16,0,0,24,16);}
				break;
			}
			case 6:
			{
				OLED_ShowString(0, 0, "GPS             ", OLED_8X16);
				OLED_ShowString(0, 16, "WIFI            ", OLED_8X16);//
				OLED_ShowString(0, 32, "Time            ", OLED_8X16);
				OLED_ShowString(0, 48, "Seting            ", OLED_8X16);
				if(D==2){OLED_Animation(0,0,24,16,0,16,32,16);}
				if(D==1){OLED_Animation(0,32,32,16,0,16,32,16);}
				break;
			}
			case 7:
			{
				OLED_ShowString(0, 0, "GPS             ", OLED_8X16);
				OLED_ShowString(0, 16, "WIFI            ", OLED_8X16);
				OLED_ShowString(0, 32, "Time            ", OLED_8X16);
				OLED_ShowString(0, 48, "Seting            ", OLED_8X16);
				if(D==2){OLED_Animation(0,16,32,16,0,32,32,16);}
				if(D==1){OLED_Animation(0,48,48,16,0,32,32,16);}
				break;
			}
			case 8:
			{
				OLED_ShowString(0, 0, "GPS             ", OLED_8X16);
				OLED_ShowString(0, 16, "WIFI            ", OLED_8X16);
				OLED_ShowString(0, 32, "Time            ", OLED_8X16);
				OLED_ShowString(0, 48, "Seting            ", OLED_8X16);
				if(D==2){OLED_Animation(0,32,32,16,0,48,48,16);}
				if(D==1){OLED_Animation(0,64,0,0,0,48,48,16);}
				break;
			}
		}
	}
}

/*------------------------------二级MPU6050菜单-------------------------------------*/
/****
	* @brief MPU6050二级菜单函数
	* @param 无
	* @retval 
	*/
int menu2_MPU6050(void)
{
	int16_t ax, ay, az;
	int16_t gx, gy, gz;
	float Pitch, Roll, Yaw;
	
	OLED_ShowString(0, 0, "<-                 ", OLED_8X16);
	OLED_Printf(0, 16, OLED_8X16, "俯仰角:%.2f       ",Pitch);
	OLED_Printf(0, 32, OLED_8X16, "偏航角:%.2f       ",Roll);
	OLED_Printf(0, 48, OLED_8X16, "老人状态: 未跌倒  ");
	OLED_Animation(0,0,0,0,0,0,16,16);
	OLED_Update();
	while(1)
	{		
		MPU6050_Read_Accel(&ax, &ay, &az);
		MPU6050_Read_Gyro(&gx, &gy, &gz);//读取加速度和角速度数据	
		MPU6050_CalculateAngles(ax, ay, az, gx, gy, gz, &Pitch, &Roll, &Yaw);//计算角度

		// 跌倒判断阈值
		if(Roll<-70 || Roll>70 ||Pitch<-70 || Pitch>70)
		{
			BEEP_ON();  // 检测到异常
			LED_red(1);
			delay_ms(100);
			BEEP_OFF();
			LED_red(0);
			delay_ms(100);
			OLED_Printf(0, 48, OLED_8X16, "老人状态:  跌倒!  ");
			OLED_Update();
		}
		else 
		{
			BEEP_OFF(); // 未检测到跌倒
			LED_red(0);
			OLED_Printf(0, 48, OLED_8X16, "老人状态: 未跌倒  ");
			OLED_Update();
		}
		KeyNum = Key_GetNum();
		if(KeyNum == 2)//确认
		{
			OLED_Clear();
			OLED_Update();
			OLED_AnimUpdate();//按下按钮,刷新一次动画效果
			return 0;
		}

		OLED_Printf(0, 16, OLED_8X16, "俯仰角:%.2f       ",Pitch);
		OLED_Printf(0, 32, OLED_8X16, "偏航角:%.2f       ",Roll);
		OLED_Update();
			
			
			
		
	}
}
/*----------------------------------------------------------------------------------*/

/*------------------------------二级温度菜单-------------------------------------*/
/****
	* @brief 温度二级菜单函数
	* @param 无
	* @retval 
	*/
int menu2_Temp(void)
{
	float body_temp;
	OLED_ShowString(0, 0, "<-                 ", OLED_8X16);
	OLED_Printf(32, 16,OLED_8X16, "体温检测");
	OLED_Printf(30, 32,OLED_8X16, "%.2f°C", body_temp);
	OLED_Animation(0,0,0,0,0,0,16,16);
	OLED_Update();
	
	while(1)
	{		
		body_temp = Temp_Show();
		if (body_temp > 38)
		{
			BEEP_ON();  // 检测到体温异常
			LED_red(1);
			delay_ms(100);
			BEEP_OFF();
			LED_red(0);
			delay_ms(100);
		}
		
		KeyNum = Key_GetNum();
		if(KeyNum == 2)//确认
		{
			OLED_Clear();
			OLED_Update();
			OLED_AnimUpdate();
			return 0;
		}
		OLED_Printf(32, 16,OLED_8X16, "体温检测");
		OLED_Printf(30, 32,OLED_8X16, "%.2f°C", body_temp);
		OLED_Update();
	}
}

/*----------------------------------------------------------------------------------*/

/*------------------------------MAX30102菜单-------------------------------------*/
/****
	* @brief MAX30102二级菜单函数
	* @param 无
	* @retval 
	*/
int menu2_MAX30102(void)
{
	u8 hr, spo2;
	OLED_ShowString(0, 0, "<-                 ", OLED_8X16);
	OLED_Printf(0, 32, OLED_8X16, "心率:%03d/min     ",hr);
	OLED_Printf(0, 48, OLED_8X16, "血氧:%03d%%       ",spo2);
	OLED_Animation(0,0,0,0,0,0,16,16);
	OLED_Update();
	while(1)
	{		
		MAX30102_get(&hr, &spo2);

		KeyNum = Key_GetNum();
		if(KeyNum == 2)//确认
		{
			OLED_Clear();
			OLED_Update();
			OLED_AnimUpdate();//按下按钮,刷新一次动画效果
			return 0;
		}
		OLED_Printf(0, 32, OLED_8X16, "心率:%03d/min     ",hr);
		OLED_Printf(0, 48, OLED_8X16, "血氧:%03d%%       ",spo2);
		OLED_Update();
	}
}
/*----------------------------------------------------------------------------------*/

/*------------------------------血压菜单-------------------------------------*/
/****
	* @brief 血压二级菜单函数
	* @param 无
	* @retval 
	*/
int menu2_Pressure(void)
{
	float systolic, diastolic;//收缩压，舒张压
	OLED_ShowString(0, 0, "<-                 ", OLED_8X16);
	OLED_Printf(32, 16,OLED_8X16, "血压检测");
	OLED_Printf(0, 32, OLED_8X16,"%.1f/%.1f mmHg", systolic - 2, diastolic - 2);//收缩压   舒张压
	OLED_Animation(0,0,0,0,0,0,16,16);
	OLED_Update();
	while(1)
	{		
		BloodPr_Show(&systolic,&diastolic);

		KeyNum = Key_GetNum();
		if(KeyNum == 2)//确认
		{
			OLED_Clear();
			OLED_Update();
			OLED_AnimUpdate();//按下按钮,刷新一次动画效果
			return 0;
		}
		OLED_Printf(32, 16,OLED_8X16, "血压检测");
		OLED_Printf(0, 32, OLED_8X16,"%.1f/%.1f mmHg", systolic - 2, diastolic - 2);//收缩压   舒张压
		OLED_Update();
	}
}
/*----------------------------------------------------------------------------------*/

/*------------------------------GPS菜单-------------------------------------*/
/****
	* @brief GPS二级菜单函数
	* @param 无
	* @retval 
	*/
int menu2_Location(void)
{
	OLED_ShowString(0, 0, "<-                 ", OLED_8X16);
	OLED_Printf(0, 16,OLED_8X16, "GPS定位:");
	OLED_Printf(0, 32,OLED_8X16, "35°08\'47.99\"N");
	OLED_Printf(0, 48, OLED_8X16,"113°57\'49.86\"E");
	OLED_Animation(0,0,0,0,0,0,16,16);
	OLED_Update();
	while(1)
	{		
		KeyNum = Key_GetNum();
		if(KeyNum == 2)//确认
		{
			OLED_Clear();
			OLED_Update();
			OLED_AnimUpdate();//按下按钮,刷新一次动画效果
			return 0;
		}
		OLED_Update();
	}
}
/*----------------------------------------------------------------------------------*/

/*---------------------------------二级时间菜单--------------------------------------*/
/****
	* @brief 时间二级菜单函数
	* @param 无
	* @retval 
	*/
int menu2_Clock(void)
{
	OLED_ShowString(0, 0, "<-                 ", OLED_8X16);
	OLED_Printf(0, 16, OLED_8X16, "Data:%d-%d-%d",MyRTC_Time[0],MyRTC_Time[1],MyRTC_Time[2]);
	OLED_Printf(0, 32, OLED_8X16, "Time:%d:%d:%d",MyRTC_Time[3],MyRTC_Time[4],MyRTC_Time[5]);
	OLED_ShowString(0, 48, "            设置", OLED_8X16);
	OLED_Animation(0,0,0,0,0,0,16,16);
	OLED_Update();
	while(1)
	{
		MyRTC_ReadTime();
		KeyNum = Key_GetNum();
		if(KeyNum == 2)//确认
		{
			OLED_Clear();
			OLED_Update();
			OLED_AnimUpdate();
			return 0;
		}
		OLED_Printf(0, 16, OLED_8X16, "Data:%d-%d-%d",MyRTC_Time[0],MyRTC_Time[1],MyRTC_Time[2]);
		OLED_Printf(0, 32, OLED_8X16, "Time:%d:%d:%d",MyRTC_Time[3],MyRTC_Time[4],MyRTC_Time[5]);
		OLED_ShowString(0, 48, "            设置", OLED_8X16);
		OLED_Update();
	}
}
/*----------------------------------------------------------------------------------*/



#include "stm32f10x.h"                  // Device header
#include <time.h>

/*调用设置时间时,将数组时间放入RTC,调用读取时间时,将RTC时间存入数组,注意个位数前面不要加0,否则为八进制数,此时9将显示不了*/
uint16_t MyRTC_Time[] = {2025, 1, 23, 16, 30, 0};//数组用于存放年月日时分秒,年份8位存不下所以用16位

void MyRTC_SetTime(void);//声明函数

/**
  * @brief RTC初始化函数
  * @param  无
  * @retval 无
  */
void MyRTC_Init(void)
{
	/*时钟开启*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);//开启PWR时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP, ENABLE);//开启BKP时钟

	PWR_BackupAccessCmd(ENABLE);				//使能PWR的DBP位
	
	/*初始化后在BKP写入0xA5A5,如果不为0xA5A5,说明上一次上电时主电源与备用电源都
	断过,此时进行初始化时间,把预先设定好的初始时间写入,否则说明备用电源没有断电,
	那么便不进行初始化,防止复位或重新上电把时间又给搞成初始时间了*/
	if(BKP_ReadBackupRegister(BKP_DR1) != 0xA5A5)
	{
		/*开启LSE时钟,并等待LES启动完成*/
		RCC_LSEConfig(RCC_LSE_ON);					//开启LSE振荡器
		while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) != SET);//等待LSERDY标志位为1,即等待开启完成
		
		/*选择RTCCLK时钟源*/
		RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);		//选择LSE作为时钟源
		RCC_RTCCLKCmd(ENABLE);						//使能RTCCLK选择
		
		/*两个等待,等待同步,等待上一次操作完成,防止BUG*/
		RTC_WaitForSynchro();//等待同步
		RTC_WaitForLastTask();//等待上一次操作完成
		
		/*配置预分频器*/
		RTC_SetPrescaler(32768 - 1);//进行32768分频(分频系数)使为1HZ,-1是因为从0开始,而CRL的CNF位在函数中已经做了,所以不需要手动进入配置和退出配置模式
		RTC_WaitForLastTask();		//由于写操作不是立马完成的,等待操作完成

		/*设置初始时间*/
		MyRTC_SetTime();

		BKP_WriteBackupRegister(BKP_DR1, 0xA5A5);//初始化后写入0xA5A5
	}
	else
	{
		/*两个等待,等待同步,等待上一次操作完成,防止BUG*/
		RTC_WaitForSynchro();//等待同步
		RTC_WaitForLastTask();//等待上一次操作完成	
	}

}

/**
  * @brief 设置RTC时间,将全局数组内部的数据转变成秒数写入CNT中
  * @param  无
  * @retval 无
  */
void MyRTC_SetTime(void)
{
	time_t time_cnt;
	struct tm time_data;
	/*将数组时间填入time_data中*/
	time_data.tm_year = MyRTC_Time[0] - 1900;//需要减去偏移1900(time.h中函数要求)
	time_data.tm_mon = MyRTC_Time[1] - 1;//需要减去偏移1(time.h中函数要求)
	time_data.tm_mday = MyRTC_Time[2];
	time_data.tm_hour = MyRTC_Time[3];
	time_data.tm_min = MyRTC_Time[4];
	time_data.tm_sec = MyRTC_Time[5];
	
	time_cnt = mktime(&time_data) - 8 * 60 * 60;//转换成秒放入time_cnt,减去偏移八小时,北京东八区
	
	RTC_SetCounter(time_cnt);//将秒数写入RTC时间
	RTC_WaitForLastTask();		//由于写操作不是立马完成的,等待操作完成
}

/**
  * @brief 读取RTC时间,将读取到的时间存入数组当中
  * @param  无
  * @retval 无
  */
void MyRTC_ReadTime(void)
{
	time_t time_cnt;
	struct tm time_data;

	time_cnt = RTC_GetCounter() + 8 * 60 * 60; //读取RTC的CNT秒数,北京处于东八区,加上8小时的秒偏移,不在hour加是因为如果是20,那20+8不就错误了
	
	time_data = *localtime(&time_cnt);//将CNT值转成日期赋值给time_data,由于返回值是指针,所以要加个*取值才可以赋给data

	MyRTC_Time[0] =time_data.tm_year + 1900;
	MyRTC_Time[1] =time_data.tm_mon + 1;
	MyRTC_Time[2] = time_data.tm_mday;
	MyRTC_Time[3] = time_data.tm_hour;
	MyRTC_Time[4] = time_data.tm_min;
	MyRTC_Time[5] = time_data.tm_sec;

}


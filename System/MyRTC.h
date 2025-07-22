#ifndef __MYRTC_H__
#define __MYRTC_H__

extern uint16_t MyRTC_Time[];//将数组扩展为外部可调用

void MyRTC_Init(void);
void MyRTC_SetTime(void);
void MyRTC_ReadTime(void);

#endif

#ifndef _XGZ6847A_BP_H_
#define _XGZ6847A_BP_H_


#include "xgz6847a.h"
#include "math.h"
#include "stdio.h"

// 血压模拟参数
#define SYSTOLIC_RATIO      0.6f    // 收缩压比例
#define DIASTOLIC_RATIO     0.4f    // 舒张压比例
#define BASE_SYSTOLIC       120.0f  // 基础收缩压(mmHg)
#define BASE_DIASTOLIC      80.0f   // 基础舒张压(mmHg)
#define PULSE_AMPLITUDE     10.0f   // 脉搏波动幅度

void XGZ6847A_SimulateBP(float *systolic, float *diastolic, float *pulse);\

#endif  

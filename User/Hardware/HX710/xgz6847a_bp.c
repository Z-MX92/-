#include "xgz6847a_bp.h"


/**
  * @brief  模拟测量血压
  * @param  systolic: 指向收缩压的指针
  * @param  diastolic: 指向舒张压的指针
  * @param  pulse: 指向脉搏率的指针(可选)
  * @retval 无
  */
void XGZ6847A_SimulateBP(float *systolic, float *diastolic, float *pulse)
{
    static uint32_t lastTick = 0;
    static float basePressure = 0;
    static uint8_t initialized = 0;
    static float phase = 0.0f;
    
    // 读取当前压力值
    float currentPressure = XGZ6847A_ReadPressure();
    
    // 第一次调用时初始化基准压力
    if(!initialized)
    {
        basePressure = currentPressure;
        initialized = 1;
    }
    
    // 计算压力变化 (模拟脉搏波动)
    phase += 0.1f;  // 相位增量
    if(phase > 2*3.14159f) phase -= 2*3.14159f;
    
    float pressureVariation = sinf(phase) * PULSE_AMPLITUDE;
    
    // 计算血压值 (mmHg)
    // 1 kPa ≈ 7.50062 mmHg
    *systolic = BASE_SYSTOLIC + pressureVariation * SYSTOLIC_RATIO;
    *diastolic = BASE_DIASTOLIC + pressureVariation * DIASTOLIC_RATIO;
    
    // 计算脉搏率 (固定值或根据时间计算)
    if(pulse != NULL)
    {
        *pulse = 72.0f;  // 默认72次/分钟
    }
}

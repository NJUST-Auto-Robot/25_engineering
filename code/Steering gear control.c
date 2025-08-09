#include "Steering gear control.h"
#include "stm32f4xx_it.h"
#include"stdlib.h"
#include"math.h"
#include "main.h"
#include "hardware_iic.h"
#include "FreeRTOS.h"
#include "task.h"
int pulse_remaining = 0;
//以下用来控制气泵
/*
气泵开关
*/
void Pump_Set_Angle(uint8_t angle)
{
    // 舵机常用脉宽：0°=0.5ms，180°=2.5ms，周期20ms
    // 计算脉宽（单位us）：pulse = 500 + (angle * 2000 / 180)
    uint32_t pulse_us = 500 + (angle * 2000 / 180);
    // 假设定时器时钟为1MHz，Period=19999，对应20ms
    // 占空比 = pulse_us
    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, pulse_us);
}
void Pump_Open(void)
{
	Pump_Set_Angle(180); // 打开气泵
}
void Pump_Close(void)
{
	Pump_Set_Angle(0); // 关闭气泵
}
/*
电磁阀开关，开阀时物品掉，开气泵前记得先关阀
*/
void Solenoid_Set_Angle(uint8_t angle)
{
    // 舵机常用脉宽：0°=0.5ms，180°=2.5ms，周期20ms
    // 计算脉宽（单位us）：pulse = 500 + (angle * 2000 / 180)
    uint32_t pulse_us = 500 + (angle * 2000 / 180);
    // 假设定时器时钟为1MHz，Period=19999，对应20ms
    // 占空比 = pulse_us
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, pulse_us);
}
void Solenoid_Open(void)
{
	Solenoid_Set_Angle(180); // 打开电磁阀
}
void Solenoid_Close(void)
{
	Solenoid_Set_Angle(0); // 关闭电磁阀
}
/*
该函数用来进行云台舵机控制
*/
void Yuntai_set_Angle(uint8_t angle)
{
    // 舵机常用脉宽：0°=0.5ms，180°=2.5ms，周期20ms
    // 计算脉宽（单位us）：pulse = 500 + (angle * 2000 / 180)
    uint32_t pulse_us = 500 + (angle * 2000 / 270);
    // 假设定时器时钟为1MHz，Period=19999，对应20ms
    // 占空比 = pulse_us
    __HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_1, pulse_us);
}
uint32_t calculate_pulses(float height)
{
   float pulses_per_mm = (Pulse_per_rev * Microstep) / Sigan_Pitch_mm;
    return (uint32_t)(fabs(height) * pulses_per_mm);
}
void Siganmove(float height_mm)
{  
    SiganDir = (height_mm > 0) ? 1 : 0;
    pulse_remaining = calculate_pulses(height_mm);
    pulse_remaining = pulse_remaining/8;
    if (pulse_remaining == 0) return;  
    SiganActive = 1; 
}
void Sigancatch(void)
{ if (color_flag == REDFLAG)
{
    while(RGBwithHSL[5]!=0XEF)
    {  
        Read_RGB_HSL();
        vTaskDelay(1);
        Siganmove(2);
        vTaskDelay(1);
    }
    Siganmove(20);
}
if (color_flag == YELLOWFLAG)
{
    while(RGBwithHSL[5]!=0XEF)
    {  
        Read_RGB_HSL();
        vTaskDelay(1);
        Siganmove(2);
        vTaskDelay(1);
    }
    Siganmove(20);
}
if (color_flag == BLUEFLAG)
{
    while(RGBwithHSL[5]!=0XEF)
    {  
        Read_RGB_HSL();
        vTaskDelay(1);
        Siganmove(2);
        vTaskDelay(1);
    }
    Siganmove(20);
}


}
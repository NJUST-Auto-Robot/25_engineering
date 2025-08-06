#include "stm32f4xx_hal.h"
#include "main.h"
#include "stdio.h"
#include "string.h"
#include "ZDTstepmotor.h"
#include "tim.h"
#define Sigan_Pitch_mm 2.0f
#define  Microstep 32
#define  Pulse_per_rev 6400
// extern int SiganActive ; // 舵机是否处于活动状态，1为活动，0为不活动
// extern int SiganDir; // 舵机方向，1为正转，0为反转
// extern int Siganbusy;
void Pump_Set_Angle(uint8_t angle);
void Pump_Open(void);
void Pump_Close(void);
void Solenoid_Set_Angle(uint8_t angle);
void Solenoid_Open(void);
void Solenoid_Close(void);
void Yuntai_set_Angle(uint8_t angle);
void Siganmove(float height_mm);
void Sigancatch(void);
uint32_t calculate_pulses(float height);

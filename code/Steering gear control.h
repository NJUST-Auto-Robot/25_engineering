#include "stm32f4xx_hal.h"
#include "main.h"
#include "stdio.h"
#include "string.h"
#include "ZDTstepmotor.h"
#include "tim.h"
void Pump_Set_Angle(uint8_t angle);
void Pump_Open(void);
void Pump_Close(void);
void Solenoid_Set_Angle(uint8_t angle);
void Solenoid_Open(void);
void Solenoid_Close(void);
void Yuntai_set_Angle(uint8_t angle);

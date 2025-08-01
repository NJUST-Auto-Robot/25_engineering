#ifndef __Motor_H
#define __Motor_H
#include "stm32f4xx_hal.h"
#include "ZDTstepmotor.h"
#include "hardware_iic.h"
#include "pid.h"
#include "usart.h"
#define BLACK 0;
#define WHITE 1;
#define LW4  4
#define LW3  3
#define LW2  2
#define LW1  1
#define RW1  1
#define RW2  2
#define RW3  3
#define RW4  4
void Motor_Speed_control(float speed1, float speed2, float speed3, float speed4);
void LineTracking();
























#endif
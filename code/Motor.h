#ifndef __Motor_H
#define __Motor_H
#include "stm32f4xx_hal.h"
#include "ZDTstepmotor.h"
#include "hardware_iic.h"
#include "pid.h"
#include "usart.h"
#define BLACK 0;
#define WHITE 1;
void Motor_Speed_control(float speed1, float speed2, float speed3, float speed4);
void LineTracking();
float limit_speed(float speed, float max_speed);
void limit_motors(float m1, float m2, float m3, float m4, float max_speed);
int Get_Black_Line_Position();
void Turn_Left();
void Turn_Right();
void Stop();























#endif
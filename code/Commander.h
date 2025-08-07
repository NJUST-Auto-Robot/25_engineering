#ifndef __COMMANDER_H
#define __COMMANDER_H
#include "stm32f4xx_hal.h"
#include "main.h"
#include "FSM.h"
#include "behavior_tree.h"
#include "Motor.h"
#include "Steering gear control.h"
#include "hardware_iic.h"

void motion_StateManager_Init(void);
void motion_StateManager_Execute(void);
extern int cross_flag;
#endif
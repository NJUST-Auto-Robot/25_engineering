/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f4xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx_it.h"
#include "FreeRTOS.h"
#include "task.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "hardware_iic.h"
#include "Steering gear control.h"
#include "ZDTstepmotor.h"
#include "Motor.h"
#include "Commander.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern TIM_HandleTypeDef htim4;
/* USER CODE BEGIN EV */
#define SiganPulse GPIO_PIN_6 
#define SiganPulse_GPIO_Port GPIOC
#define SiganDirection GPIO_PIN_7 
#define SiganDirection_GPIO_Port GPIOC
#define Sigan_Dir_Plus() HAL_GPIO_WritePin(SiganDirection_GPIO_Port, SiganDirection, GPIO_PIN_SET) // 设置方向为正转
#define Sigan_Dir_Minus() HAL_GPIO_WritePin(SiganDirection_GPIO_Port, SiganDirection, GPIO_PIN_RESET) // 设置方向为反转
#define SiganPulse_High() HAL_GPIO_WritePin(SiganPulse_GPIO_Port, SiganPulse, GPIO_PIN_SET) // 设置脉冲高电平
#define SiganPulse_Low() HAL_GPIO_WritePin(SiganPulse_GPIO_Port, SiganPulse, GPIO_PIN_RESET) // 设置脉冲低电平
extern uint32_t pulse_remaining;
int Sigan_Motor_State = 0;
int Sigan_Motor_Speed = 25;
int Sigan_Motor_Temp_Count = 0;
int SiganActive = 0; // 舵机初始化为不活动状态
  int SiganDir = 0; // 
  int Siganbusy = 0; // 步进电机初始化为空闲状态
int gray_state=0;
int gray_count=0;
int gray_delay_time=0;
int delay_no_conflict(int *delay_temp_count, int delay_time)
{

  (*delay_temp_count)++;
  pulse_remaining--;
  if (*delay_temp_count >= delay_time)
  {
    *delay_temp_count = 0;
    return 1;
  }
  else
    return 0;
}
int delay_no_conflict_state(int *delay_temp_count, int delay_time)
{

  (*delay_temp_count)++;
  if (*delay_temp_count >= delay_time)
  {
    *delay_temp_count = 0;
    return 1;
  }
  else
    return 0;
}
/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M4 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
   while (1)
  {
  }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Pre-fetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
#if (INCLUDE_xTaskGetSchedulerState == 1 )
  if (xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED)
  {
#endif /* INCLUDE_xTaskGetSchedulerState */
  xPortSysTickHandler();
#if (INCLUDE_xTaskGetSchedulerState == 1 )
  }
#endif /* INCLUDE_xTaskGetSchedulerState */
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F4xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f4xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles TIM4 global interrupt.
  */
void TIM4_IRQHandler(void)
{
  /* USER CODE BEGIN TIM4_IRQn 0 */
if (SiganActive==1)
{ if (SiganDir == 1) // 如果舵机方向为正转
  {
    Sigan_Dir_Plus(); // 设置方向为正转
  }
  else // 如果舵机方向为反转
  {
    Sigan_Dir_Minus(); // 设置方向为反转
  }
  switch (Sigan_Motor_State)
  {
  case 0:
   { if (pulse_remaining>0)
   {
   
    SiganPulse_High(); 
    Sigan_Motor_State += delay_no_conflict(&Sigan_Motor_Temp_Count, Sigan_Motor_Speed);
    // pulse_remaining--;
   }
   else
   {
    SiganActive = 0;
    Siganbusy = 0;
   }
    break;
   }
  case 1:
   { SiganPulse_Low(); 
    Sigan_Motor_State = 0;
   }
  default:
  break;
  }

}
  /* USER CODE END TIM4_IRQn 0 */
  HAL_TIM_IRQHandler(&htim4);
  /* USER CODE BEGIN TIM4_IRQn 1 */

  /* USER CODE END TIM4_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

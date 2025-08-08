#include "maintask.h"
#include "FreeRTOS.h"
#include "task.h"
#include "hardware_iic.h"
#include "Steering gear control.h"
#include "stdio.h"
#include "string.h"
#include "ZDTstepmotor.h"
#include "Motor.h"
#include "Commander.h"

TaskHandle_t motion_process_task_handle;
TaskHandle_t sensor_process_task_handle;
void motion_process_task(void *pvParameters);
void sensor_process_task(void *pvParameters);
void  main_task_create(void)
{
  Step_ZDT_Init(&Motor1, 2, &huart1, 0, 0.077f, true); // 初始化电机1
  vTaskDelay(10);
  Step_ZDT_Init(&Motor2, 1, &huart1, 1, 0.077f, false); // 初始化电机2
  vTaskDelay(10);
  Step_ZDT_Init(&Motor3, 3, &huart1, 0, 0.077f, false); // 初始化电机3
  vTaskDelay(10);
  Step_ZDT_Init(&Motor4, 4, &huart1, 1, 0.077f, false); // 初始化电机4
  vTaskDelay(10);
  motion_StateManager_Init(); // 初始化状态管理器
  Yuntai_set_Angle(65);
  Pump_Close();
  Solenoid_Close();
  vTaskDelay(1000); // 等待1秒钟，确保初始化完成

  BaseType_t ok2 = xTaskCreate(motion_process_task, "MotionProcess", 2000, NULL, 3  , &motion_process_task_handle);
  BaseType_t ok3 = xTaskCreate(sensor_process_task, "SensorProcess", 600, NULL, 2, &sensor_process_task_handle);

}
void motion_process_task(void *pvParameters)
{
  while(1)
	{
	  motion_StateManager_Execute(); // 执行状态机
    vTaskDelay(50); // 延时50毫秒
	}


}
void sensor_process_task(void *pvParameters)
{
  while (1)
  {
    // 传感器处理逻辑
    // 例如读取传感器数据并更新状态
    Read_RGB_HSL(); // 读取RGB和HSL数据
    vTaskDelay(1); // 延时10毫秒
    Update_Color_Flag(); // 更新颜色标志
    vTaskDelay(1);
    Read_All_GRAY_Digital(); // 读取灰度数据
    vTaskDelay(1); // 延时10毫秒
  }
}
#include "Motor.h"
void Motor_Speed_control(float speed1, float speed2, float speed3, float speed4)
{
    set_speed_target(&Motor1, speed1); // 设置电机1目标速度
    set_speed_target(&Motor2, speed2); // 设置电机2目标速度
    set_speed_target(&Motor3, speed3); // 设置电机3目标速度
    set_speed_target(&Motor4, speed4); // 设置电机4目标速度
}
void LineTracking()
{ char left[4] = {0};
  char right[4] = {0};
  for (int i = 0; i < 4; i++)
  {if (gray_front[i] == 0)
  {
    left[i] = 1; // 左侧传感器检测到黑线
  }
  else
  {
    left[i] = 0; // 左侧传感器未检测到黑线
  }
  }
  for (int i = 0; i < 4; i++)
  {if (gray_front[i + 4] == 0)
  {
    right[i] = 1; // 右侧传感器检测到黑线
  }
  else
  {
    right[i] = 0; // 右侧传感器未检测到黑线
  }
}
  
  int bias = 0;
  bias=(-4 * left[3]) + (-3 * left[2]) + (-2 * left[1]) + (-1 * left[0]) 
         + (1 * right[0]) + (2 * right[1]) + (3 * right[2]) + (4 * right[3]);
     Motor_Speed_control(0.1 + bias * 0.02, 0.1 - bias * 0.02, 0.1+ bias * 0.02, 0.1-bias * 0.02);
}

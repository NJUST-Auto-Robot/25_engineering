#include "Motor.h"
const float SENSOR_WEIGHTS[8] = {
    -4.0f, 
    -2.5f,
    -1.0f,
    -0.5f, 
     0.5f, 
     1.0f,
     2.5f,
     4.0f  
};
float limit_speed(float speed, float max_speed)
{
    if (speed > max_speed)  return max_speed;
    if (speed < -max_speed) return -max_speed;
    else return speed;
}
void limit_motors(float m1, float m2, float m3, float m4, float max_speed)
 {
    m1 = limit_speed(m1, max_speed);
    m2 = limit_speed(m2, max_speed);
    m3 = limit_speed(m3, max_speed);
    m4 = limit_speed(m4, max_speed);
}
void Motor_Speed_control(float s1, float s2, float s3, float s4)
{
    set_speed_target(&Motor1, s1); // 设置电机1目标速度
    set_speed_target(&Motor2, s2); // 设置电机2目标速度
    set_speed_target(&Motor3, s3); // 设置电机3目标速度
    set_speed_target(&Motor4, s4); // 设置电机4目标速度
}
int Get_Black_Line_Position()
{
  float weight_sum = 0.0f;
  int   count = 0;
  for (int i = 0; i < 8; i++)
  {
    if(gray_front[i] == 0)
    {
      weight_sum += SENSOR_WEIGHTS[i];
            count++;
    }
  }
  if ((gray_front[0]==0)&&(gray_front[1]==0)&&(gray_front[2]==0)&&(gray_front[3]==0)&&(gray_front[4]==0)&&(gray_front[5]==0)&&(gray_front[6]==0)&&(gray_front[7]==0))
  {
    return -1; //全黑线
  }
  if ((gray_front[0]==0)&&(gray_front[1]==0)&&(gray_front[2]==0)&&(gray_front[3]==0)&&(gray_front[4]==0)&&(gray_front[5]==1)&&(gray_front[6]==1)&&(gray_front[7]==1))
  {
    return -2;//左转
  }
   if ((gray_front[0]==1)&&(gray_front[1]==1)&&(gray_front[2]==1)&&(gray_front[3]==0)&&(gray_front[4]==0)&&(gray_front[5]==0)&&(gray_front[6]==0)&&(gray_front[7]==0))
  {
    return -3;//右转
  }
  float normalized_pos = (weight_sum / count + 4.0f) * 0.875f;
  return (int)(normalized_pos + 0.5f); 
}
void LineTracking()
 {
  int black_line_pos = Get_Black_Line_Position();
  // if (black_line_pos == -1)
  // {
  //   Stop(); // 停止所有电机
  // }
  // if (black_line_pos == -2)
  // {
  //   Turn_Left(); // 左转
  // }
  // if (black_line_pos == -3)
  // {
  //   Turn_Right(); // 右转
  // }
  float base_speed = 0.2f; // 设定基准速度
  float error = black_line_pos - 3.5f; 
  float error_weight = 0.1f; 
  float Correction = error * error_weight; 
  float speed1 = base_speed + Correction;
  float speed2 = base_speed - Correction;
  float speed3 = base_speed + Correction;
  float speed4 = base_speed - Correction;
  Motor_Speed_control(speed1, speed2, speed3, speed4);
}
void Turn_Left()
{
  set_speed_pos_target(&Motor1, 0.2f,  0.24f);
  set_speed_pos_target(&Motor2, 0.2f,  0.72f);
  set_speed_pos_target(&Motor3, 0.2f,  0.24f);
  set_speed_pos_target(&Motor4, 0.2f,  0.72f);
}
void Turn_Right()
{
  set_speed_pos_target(&Motor1, 0.2f,  0.72f);
  set_speed_pos_target(&Motor2, 0.2f,  0.24f);
  set_speed_pos_target(&Motor3, 0.2f,  0.72f);
  set_speed_pos_target(&Motor4, 0.2f,  0.24f);
}
void Stop()
{
  set_speed_target(&Motor1, 0.0f);
  set_speed_target(&Motor2, 0.0f);
  set_speed_target(&Motor3, 0.0f);
  set_speed_target(&Motor4, 0.0f);
}
#include "Motor.h"
int black_line_pos;
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
float Get_Black_Line_Position()
{
  float weight_sum = 0.0f;
  int   count = 0;
   if ((gray_front[0]==1)&&(gray_front[1]==1)&&(gray_front[2]==1)&&(gray_front[3]=1)&&(gray_front[4]==1)&&(gray_front[5]==1)&&(gray_front[6]==1)&&(gray_front[7]==1))
   {
    return 3.5;
   }
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
    return 3.5;
  }
  if ((gray_front[0]==0)&&(gray_front[1]==0)&&(gray_front[2]==0)&&(gray_front[3]==0)&&(gray_front[5]==1)&&(gray_front[6]==1)&&(gray_front[7]==1))
  {
    return 3.5;
  }
   if ((gray_front[0]==1)&&(gray_front[1]==1)&&(gray_front[2]==1)&&(gray_front[4]==0)&&(gray_front[5]==0)&&(gray_front[6]==0)&&(gray_front[7]==0))
  {
    return 3.5;
  }
  float normalized_pos = (weight_sum / count + 4.0f) * 0.875f;
  return (int)(normalized_pos + 0.5f); 
}
void LineTracking()
 {
  float black_line_pos = Get_Black_Line_Position();
  if (black_line_pos == 3.5)
  {
    Motor_Speed_control(0.2f, 0.2f, 0.2f, 0.2f);
  }
  
  float base_speed = 0.2f; // 设定基准速度
  float error = black_line_pos - 3.5f; 
  float error_weight = 0.05f; 
  float Correction = error * error_weight; 
  float speed1 = base_speed + Correction;
  float speed2 = base_speed - Correction;
  float speed3 = base_speed + Correction;
  float speed4 = base_speed - Correction;
  Motor_Speed_control(speed1, speed2, speed3, speed4);
}
void Turn_Left()
{
  set_speed_pos_target(&Motor1, -0.08f,  0.25f);
  set_speed_pos_target(&Motor2, 0.28f,  0.70f);
  set_speed_pos_target(&Motor3, 0.12f,  0.25f);
  set_speed_pos_target(&Motor4, 0.22f,  0.55f);
}
void Turn_Right()
{
  set_speed_pos_target(&Motor1, 0.28f,  0.70f);
  set_speed_pos_target(&Motor2, -0.08f,  0.25f);
  set_speed_pos_target(&Motor3, 0.22f,  0.55f);
  set_speed_pos_target(&Motor4, 0.12f,  0.25f);
}
void Stop()
{
  set_speed_target(&Motor1, 0.0f);
  set_speed_target(&Motor2, 0.0f);
  set_speed_target(&Motor3, 0.0f);
  set_speed_target(&Motor4, 0.0f);
}
void Move_Forward_Position(float target_pos)
{
  set_speed_pos_target(&Motor1, 0.2f, target_pos);
  set_speed_pos_target(&Motor2, 0.2f, target_pos);
  set_speed_pos_target(&Motor3, 0.2f, target_pos);
  set_speed_pos_target(&Motor4, 0.2f, target_pos);
}
void Move_Backward_Position(float target_pos)
{
  set_speed_pos_target(&Motor1, -0.2f, target_pos);
  set_speed_pos_target(&Motor2, -0.2f, target_pos);
  set_speed_pos_target(&Motor3, -0.2f, target_pos);
  set_speed_pos_target(&Motor4, -0.2f, target_pos);
}
void Move_Right_Position(float target_pos)
{
  set_speed_pos_target(&Motor1, 0.2f, target_pos);
  set_speed_pos_target(&Motor2, -0.2f, target_pos);
  set_speed_pos_target(&Motor3, -0.2f, target_pos);
  set_speed_pos_target(&Motor4, 0.2f, target_pos);
}
void Move_Left_Position(float target_pos)
{
  set_speed_pos_target(&Motor1, -0.2f, target_pos);
  set_speed_pos_target(&Motor2, 0.2f, target_pos);
  set_speed_pos_target(&Motor3, 0.2f, target_pos);
  set_speed_pos_target(&Motor4, -0.2f, target_pos);
}
void Motorangle(float angle)
{
  float ang=angle*0.2966f;
  ang=ang/90.0f;
  set_speed_pos_target(&Motor1, 0.2966f, ang); 
  set_speed_pos_target(&Motor2, -0.2966f, ang);
  set_speed_pos_target(&Motor3, 0.2966f, ang); 
  set_speed_pos_target(&Motor4, -0.2966f, ang);
}
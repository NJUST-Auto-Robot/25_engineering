#include "Commander.h"
#include "FreeRTOS.h"
#include "task.h"
FSM *FsmYellow = NULL;

static FSM_StateNode *Begin = NULL;
static FSM_StateNode *StageA = NULL;
static FSM_StateNode *CarryA = NULL;
static FSM_StateNode *Delivery_beginA1 = NULL;
static FSM_StateNode *Delivery_endA1 = NULL;
static FSM_StateNode *Back_beginA1 = NULL;
static FSM_StateNode *Back_endA1 = NULL;
static FSM_StateNode *Delivery_beginA2 = NULL;
static FSM_StateNode *Delivery_endA2 = NULL;
static FSM_StateNode *Back_beginA2 = NULL;
static FSM_StateNode *Back_endA2 = NULL;
static FSM_StateNode *Delivery_beginA3 = NULL;
static FSM_StateNode *Delivery_endA3 = NULL;
static FSM_StateNode *Back_beginA3 = NULL;
static FSM_StateNode *Back_endA3 = NULL;
static FSM_StateNode *Stop_mode = NULL;
static FSM_StateNode *CarryB = NULL;
static FSM_StateNode *Delivery_beginB1 = NULL;
static FSM_StateNode *Delivery_endB1 = NULL;
static FSM_StateNode *Back_beginB1 = NULL;
static FSM_StateNode *Back_endB1 = NULL;
static FSM_StateNode *Delivery_beginB2 = NULL;
static FSM_StateNode *Delivery_endB2 = NULL;
static FSM_StateNode *Back_beginB2 = NULL;
static FSM_StateNode *Back_endB2 = NULL;
static FSM_StateNode *Delivery_beginB3 = NULL;
static FSM_StateNode *Delivery_endB3 = NULL;
static FSM_StateNode *Back_beginB3 = NULL;
static FSM_StateNode *Back_endB3 = NULL;
static FSM_StateNode *CarryC = NULL;
static FSM_StateNode *Delivery_beginC1 = NULL;
static FSM_StateNode *Delivery_endC1 = NULL;
static FSM_StateNode *Back_beginC1 = NULL;
static FSM_StateNode *Back_endC1 = NULL;
static FSM_StateNode *Delivery_beginC2 = NULL;
static FSM_StateNode *Delivery_endC2 = NULL;
static FSM_StateNode *Back_beginC2 = NULL;
static FSM_StateNode *Back_endC2 = NULL;
static FSM_StateNode *Delivery_beginC3 = NULL;
static FSM_StateNode *Delivery_endC3 = NULL;
static FSM_StateNode *Back_beginC3 = NULL;
static FSM_StateNode *Back_endC3 = NULL;





extern void Begin_StateFunc(void *data);
extern void CarryA_StateFunc(void *data);
extern void Delivery_beginA1_StateFunc(void *data);
extern void Delivery_endA1_StateFunc(void *data);
extern void Back_beginA1_StateFunc(void *data);
extern void Back_endA1_StateFunc(void *data);
extern void Delivery_beginA2_StateFunc(void *data);
extern void Delivery_endA2_StateFunc(void *data);
extern void Back_beginA2_StateFunc(void *data);
extern void Back_endA2_StateFunc(void *data);
extern void Delivery_beginA3_StateFunc(void *data);
extern void Delivery_endA3_StateFunc(void *data);
extern void Back_beginA3_StateFunc(void *data);
extern void Back_endA3_StateFunc(void *data);
extern void CarryB_StateFunc(void *data);
extern void Delivery_beginB1_StateFunc(void *data);
extern void Delivery_endB1_StateFunc(void *data);
extern void Back_beginB1_StateFunc(void *data);
extern void Back_endB1_StateFunc(void *data);
extern void Delivery_beginB2_StateFunc(void *data);
extern void Delivery_endB2_StateFunc(void *data);
extern void Back_beginB2_StateFunc(void *data);
extern void Back_endB2_StateFunc(void *data);
extern void Delivery_beginB3_StateFunc(void *data);
extern void Delivery_endB3_StateFunc(void *data);
extern void Back_beginB3_StateFunc(void *data);
extern void Back_endB3_StateFunc(void *data);
extern void Stop_mode_StateFunc(void *data);
extern void CarryC_StateFunc(void *data);
extern void Delivery_beginC1_StateFunc(void *data);
extern void Delivery_endC1_StateFunc(void *data);
extern void Back_beginC1_StateFunc(void *data);
extern void Back_endC1_StateFunc(void *data);
extern void Delivery_beginC2_StateFunc(void *data);
extern void Delivery_endC2_StateFunc(void *data);
extern void Back_beginC2_StateFunc(void *data);
extern void Back_endC2_StateFunc(void *data);
extern void Delivery_beginC3_StateFunc(void *data);
extern void Delivery_endC3_StateFunc(void *data);
extern void Back_beginC3_StateFunc(void *data);
extern void Back_endC3_StateFunc(void *data);

extern bool ConditionA1(void *data);
extern bool ConditionA2(void *data);
extern bool ConditionA3(void *data);
extern bool ConditionA4(void *data);
extern bool ConditionA5(void *data);
extern bool ConditionA6(void *data);
extern bool ConditionB3(void *data);
extern bool ConditionB6(void *data);
extern bool ConditionC3(void *data);
extern bool ConditionC6(void *data);

int color_read=0;
int delivery_count=0;
int yellow_end_flag=0;
int finish_flag=0;
int cross_flag=0;
int cross_ready=0;
int blue_end_flag=0;
int red_end_flag=0;

void motion_StateManager_Init(void)
{
    FsmYellow = fsm_Create();
    Begin = fsm_Create_And_Add_State(FsmYellow, 0, "Begin", Begin_StateFunc);
    CarryA = fsm_Create_And_Add_State(FsmYellow, 1, "CarryA", CarryA_StateFunc);
    Delivery_beginA1 = fsm_Create_And_Add_State(FsmYellow, 2, "Delivery_beginA1", Delivery_beginA1_StateFunc);
    Delivery_endA1 = fsm_Create_And_Add_State(FsmYellow, 3, "Delivery_endA1", Delivery_endA1_StateFunc);
    Back_beginA1 = fsm_Create_And_Add_State(FsmYellow, 4, "Back_beginA1", Back_beginA1_StateFunc);
    Back_endA1 = fsm_Create_And_Add_State(FsmYellow, 5, "Back_endA1", Back_endA1_StateFunc);
    Delivery_beginA2 = fsm_Create_And_Add_State(FsmYellow, 6, "Delivery_beginA2", Delivery_beginA2_StateFunc);
    Delivery_endA2 = fsm_Create_And_Add_State(FsmYellow, 7, "Delivery_endA2", Delivery_endA2_StateFunc);
    Back_beginA2 = fsm_Create_And_Add_State(FsmYellow, 8, "Back_beginA2", Back_beginA2_StateFunc);
    Back_endA2 = fsm_Create_And_Add_State(FsmYellow, 9, "Back_endA2", Back_endA2_StateFunc);
    Delivery_beginA3 = fsm_Create_And_Add_State(FsmYellow, 10, "Delivery_beginA3", Delivery_beginA3_StateFunc);
    Delivery_endA3 = fsm_Create_And_Add_State(FsmYellow, 11, "Delivery_endA3", Delivery_endA3_StateFunc);
    Back_beginA3 = fsm_Create_And_Add_State(FsmYellow, 12, "Back_beginA3", Back_beginA3_StateFunc);
    Back_endA3 = fsm_Create_And_Add_State(FsmYellow, 13, "Back_endA3", Back_endA3_StateFunc);
    CarryB = fsm_Create_And_Add_State(FsmYellow, 15, "CarryB", CarryB_StateFunc);
    Delivery_beginB1 = fsm_Create_And_Add_State(FsmYellow, 16, "Delivery_beginB1", Delivery_beginB1_StateFunc);
    Delivery_endB1 = fsm_Create_And_Add_State(FsmYellow, 17, "Delivery_endB1", Delivery_endB1_StateFunc);
    Back_beginB1 = fsm_Create_And_Add_State(FsmYellow, 18, "Back_beginB1", Back_beginB1_StateFunc);
    Back_endB1 = fsm_Create_And_Add_State(FsmYellow, 19, "Back_endB1", Back_endB1_StateFunc);
    Delivery_beginB2 = fsm_Create_And_Add_State(FsmYellow, 20, "Delivery_beginB2", Delivery_beginB2_StateFunc);
    Delivery_endB2 = fsm_Create_And_Add_State(FsmYellow, 21, "Delivery_endB2", Delivery_endB2_StateFunc);
    Back_beginB2 = fsm_Create_And_Add_State(FsmYellow, 22, "Back_beginB2", Back_beginB2_StateFunc);
    Back_endB2 = fsm_Create_And_Add_State(FsmYellow, 23, "Back_endB2", Back_endB2_StateFunc);
    Delivery_beginB3 = fsm_Create_And_Add_State(FsmYellow, 24, "Delivery_beginB3", Delivery_beginB3_StateFunc);
    Delivery_endB3 = fsm_Create_And_Add_State(FsmYellow, 25, "Delivery_endB3", Delivery_endB3_StateFunc);
    Back_beginB3 = fsm_Create_And_Add_State(FsmYellow, 26, "Back_beginB3", Back_beginB3_StateFunc);
    Back_endB3 = fsm_Create_And_Add_State(FsmYellow, 27, "Back_endB3", Back_endB3_StateFunc);
    CarryC = fsm_Create_And_Add_State(FsmYellow, 28, "CarryC", CarryC_StateFunc);
    Delivery_beginC1 = fsm_Create_And_Add_State(FsmYellow, 29, "Delivery_beginC1", Delivery_beginC1_StateFunc);
    Delivery_endC1 = fsm_Create_And_Add_State(FsmYellow, 30, "Delivery_endC1", Delivery_endC1_StateFunc);
    Back_beginC1 = fsm_Create_And_Add_State(FsmYellow, 31, "Back_beginC1", Back_beginC1_StateFunc);
    Back_endC1 = fsm_Create_And_Add_State(FsmYellow, 32, "Back_endC1", Back_endC1_StateFunc);
    Delivery_beginC2 = fsm_Create_And_Add_State(FsmYellow, 33, "Delivery_beginC2", Delivery_beginC2_StateFunc);
    Delivery_endC2 = fsm_Create_And_Add_State(FsmYellow, 34, "Delivery_endC2", Delivery_endC2_StateFunc);
    Back_beginC2 = fsm_Create_And_Add_State(FsmYellow, 35, "Back_beginC2", Back_beginC2_StateFunc);
    Back_endC2 = fsm_Create_And_Add_State(FsmYellow, 36, "Back_endC2", Back_endC2_StateFunc);
    Delivery_beginC3 = fsm_Create_And_Add_State(FsmYellow, 37, "Delivery_beginC3", Delivery_beginC3_StateFunc);
    Delivery_endC3 = fsm_Create_And_Add_State(FsmYellow, 38, "Delivery_endC3", Delivery_endC3_StateFunc);
    Back_beginC3 = fsm_Create_And_Add_State(FsmYellow, 39, "Back_beginC3", Back_beginC3_StateFunc);
    Back_endC3 = fsm_Create_And_Add_State(FsmYellow, 40, "Back_endC3", Back_endC3_StateFunc);
    Stop_mode = fsm_Create_And_Add_State(FsmYellow, 14, "Stop_mode", Stop_mode_StateFunc);

    fsm_Add_Transition(Begin, CarryA, ConditionA1);
    fsm_Add_Transition(CarryA, Delivery_beginA1, ConditionA2);
    fsm_Add_Transition(Delivery_beginA1, Delivery_endA1, ConditionA1);
    fsm_Add_Transition(Delivery_endA1, Back_beginA1, ConditionA1);
    fsm_Add_Transition(Back_beginA1, Back_endA1, ConditionA3);
    fsm_Add_Transition(Back_endA1, Delivery_beginA1, ConditionA3);
    fsm_Add_Transition(CarryA, Delivery_beginA2, ConditionA4);
    fsm_Add_Transition(Delivery_beginA2, Delivery_endA2, ConditionA1);
    fsm_Add_Transition(Delivery_endA2, Back_beginA2, ConditionA1);
    fsm_Add_Transition(Back_beginA2, Back_endA2, ConditionA3);
    fsm_Add_Transition(Back_endA2, Delivery_beginA2, ConditionA3);
    fsm_Add_Transition(CarryA, Delivery_beginA3, ConditionA5);
    fsm_Add_Transition(Delivery_beginA3, Delivery_endA3, ConditionA1);
    fsm_Add_Transition(Delivery_endA3, Back_beginA3, ConditionA1);
    fsm_Add_Transition(Back_beginA3, Back_endA3, ConditionA3);
    fsm_Add_Transition(Back_endA3, Delivery_beginA3, ConditionA3);
    fsm_Add_Transition(Back_beginA1, Stop_mode, ConditionA6);
    fsm_Add_Transition(Back_beginA2, Stop_mode, ConditionA6);
    fsm_Add_Transition(Back_beginA3, Stop_mode, ConditionA6);
    fsm_Add_Transition(Stop_mode, CarryB, ConditionB3);
    fsm_Add_Transition(CarryB, Delivery_beginB1, ConditionA2);
    fsm_Add_Transition(Delivery_beginB1, Delivery_endB1, ConditionA1);
    fsm_Add_Transition(Delivery_endB1, Back_beginB1, ConditionA1);
    fsm_Add_Transition(Back_beginB1, Back_endB1, ConditionB3);
    fsm_Add_Transition(Back_endB1, Delivery_beginB1, ConditionB3);
    fsm_Add_Transition(CarryB, Delivery_beginB2, ConditionA4);
    fsm_Add_Transition(Delivery_beginB2, Delivery_endB2, ConditionA1);
    fsm_Add_Transition(Delivery_endB2, Back_beginB2, ConditionA1);
    fsm_Add_Transition(Back_beginB2, Back_endB2, ConditionB3);
    fsm_Add_Transition(Back_endB2, Delivery_beginB2, ConditionB3);
    fsm_Add_Transition(CarryB, Delivery_beginB3, ConditionA5);
    fsm_Add_Transition(Delivery_beginB3, Delivery_endB3, ConditionA1);
    fsm_Add_Transition(Delivery_endB3, Back_beginB3, ConditionA1);
    fsm_Add_Transition(Back_beginB3, Back_endB3, ConditionB3);
    fsm_Add_Transition(Back_endB3, Delivery_beginB3, ConditionB3);
    fsm_Add_Transition(Back_beginB1, Stop_mode, ConditionB6);
    fsm_Add_Transition(Back_beginB2, Stop_mode, ConditionB6);
    fsm_Add_Transition(Back_beginB3, Stop_mode, ConditionB6);
    fsm_Add_Transition(Stop_mode, CarryC, ConditionC3);
    fsm_Add_Transition(CarryC, Delivery_beginC1, ConditionA2);
    fsm_Add_Transition(Delivery_beginC1, Delivery_endC1, ConditionA1);
    fsm_Add_Transition(Delivery_endC1, Back_beginC1, ConditionA1);
    fsm_Add_Transition(Back_beginC1, Back_endC1, ConditionC3);
    fsm_Add_Transition(Back_endC1, Delivery_beginC1, ConditionC3);
    fsm_Add_Transition(CarryC, Delivery_beginC2, ConditionA4);
    fsm_Add_Transition(Delivery_beginC2, Delivery_endC2, ConditionA1);
    fsm_Add_Transition(Delivery_endC2, Back_beginC2, ConditionA1);
    fsm_Add_Transition(Back_beginC2, Back_endC2, ConditionC3);
    fsm_Add_Transition(Back_endC2, Delivery_beginC2, ConditionC3);
    fsm_Add_Transition(CarryC, Delivery_beginC3, ConditionA5);
    fsm_Add_Transition(Delivery_beginC3, Delivery_endC3, ConditionA1);
    fsm_Add_Transition(Delivery_endC3, Back_beginC3, ConditionA1);
    fsm_Add_Transition(Back_beginC3, Back_endC3, ConditionC3);
    fsm_Add_Transition(Back_endC3, Delivery_beginC3, ConditionC3);
    fsm_Add_Transition(Back_endC1, Stop_mode, ConditionC6);
    fsm_Add_Transition(Back_endC2, Stop_mode, ConditionC6);
    fsm_Add_Transition(Back_endC3, Stop_mode, ConditionC6);
    fsm_Set_Initial_State(FsmYellow, Begin); // 设置初始状态
}

void motion_StateManager_Execute()
{
    fsm_Execute(FsmYellow, NULL); // 执行状态机
}

void Begin_StateFunc(void *data)
{
    cross_ready=0;
    cross_flag = 0;
    while (cross_flag!=4)
    {
    LineTracking();
    if(gray_front[6]==0&& gray_front[7]==0||gray_front[0]==0&&gray_front[1]==0)
    {
        cross_ready=1;
    }
    if (gray_right[3]==0&&cross_ready==1)
    {
        cross_flag++;
        cross_ready=0;
    }
    }
    Stop();
    vTaskDelay(500);
    finish_flag=1;
    
}
bool ConditionA1(void *data)
{
    return finish_flag==1;
}
void CarryA_StateFunc(void *data)
{
    finish_flag=0;
    Move_Backward_Position(0.05f);
    vTaskDelay(1500);
    Move_Right_Position(0.3f);
    vTaskDelay(3000);
    color_read=color_flag;
    Solenoid_Close();
    Pump_Open();
    Sigancatch();
    vTaskDelay(2500);
    Siganmove(-100.0f);
    vTaskDelay(1500);
    Move_Left_Position(0.3f);
    vTaskDelay(1500);
    Motorangle(180.0f);
    vTaskDelay(3200);
    finish_flag=1;
}
bool ConditionA2(void *data)
{
    return finish_flag==1&&color_read==YELLOWFLAG;
}
void Delivery_beginA1_StateFunc(void *data)
{
    finish_flag=0;
    cross_ready=0;
    cross_flag = 0;
    if (delivery_count>=1)
    {
        Move_Forward_Position(0.43f);
        vTaskDelay(2200);
    }
    else{
        Move_Forward_Position(0.25f);
        vTaskDelay(1500);
    }
    Stop();
    vTaskDelay(500);
    niMotorangle(90.0f);
    vTaskDelay(2200);
    while (gray_front[7]!= 0)
    {
        LineTracking();
        vTaskDelay(10);
    }
    Stop();
    vTaskDelay(500);
    Move_Forward_Position(0.13f);
    vTaskDelay(2200);
    Move_Right_Position(0.6f);
    vTaskDelay(3200);
    finish_flag=1;
}
void Delivery_endA1_StateFunc(void *data)
{
    finish_flag=0;
    switch (delivery_count)
    {
    case 0:
        Move_Forward_Position(0.15f);
        vTaskDelay(1500);
        Yuntai_set_Angle(95);
        vTaskDelay(500);
        Pump_Close();
        Solenoid_Open();
        vTaskDelay(1500);
        Yuntai_set_Angle(65);
        vTaskDelay(1500);
        Move_Backward_Position(0.15f);
        vTaskDelay(1500);
        break;
    
    case 1:
        Move_Forward_Position(0.15f);
        vTaskDelay(1500);
        Yuntai_set_Angle(15);
        vTaskDelay(500);
        Pump_Close();
        Solenoid_Open();
        vTaskDelay(1500);
        Yuntai_set_Angle(65);
        vTaskDelay(1500);
        Move_Backward_Position(0.15f);
        vTaskDelay(1500);
        break;
    case 2:
        Pump_Close();
        Solenoid_Open();
        break;
    }
    finish_flag=1;
}
void Back_beginA1_StateFunc(void *data)
{
    finish_flag=0;
    if(delivery_count==2){
        niMotorangle(90.0f);
        vTaskDelay(2200);
        Move_Forward_Position(0.6f);
        vTaskDelay(3200);
        yellow_end_flag=1;
    }
    else{
        Move_Left_Position(0.6f);
        vTaskDelay(3200);
        niMotorangle(180.0f);
        vTaskDelay(2200);
        Move_Forward_Position(0.1f);
        vTaskDelay(500);
        while (gray_right[3]!= 0)
        {
            LineTracking();
        }
        Stop();
        vTaskDelay(500);
        Motorangle(90.0f);
        vTaskDelay(2200);
        while (gray_right[3]!= 0 )
        {
            LineTracking();
        }
        Stop();
        vTaskDelay(500);
    }
    finish_flag=1;       
    
}
void Back_endA1_StateFunc(void *data)
{
    finish_flag=0;
    switch (delivery_count)
    {
    case 0:
        Move_Right_Position(0.25f);
        vTaskDelay(1500);
        Move_Forward_Position(0.15f);
        vTaskDelay(1500);
        Yuntai_set_Angle(85);
        vTaskDelay(3200);
        Solenoid_Close();
        Pump_Open();
        Sigancatch();
        vTaskDelay(2500);
        Siganmove(-100.0f);
        vTaskDelay(1500);
        Yuntai_set_Angle(65);
        vTaskDelay(1500);
        Move_Left_Position(0.27f);
        vTaskDelay(2200);
        Motorangle(180.0f);
        vTaskDelay(2200);
        delivery_count++;
        break;
    case 1:
        Move_Right_Position(0.33f);
        vTaskDelay(2200);
        Move_Forward_Position(0.15f);
        vTaskDelay(1500);
        Yuntai_set_Angle(45);
        vTaskDelay(3200);
        Solenoid_Close();
        Pump_Open();
        Sigancatch();
        vTaskDelay(2500);
        Siganmove(-100.0f);
        vTaskDelay(1500);
        Yuntai_set_Angle(65);
        vTaskDelay(1500);
        Move_Left_Position(0.36f);
        vTaskDelay(2200);
        Motorangle(180.0f);
        vTaskDelay(2200);
        delivery_count++;
        break;
    case 2:
        delivery_count=0;
        yellow_end_flag=1;
        break;
    }
    finish_flag=1;
}
bool ConditionA3(void *data)
{
    return finish_flag==1 && yellow_end_flag==0;
}
bool ConditionB3(void *data){
    return finish_flag==1 && blue_end_flag==0;
}
bool ConditionA4(void *data)
{
    return finish_flag==1 && color_read==BLUEFLAG;
}
void Delivery_beginA2_StateFunc(void *data)
{
    finish_flag=0;
    cross_ready=0;
    cross_flag = 0;
    while (cross_flag<=2)
    {
    LineTracking();
    if((gray_front[6]== 0 && gray_front[7] == 0)||(gray_front[0]== 0 && gray_front[1] == 0))
    {
        cross_ready=1;
    }
    if (gray_right[3]==0&&cross_ready==1)
    {
        cross_flag++;
        cross_ready=0;
    }
    }
    while(cross_flag<=3)
    {
    LineTracking();
    if(gray_front[0]== 0 && gray_front[1] == 0)
    {
        Move_Forward_Position(0.1f);
        vTaskDelay(500);
        cross_flag++;
    }
     }
    Stop();
    vTaskDelay(1500);
    niMotorangle(90.0f);
    vTaskDelay(1500);
    Move_Forward_Position(0.3f);
    vTaskDelay(1500);
    finish_flag=1;
}
void Delivery_endA2_StateFunc(void *data)
{
    finish_flag=0;
    switch (delivery_count)
    {
    case 0:
        Move_Forward_Position(0.15f);
        vTaskDelay(1500);
        Yuntai_set_Angle(95);
        vTaskDelay(1500);
        Pump_Close();
        Solenoid_Open();
        vTaskDelay(1500);
        Yuntai_set_Angle(65);
        vTaskDelay(1500);
        Move_Backward_Position(0.15f);
        vTaskDelay(1500);
        break;
    
    case 1:
        Move_Forward_Position(0.15f);
        vTaskDelay(1500);
        Yuntai_set_Angle(15);
        vTaskDelay(1500);
        Pump_Close();
        Solenoid_Open();
        vTaskDelay(1500);
        Yuntai_set_Angle(65);
        vTaskDelay(1500);
        Move_Backward_Position(0.15f);
        vTaskDelay(1500);
        break;
    case 2:
        Pump_Close();
        Solenoid_Open();
        break;
    }
    finish_flag=1;
}
void Back_beginA2_StateFunc(void *data)
{
    finish_flag=0;
    cross_flag = 0;
    cross_ready=0;
    if(delivery_count==2){
        Move_Backward_Position(0.3f);
        vTaskDelay(2200);
        niMotorangle(90.0f);
        vTaskDelay(2200);
        while (cross_flag!=3)
        {
        LineTracking();
     if(gray_right[0]==0)
    {
        cross_ready=1;
    }
    if (gray_right[3]==0&&cross_ready==1)
    {
        cross_flag++;
        cross_ready=0;
    }
        }
    Motorangle(90.0f);
    vTaskDelay(2200);
        while (gray_right[3]!= 0)
    {
        LineTracking();
        vTaskDelay(10);
    }
    Stop();
    vTaskDelay(500);
    niMotorangle(90.0f);
    vTaskDelay(2200);
    yellow_end_flag=1;

}
    else{
        Move_Backward_Position(0.3f);
        vTaskDelay(2200);
        niMotorangle(90.0f);
        vTaskDelay(2200);
        while (cross_flag!=4)
        {
        LineTracking();
     if(gray_right[0]==0)
    {
        cross_ready=1;
    }
    if (gray_right[3]==0&&cross_ready==1)
    {
        cross_flag++;
        cross_ready=0;
    }
        }
    Stop();
    vTaskDelay(1500);
    }
    
    finish_flag=1;
}
void Back_endA2_StateFunc(void *data)
{
    finish_flag=0;
    switch (delivery_count)
    {
    case 0:
        Move_Right_Position(0.25f);
        vTaskDelay(1500);
        Move_Forward_Position(0.15f);
        vTaskDelay(1500);
        Yuntai_set_Angle(85);
        vTaskDelay(3200);
        Solenoid_Close();
        Pump_Open();
        Sigancatch();
        vTaskDelay(2500);
        Siganmove(-100.0f);
        vTaskDelay(1500);
        Yuntai_set_Angle(65);
        vTaskDelay(1500);
        Move_Left_Position(0.25f);
        vTaskDelay(2200);
        Motorangle(180.0f);
        vTaskDelay(2200);
        delivery_count++;
        break;
    case 1:
        Move_Right_Position(0.33f);
        vTaskDelay(2200);
        Move_Forward_Position(0.15f);
        vTaskDelay(1500);
        Yuntai_set_Angle(45);
        vTaskDelay(3200);
        Solenoid_Close();
        Pump_Open();
        Sigancatch();
        vTaskDelay(2500);
        Siganmove(-100.0f);
        vTaskDelay(1500);
        Yuntai_set_Angle(65);
        vTaskDelay(1500);
        Move_Left_Position(0.33f);
        vTaskDelay(2200);
        Motorangle(180.0f);
        vTaskDelay(2200);
        delivery_count++;
        break;
    case 2:
        delivery_count=0;
        yellow_end_flag=1;
        break;
    }
    finish_flag=1;
}
bool ConditionA5(void *data)
{
    return finish_flag==1 && color_read==REDFLAG;
}
void Delivery_beginA3_StateFunc(void *data)
{
    finish_flag=0;
    cross_ready=0;
    cross_flag = 0;
    while (cross_flag<=2)
    {
    LineTracking();
    if((gray_front[6]== 0 && gray_front[7] == 0)||(gray_front[0]== 0 && gray_front[1] == 0))
    {
        cross_ready=1;
    }
    if (gray_right[3]==0&&cross_ready==1)
    {
        cross_flag++;
        cross_ready=0;
    }
    }
    while(cross_flag<=5)
    {
    LineTracking();
    if(gray_front[0]== 0 && gray_front[1] == 0)
    {
        Move_Forward_Position(0.1f);
        vTaskDelay(500);
        cross_flag++;
    }
     }
    Stop();
    vTaskDelay(1500);
    Move_Forward_Position(0.05f);
    vTaskDelay(500);
    niMotorangle(90.0f);
    vTaskDelay(2200);
    while (gray_front[0]!= 0 || gray_front[1] != 0)
    {
        LineTracking();
    }
    Stop();
    vTaskDelay(1500);
    Move_Left_Position(0.3f);
    vTaskDelay(2200);
    Move_Forward_Position(0.75f);
    vTaskDelay(4400);
    niMotorangle(90.0f);
    vTaskDelay(2200);
    finish_flag=1;
}
void Delivery_endA3_StateFunc(void *data)
{
    finish_flag=0;
    switch (delivery_count)
    {
    case 0:
        Move_Forward_Position(0.15f);
        vTaskDelay(1500);
        Yuntai_set_Angle(125);
        vTaskDelay(1500);
        Pump_Close();
        Solenoid_Open();
        Yuntai_set_Angle(65);
        vTaskDelay(1500);
        Move_Backward_Position(0.15f);
        vTaskDelay(1500);
        break;
    
    case 1:
        Move_Forward_Position(0.15f);
        vTaskDelay(1500);
        Yuntai_set_Angle(35);
        vTaskDelay(1500);
        Pump_Close();
        Solenoid_Open();
        Yuntai_set_Angle(65);
        vTaskDelay(1500);
        Move_Backward_Position(0.15f);
        vTaskDelay(1500);
        break;
    case 2:
        Pump_Close();
        Solenoid_Open();
        vTaskDelay(1500);
        break;
    }
    finish_flag=1;
}
void Back_beginA3_StateFunc(void *data)
{
    Solenoid_Close();
    finish_flag=0;
    cross_ready=0;
    cross_flag = 0;
    if(delivery_count==2){
        niMotorangle(90.0f);
        vTaskDelay(2200);
        Move_Forward_Position(0.8f);
        vTaskDelay(3200);
        Move_Left_Position(0.3f);
        vTaskDelay(2200);
        while (gray_right[3]!= 0)
        {
            LineTracking();
        }
        Stop();
        vTaskDelay(1500);
        Motorangle(90.0f);
        vTaskDelay(1500);
        while (cross_flag!=5)
        {
            LineTracking();
    if(gray_right[0]==0)
    {
        cross_ready=1;
    }
    if (gray_right[3]==0&&cross_ready==1)
    {
        cross_flag++;
        cross_ready=0;
    }
        }
        Stop();
        vTaskDelay(1500);
        Motorangle(90.0f);
        vTaskDelay(1500);
        Move_Forward_Position(0.1f);
        vTaskDelay(1000);
        while (gray_right[3]!= 0 )
        {
            LineTracking();
        }
        Stop();
        vTaskDelay(1500);
        niMotorangle(90.0f);
        vTaskDelay(2200);
        yellow_end_flag=1;
    }
    else{
        niMotorangle(90.0f);
        vTaskDelay(2200);
        Move_Forward_Position(0.8f);
        vTaskDelay(3200);
        Move_Left_Position(0.3f);
        vTaskDelay(2200);
        while (gray_right[3]!= 0)
        {
            LineTracking();
        }
        Stop();
        vTaskDelay(1500);
        Motorangle(90.0f);
        vTaskDelay(1500);
        while (cross_flag!=6)
        {
        LineTracking();
     if(gray_right[0]==0)
    {
        cross_ready=1;
    }
    if (gray_right[3]==0&&cross_ready==1)
    {
        cross_flag++;
        cross_ready=0;
    }
        }
    Stop();
    vTaskDelay(1500);
    }
    finish_flag=1;       
}
void Back_endA3_StateFunc(void *data)
{
    finish_flag=0;
    switch (delivery_count)
    {
    case 0:
        Move_Right_Position(0.25f);
        vTaskDelay(1500);
        Move_Forward_Position(0.15f);
        vTaskDelay(1500);
        Yuntai_set_Angle(85);
        vTaskDelay(3200);
        Solenoid_Close();
        Pump_Open();
        Sigancatch();
        vTaskDelay(2500);
        Siganmove(-100.0f);
        vTaskDelay(1500);
        Yuntai_set_Angle(65);
        vTaskDelay(1500);
        Move_Left_Position(0.25f);
        vTaskDelay(2200);
        Motorangle(180.0f);
        vTaskDelay(2200);
        delivery_count++;
        break;
    case 1:
        Move_Right_Position(0.33f);
        vTaskDelay(2200);
        Move_Forward_Position(0.15f);
        vTaskDelay(1500);
        Yuntai_set_Angle(45);
        vTaskDelay(3200);
        Solenoid_Close();
        Pump_Open();
        Sigancatch();
        vTaskDelay(2500);
        Siganmove(-100.0f);
        vTaskDelay(1500);
        Yuntai_set_Angle(65);
        vTaskDelay(1500);
        Move_Left_Position(0.33f);
        vTaskDelay(2200);
        Motorangle(180.0f);
        vTaskDelay(2200);
        delivery_count++;
        break;
    case 2:
        delivery_count=0;
        yellow_end_flag=1;
        break;
    }
    finish_flag=1;
}   
bool ConditionA6(void *data)
{
    return finish_flag==1 && yellow_end_flag==1;
}
bool ConditionB6(void *data){
    return finish_flag==1 && blue_end_flag==1;
}
void Stop_mode_StateFunc(void *data)
{
    Stop();
    vTaskDelay(1500);
}
void CarryB_StateFunc(void *data)
{
    finish_flag=0;
    delivery_count=0;
    Move_Forward_Position(0.25f);
    vTaskDelay(2200);
    color_read=color_flag;
    Solenoid_Close();
    Pump_Open();
    Sigancatch();
    vTaskDelay(2200);
    Siganmove(-100.0f);
    vTaskDelay(1500);
    finish_flag=1;
}
void Delivery_beginB1_StateFunc(void *data){

    finish_flag=0;
    cross_ready=0;
    cross_flag = 0;
    Move_Backward_Position(0.25f);
    vTaskDelay(2200);
    Motorangle(180.0f);
    vTaskDelay(2200);
    while (gray_front[7]!=0)
    {
        LineTracking();
        vTaskDelay(10);
    }
    Stop();
    vTaskDelay(1500);
    Move_Forward_Position(0.1f);
    vTaskDelay(500);
    niMotorangle(90.0f);
    vTaskDelay(2200);
    finish_flag=1;
}
void Delivery_endB1_StateFunc(void *data){
    finish_flag=0;
    switch (delivery_count)
    {
    case 0:
        Move_Forward_Position(0.15f);
        vTaskDelay(1500);
        Yuntai_set_Angle(125);
        vTaskDelay(1500);
        Pump_Close();
        Solenoid_Open();
        Yuntai_set_Angle(65);
        vTaskDelay(1500);
        Move_Backward_Position(0.15f);
        vTaskDelay(1500);
        break;
    
    case 1:
        Move_Forward_Position(0.15f);
        vTaskDelay(1500);
        Yuntai_set_Angle(35);
        vTaskDelay(1500);
        Pump_Close();
        Solenoid_Open();
        Yuntai_set_Angle(65);
        vTaskDelay(1500);
        Move_Backward_Position(0.15f);
        vTaskDelay(1500);
        break;
    case 2:
        Pump_Close();
        Solenoid_Open();
        vTaskDelay(1500);
        break;
    }
    finish_flag=1;
}
void Back_beginB1_StateFunc(void *data)
{
    finish_flag=0;
    cross_flag = 0;
    cross_ready=0;
    niMotorangle(90.0f);
    vTaskDelay(2200);
    while (gray_right[3]!=0)
    {
        LineTracking();
        vTaskDelay(10);
    }
    Move_Forward_Position(0.1f);
    vTaskDelay(500);
    while(gray_right[3]!=0){
        LineTracking();
        vTaskDelay(10);
    }
    Stop();
    vTaskDelay(500);
    if (delivery_count==2)
    {
        Motorangle(90.0f);
        vTaskDelay(2200);
        while (gray_right[3]!= 0)
        {
            LineTracking();
            vTaskDelay(10);
        }
        niMotorangle(90.0f);
        vTaskDelay(2200);
        blue_end_flag=1;
    }
    else{
        Move_Forward_Position(0.4f);
        vTaskDelay(3200);
    }
    finish_flag=1;
}
void Back_endB1_StateFunc(void *data){
    finish_flag=0;
    switch (delivery_count)
    {
    case 0:
        Move_Left_Position(0.05f);
        vTaskDelay(500);
        Yuntai_set_Angle(85);
        vTaskDelay(3200);
        Solenoid_Close();
        Pump_Open();
        Sigancatch();
        vTaskDelay(2500);
        Siganmove(-100.0f);
        vTaskDelay(1500);
        Yuntai_set_Angle(65);
        vTaskDelay(1500);
        Move_Backward_Position(0.15f);
        vTaskDelay(1500);
        delivery_count++;
        break;
    case 1:
        Move_Right_Position(0.05f);
        vTaskDelay(500);
        Yuntai_set_Angle(45);
        vTaskDelay(3200);
        Solenoid_Close();
        Pump_Open();
        Sigancatch();
        vTaskDelay(2500);
        Siganmove(-100.0f);
        vTaskDelay(1500);
        Yuntai_set_Angle(65);
        Move_Left_Position(0.05f);
        vTaskDelay(500);
        Move_Backward_Position(0.15f);
        vTaskDelay(1500);
        delivery_count++;
        break;
    case 2:
        Pump_Close();
        Solenoid_Open();
        vTaskDelay(1500);
        break;
    }
    finish_flag=1;
}
void Delivery_beginB2_StateFunc(void *data){
    finish_flag=0;
    cross_ready=0;
    cross_flag = 0;
    Move_Left_Position(0.9f);
    vTaskDelay(3500);
    Motorangle(180.0f);
    vTaskDelay(2200);
    while (cross_flag<=2)
    {
    LineTracking();
    if((gray_front[6]== 0 && gray_front[7] == 0)||(gray_front[0]== 0 && gray_front[1] == 0))
    {
        cross_ready=1;
    }
    if (gray_right[3]==0&&cross_ready==1)
    {
        cross_flag++;
        cross_ready=0;
    }
    }
    while(cross_flag<=3)
    {
    LineTracking();
    if(gray_front[0]== 0 && gray_front[1] == 0)
    {
        Move_Forward_Position(0.1f);
        vTaskDelay(500);
        cross_flag++;
    }
     }
    Stop();
    vTaskDelay(1500);
    niMotorangle(90.0f);
    vTaskDelay(1500);
    Move_Forward_Position(0.3f);
    vTaskDelay(1500);
    finish_flag=1;
}
void Delivery_endB2_StateFunc(void *data){
    finish_flag=0;
    switch (delivery_count)
    {
    case 0:
        Move_Forward_Position(0.15f);
        vTaskDelay(1500);
        Yuntai_set_Angle(125);
        vTaskDelay(1500);
        Pump_Close();
        Solenoid_Open();
        Yuntai_set_Angle(65);
        vTaskDelay(1500);
        Move_Backward_Position(0.15f);
        vTaskDelay(1500);
        break;
    
    case 1:
        Move_Forward_Position(0.15f);
        vTaskDelay(1500);
        Yuntai_set_Angle(35);
        vTaskDelay(1500);
        Pump_Close();
        Solenoid_Open();
        Yuntai_set_Angle(65);
        vTaskDelay(1500);
        Move_Backward_Position(0.15f);
        vTaskDelay(1500);
        break;
    case 2:
        Pump_Close();
        Solenoid_Open();
        vTaskDelay(1500);
        break;
    }
    finish_flag=1;
}
void Back_beginB2_StateFunc(void *data)
{
    finish_flag=0;
    cross_flag = 0;
    cross_ready=0;
    if(delivery_count==2){
        Move_Backward_Position(0.3f);
        vTaskDelay(2200);
        niMotorangle(90.0f);
        vTaskDelay(2200);
        while (cross_flag!=3)
        {
        LineTracking();
     if(gray_right[0]==0)
    {
        cross_ready=1;
    }
    if (gray_right[3]==0&&cross_ready==1)
    {
        cross_flag++;
        cross_ready=0;
    }
        }
    Motorangle(90.0f);
    vTaskDelay(2200);
        while (gray_right[3]!= 0)
    {
        LineTracking();
        vTaskDelay(10);
    }
    Move_Forward_Position(0.1f);
    vTaskDelay(500);
            while (gray_right[3]!= 0)
    {
        LineTracking();
        vTaskDelay(10);
    }
    Stop();
    vTaskDelay(500);
    niMotorangle(90.0f);
    vTaskDelay(2200);
    blue_end_flag=1;
    finish_flag=1;

}
    else{
        Move_Backward_Position(0.3f);
        vTaskDelay(2200);
        niMotorangle(90.0f);
        vTaskDelay(2200);
        while (cross_flag!=4)
        {
        LineTracking();
     if(gray_right[0]==0)
    {
        cross_ready=1;
    }
    if (gray_right[3]==0&&cross_ready==1)
    {
        cross_flag++;
        cross_ready=0;
    }
        }
    Stop();
    vTaskDelay(1500);
    Move_Right_Position(0.9f);
    vTaskDelay(3500);
    }
    
    finish_flag=1;
}
void Back_endB2_StateFunc(void *data){
    finish_flag=0;
    switch (delivery_count)
    {
    case 0:
        Move_Forward_Position(0.15f);
        vTaskDelay(1500);
        Move_Left_Position(0.05f);
        vTaskDelay(500);
        Yuntai_set_Angle(85);
        vTaskDelay(3200);
        Solenoid_Close();
        Pump_Open();
        Sigancatch();
        vTaskDelay(2500);
        Siganmove(-100.0f);
        vTaskDelay(1500);
        Yuntai_set_Angle(65);
        vTaskDelay(1500);
        Move_Backward_Position(0.15f);
        vTaskDelay(1500);
        delivery_count++;
        break;
    case 1:
        Move_Forward_Position(0.15f);
        vTaskDelay(1500);
        Move_Right_Position(0.05f);
        vTaskDelay(500);
        Yuntai_set_Angle(45);
        vTaskDelay(3200);
        Solenoid_Close();
        Pump_Open();
        Sigancatch();
        vTaskDelay(2500);
        Siganmove(-100.0f);
        vTaskDelay(1500);
        Yuntai_set_Angle(65);
        Move_Left_Position(0.05f);
        vTaskDelay(500);
        Move_Backward_Position(0.15f);
        vTaskDelay(1500);
        delivery_count++;
        break;
    case 2:
        Pump_Close();
        Solenoid_Open();
        vTaskDelay(1500);
        break;
    }
    finish_flag=1;
}
void Delivery_beginB3_StateFunc(void *data){
    finish_flag=0;
    cross_ready=0;
    cross_flag = 0;
    Move_Left_Position(0.9f);
    vTaskDelay(3500);
    Motorangle(180.0f);
    vTaskDelay(2200);
    while (cross_flag<=2)
    {
    LineTracking();
    if((gray_front[6]== 0 && gray_front[7] == 0)||(gray_front[0]== 0 && gray_front[1] == 0))
    {
        cross_ready=1;
    }
    if (gray_right[3]==0&&cross_ready==1)
    {
        cross_flag++;
        cross_ready=0;
    }
    }
    while(cross_flag<=5)
    {
    LineTracking();
    if(gray_front[0]== 0 && gray_front[1] == 0)
    {
        Move_Forward_Position(0.1f);
        vTaskDelay(500);
        cross_flag++;
    }
     }
    Stop();
    vTaskDelay(1500);
    Move_Forward_Position(0.05f);
    vTaskDelay(500);
    niMotorangle(90.0f);
    vTaskDelay(2200);
    while (gray_front[0]!= 0 || gray_front[1] != 0)
    {
        LineTracking();
    }
    Stop();
    vTaskDelay(1500);
    Move_Left_Position(0.3f);
    vTaskDelay(2200);
    Move_Forward_Position(0.75f);
    vTaskDelay(4400);
    niMotorangle(90.0f);
    vTaskDelay(2200);
    finish_flag=1;
}
void Delivery_endB3_StateFunc(void *data){
    finish_flag=0;
    switch (delivery_count)
    {
    case 0:
        Move_Forward_Position(0.15f);
        vTaskDelay(1500);
        Yuntai_set_Angle(125);
        vTaskDelay(1500);
        Pump_Close();
        Solenoid_Open();
        Yuntai_set_Angle(65);
        vTaskDelay(1500);
        Move_Backward_Position(0.15f);
        vTaskDelay(1500);
        break;
    
    case 1:
        Move_Forward_Position(0.15f);
        vTaskDelay(1500);
        Yuntai_set_Angle(35);
        vTaskDelay(1500);
        Pump_Close();
        Solenoid_Open();
        Yuntai_set_Angle(65);
        vTaskDelay(1500);
        Move_Backward_Position(0.15f);
        vTaskDelay(1500);
        break;
    case 2:
        Pump_Close();
        Solenoid_Open();
        vTaskDelay(1500);
        break;
    }
    finish_flag=1;
}
void Back_beginB3_StateFunc(void *data){
    Solenoid_Close();
    finish_flag=0;
    cross_ready=0;
    cross_flag = 0;
    if(delivery_count==2){
        niMotorangle(90.0f);
        vTaskDelay(2200);
        Move_Forward_Position(0.8f);
        vTaskDelay(3200);
        Move_Left_Position(0.3f);
        vTaskDelay(2200);
        while (gray_right[3]!= 0)
        {
            LineTracking();
        }
        Stop();
        vTaskDelay(1500);
        Motorangle(90.0f);
        vTaskDelay(1500);
        while (cross_flag!=5)
        {
            LineTracking();
    if(gray_right[0]==0)
    {
        cross_ready=1;
    }
    if (gray_right[3]==0&&cross_ready==1)
    {
        cross_flag++;
        cross_ready=0;
    }
        }
        Stop();
        vTaskDelay(1500);
        Motorangle(90.0f);
        vTaskDelay(1500);
        Move_Forward_Position(0.1f);
        vTaskDelay(1000);
        while (gray_right[3]!= 0 )
        {
            LineTracking();
            vTaskDelay(10);
        }
        Move_Forward_Position(0.1f);
        while (gray_right[3]!= 0)
        {
            LineTracking();
            vTaskDelay(10);
        }
        Stop();
        vTaskDelay(1500);
        niMotorangle(90.0f);
        vTaskDelay(2200);
        blue_end_flag=1;
    }
    else{
        niMotorangle(90.0f);
        vTaskDelay(2200);
        Move_Forward_Position(0.8f);
        vTaskDelay(3200);
        Move_Left_Position(0.3f);
        vTaskDelay(2200);
        while (gray_right[3]!= 0)
        {
            LineTracking();
        }
        Stop();
        vTaskDelay(1500);
        Motorangle(90.0f);
        vTaskDelay(1500);
        while (cross_flag!=6)
        {
        LineTracking();
     if(gray_right[0]==0)
    {
        cross_ready=1;
    }
    if (gray_right[3]==0&&cross_ready==1)
    {
        cross_flag++;
        cross_ready=0;
    }
        }
    Stop();
    vTaskDelay(1500);
    }
    Move_Right_Position(0.9f);
    vTaskDelay(3500);
    finish_flag=1;   
}    
void Back_endB3_StateFunc(void *data){
    finish_flag=0;
    switch (delivery_count)
    {
    case 0:
        Move_Forward_Position(0.15f);
        vTaskDelay(1500);
        Move_Left_Position(0.05f);
        vTaskDelay(500);
        Yuntai_set_Angle(85);
        vTaskDelay(3200);
        Solenoid_Close();
        Pump_Open();
        Sigancatch();
        vTaskDelay(2500);
        Siganmove(-100.0f);
        vTaskDelay(1500);
        Yuntai_set_Angle(65);
        vTaskDelay(1500);
        Move_Backward_Position(0.15f);
        vTaskDelay(1500);
        delivery_count++;
        break;
    case 1:
        Move_Forward_Position(0.15f);
        vTaskDelay(1500);
        Move_Right_Position(0.05f);
        vTaskDelay(500);
        Yuntai_set_Angle(45);
        vTaskDelay(3200);
        Solenoid_Close();
        Pump_Open();
        Sigancatch();
        vTaskDelay(2500);
        Siganmove(-100.0f);
        vTaskDelay(1500);
        Yuntai_set_Angle(65);
        Move_Left_Position(0.05f);
        vTaskDelay(500);
        Move_Backward_Position(0.15f);
        vTaskDelay(1500);
        delivery_count++;
        break;
    case 2:
        Pump_Close();
        Solenoid_Open();
        vTaskDelay(1500);
        break;
    }
    finish_flag=1;
}
bool ConditionC3(void *data){
    return finish_flag==1 && red_end_flag==0;
}
bool ConditionC6(void *data){
    return red_end_flag==1;
}
void CarryC_StateFunc(void *data){
    finish_flag=0;
    delivery_count=0;
    Move_Forward_Position(0.25f);
    vTaskDelay(2200);
    Move_Left_Position(0.3f);
    vTaskDelay(2200);
    color_read=color_flag;
    Solenoid_Close();
    Pump_Open();
    vTaskDelay(1500);
    Sigancatch();
    vTaskDelay(2500);
    Siganmove(-100.0f);
    vTaskDelay(1500);
    Move_Right_Position(0.3f);
    vTaskDelay(2200);
    Move_Backward_Position(0.25f);
    vTaskDelay(2200);
    Motorangle(180.0f);
    vTaskDelay(2200);
    finish_flag=1;
}
void Delivery_beginC1_StateFunc(void *data){

    finish_flag=0;
    cross_ready=0;
    cross_flag = 0;
    Motorangle(90.0f);
    vTaskDelay(2200);
    Move_Forward_Position(0.1f);
    vTaskDelay(500);
    while (gray_right[3]!= 0)
    {
        LineTracking();
        vTaskDelay(10);
    }
    Stop();
    vTaskDelay(500);
    niMotorangle(90.0f);
    vTaskDelay(2200);
    Move_Forward_Position(0.1f);
    vTaskDelay(500);
    while (gray_right[3]!= 0)
    {
        LineTracking();
        vTaskDelay(10);
    }
    Stop();
    vTaskDelay(500);
    niMotorangle(90.0f);
    vTaskDelay(2200);
    finish_flag=1;
}
void Delivery_endC1_StateFunc(void *data){
    finish_flag=0;
    switch (delivery_count)
    {
    case 0:
        Move_Forward_Position(0.15f);
        vTaskDelay(1500);
        Yuntai_set_Angle(125);
        vTaskDelay(1500);
        Pump_Close();
        Solenoid_Open();
        Yuntai_set_Angle(65);
        vTaskDelay(1500);
        Move_Backward_Position(0.15f);
        vTaskDelay(1500);
        break;
    
    case 1:
        Move_Forward_Position(0.15f);
        vTaskDelay(1500);
        Yuntai_set_Angle(35);
        vTaskDelay(1500);
        Pump_Close();
        Solenoid_Open();
        Yuntai_set_Angle(65);
        vTaskDelay(1500);
        Move_Backward_Position(0.15f);
        vTaskDelay(1500);
        break;
    case 2:
        Pump_Close();
        Solenoid_Open();
        vTaskDelay(1500);
        break;
    }
    finish_flag=1;
}
void Back_beginC1_StateFunc(void *data){
    if(delivery_count==2){
        niMotorangle(90.0f);
        vTaskDelay(2200);
        Move_Forward_Position(0.6f);
        vTaskDelay(3000);
        niMotorangle(90.0f);
        vTaskDelay(2200);
        Move_Forward_Position(0.1f);
        vTaskDelay(500);
        while (gray_right[3]!= 0)
        {
            LineTracking();
            vTaskDelay(10);
        }
        Stop();
        vTaskDelay(500);
        niMotorangle(90.0f);
        vTaskDelay(2200);
        Move_Forward_Position(0.8f);
        vTaskDelay(3000);
        blue_end_flag=1;
    }
    else{
    finish_flag=0;
    cross_ready=0;
    cross_flag = 0;
    niMotorangle(90.0f);
    vTaskDelay(2200);
    Move_Forward_Position(0.6f);
    vTaskDelay(3000);
    Motorangle(90.0f);
    vTaskDelay(2200);
    Move_Forward_Position(0.1f);
    vTaskDelay(500);
    while(gray_right[3]!= 0){
        LineTracking();
        vTaskDelay(10);
    }
    Stop();
    vTaskDelay(500);
    niMotorangle(90.0f);
    vTaskDelay(2200);
}
    finish_flag=1;
}
void Back_endC1_StateFunc(void *data){
    finish_flag=0;
    switch (delivery_count)
    {
    case 0:
        Move_Left_Position(0.35f);
        vTaskDelay(2200);
        Move_Forward_Position(0.45f);
        vTaskDelay(2200);
        Yuntai_set_Angle(85);
        vTaskDelay(1500);
        Solenoid_Close();
        Pump_Open();
        Sigancatch();
        vTaskDelay(2200);
        Siganmove(-100.0f);
        vTaskDelay(1500);
        Yuntai_set_Angle(65);
        vTaskDelay(1500);
        Move_Backward_Position(0.45f);
        vTaskDelay(2200);
        Move_Right_Position(0.35f);
        vTaskDelay(2200);
        Motorangle(180.0f);
        vTaskDelay(2200);
        delivery_count++;
        break;
    case 1:
        Move_Left_Position(0.25f);
        vTaskDelay(2200);
        Move_Forward_Position(0.45f);
        vTaskDelay(2200);
        Yuntai_set_Angle(45);
        vTaskDelay(1500);
        Solenoid_Close();
        Pump_Open();
        Sigancatch();
        vTaskDelay(2200);
        Siganmove(-100.0f);
        vTaskDelay(1500);
        Yuntai_set_Angle(65);
        vTaskDelay(1500);
        Move_Backward_Position(0.45f);
        vTaskDelay(2200);
        Move_Right_Position(0.25f);
        vTaskDelay(2200);
        Motorangle(180.0f);
        vTaskDelay(2200);
        delivery_count++;
        break;
    case 2:
        Pump_Close();
        Solenoid_Open();
        vTaskDelay(1500);
        break;
    }
    finish_flag=1;
}
void Delivery_beginC2_StateFunc(void *data){
    finish_flag=0;
    cross_ready=0;
    cross_flag = 0;
    Move_Forward_Position(0.1f);
    vTaskDelay(500);
    while (gray_right[3]!= 0)
    {
        LineTracking();
        vTaskDelay(10);
    }
    Stop();
    vTaskDelay(500);
    Move_Right_Position(0.3f);
    vTaskDelay(2200);
    Move_Forward_Position(0.3f);
    vTaskDelay(2200);
    Motorangle(90.0f);
    vTaskDelay(2200);
    Move_Forward_Position(0.1f);
    vTaskDelay(500);
    while (gray_right[3] != 0)
    {
        LineTracking();
        vTaskDelay(10);
    }
    Stop();
    vTaskDelay(500);
    finish_flag=1;
}
void Delivery_endC2_StateFunc(void *data){
    finish_flag=0;
    switch (delivery_count)
    {
    case 0:
        Move_Forward_Position(0.15f);
        vTaskDelay(1500);
        Yuntai_set_Angle(125);
        vTaskDelay(1500);
        Pump_Close();
        Solenoid_Open();
        Yuntai_set_Angle(65);
        vTaskDelay(1500);
        Move_Backward_Position(0.15f);
        vTaskDelay(1500);
        break;
    
    case 1:
        Move_Forward_Position(0.15f);
        vTaskDelay(1500);
        Yuntai_set_Angle(35);
        vTaskDelay(1500);
        Pump_Close();    
        Solenoid_Open();
        Yuntai_set_Angle(65);
        vTaskDelay(1500);
        Move_Backward_Position(0.15f);
        vTaskDelay(1500);
        break;
    case 2:
        Pump_Close();
        Solenoid_Open();
        vTaskDelay(1500);
        break;
    }
    finish_flag=1;
}
void Back_beginC2_StateFunc(void *data){
    finish_flag=0;
        Motorangle(180.0f);
        vTaskDelay(2200);
        while (gray_front[0] != 0)
        {
            LineTracking();
            vTaskDelay(10);
        }
        Stop();
        vTaskDelay(500);
        Move_Left_Position(0.3f);
        vTaskDelay(2200);
        Move_Forward_Position(0.37f);
        vTaskDelay(2200);
        niMotorangle(90.0f);
        vTaskDelay(2200);
        Move_Forward_Position(0.1f);
        vTaskDelay(500);
        while (gray_right[3] != 0)
        {
            LineTracking();
            vTaskDelay(10);
        }
        Stop();
        vTaskDelay(500);
        if(delivery_count==2){
            niMotorangle(90.0f);
            vTaskDelay(2200);
            Move_Forward_Position(0.1f);
            vTaskDelay(500);
            while (gray_right[3] != 0)
            {
                LineTracking();
                vTaskDelay(10);
            }
            Move_Forward_Position(0.1f);
            vTaskDelay(500);
            while (gray_right[3] != 0)
            {
                LineTracking();
                vTaskDelay(10);
            }
            Stop();
            vTaskDelay(500);
            niMotorangle(90.0f);
            vTaskDelay(2200);
            Move_Forward_Position(0.8f);
            vTaskDelay(3000);
            red_end_flag=1;
        }
    finish_flag=1;
}
void Back_endC2_StateFunc(void *data){
    finish_flag=0;
    switch (delivery_count)
    {
    case 0:
        Move_Left_Position(0.35f);
        vTaskDelay(2200);
        Move_Forward_Position(0.45f);
        vTaskDelay(2200);
        Yuntai_set_Angle(85);
        vTaskDelay(1500);
        Solenoid_Close();
        Pump_Open();
        Sigancatch();
        vTaskDelay(2200);
        Siganmove(-100.0f);
        vTaskDelay(1500);
        Yuntai_set_Angle(65);
        vTaskDelay(1500);
        Move_Backward_Position(0.45f);
        vTaskDelay(2200);
        Move_Right_Position(0.35f);
        vTaskDelay(2200);
        Motorangle(180.0f);
        vTaskDelay(2200);
        delivery_count++;
        break;
    case 1:
        Move_Left_Position(0.25f);
        vTaskDelay(2200);
        Move_Forward_Position(0.45f);
        vTaskDelay(2200);
        Yuntai_set_Angle(45);
        vTaskDelay(1500);
        Solenoid_Close();
        Pump_Open();
        Sigancatch();
        vTaskDelay(2200);
        Siganmove(-100.0f);
        vTaskDelay(1500);
        Yuntai_set_Angle(65);
        vTaskDelay(1500);
        Move_Backward_Position(0.45f);
        vTaskDelay(2200);
        Move_Right_Position(0.25f);
        vTaskDelay(2200);
        Motorangle(180.0f);
        vTaskDelay(2200);
        delivery_count++;
        break;
    case 2:
        Pump_Close();
        Solenoid_Open();
        vTaskDelay(1500);
        break;
    }
    finish_flag=1;
}
void Delivery_beginC3_StateFunc(void *data){
    
    finish_flag=0;
    cross_ready=0;
    cross_flag = 0;
    Move_Forward_Position(0.1f);
    vTaskDelay(500);
    while (gray_right[3] != 0)
    {
        LineTracking();
        vTaskDelay(10);
    }
    Stop();
    vTaskDelay(500);
    Move_Forward_Position(0.1f);
    vTaskDelay(500);
    while (gray_right[3] != 0)
    {
        LineTracking();
        vTaskDelay(10);
    }
    Stop();
    vTaskDelay(500);
    Move_Right_Position(0.6f);
    vTaskDelay(3000);
    while (gray_front[0] != 0)
    {
        LineTracking();
        vTaskDelay(10);
    }
    Stop();
    vTaskDelay(500);
    Move_Forward_Position(0.1f);
    vTaskDelay(500);
    Stop();
    vTaskDelay(500);
    finish_flag=1;
}
void Delivery_endC3_StateFunc(void *data){
    finish_flag=0;
    switch (delivery_count)
    {
    case 0:
        Move_Forward_Position(0.15f);
        vTaskDelay(1500);
        Yuntai_set_Angle(125);
        vTaskDelay(1500);
        Pump_Close();
        Solenoid_Open();
        Yuntai_set_Angle(65);
        vTaskDelay(1500);
        Move_Backward_Position(0.15f);
        vTaskDelay(1500);
        break;
    case 1:
        Move_Forward_Position(0.15f);
        vTaskDelay(1500);
        Yuntai_set_Angle(35);
        vTaskDelay(1500);
        Pump_Close();
        Solenoid_Open();
        Yuntai_set_Angle(65);
        vTaskDelay(1500);
        Move_Backward_Position(0.15f);
        vTaskDelay(1500);
        break;
    case 2:
        Pump_Close();
        Solenoid_Open();
        vTaskDelay(1500);
        red_end_flag=1;
        break;
    }
    finish_flag=1;
}
void Back_beginC3_StateFunc(void *data){
    finish_flag=0;
    cross_ready=0;
    cross_flag = 0;
    Motorangle(180.0f);
    vTaskDelay(2200);
    Move_Forward_Position(0.1f);
    vTaskDelay(500);
    while (gray_right[3] != 0)
    {
        LineTracking();
        vTaskDelay(10);
    }
    Move_Forward_Position(0.1f);
    vTaskDelay(500);
    while (gray_right[3] != 0)
    {
        LineTracking();
        vTaskDelay(10);
    }
    Motorangle(90.0f);
    vTaskDelay(2200);
    while (gray_front[0] != 0)
    {
        LineTracking();
        vTaskDelay(10);
    }
    Stop();
    vTaskDelay(500);
    Move_Left_Position(0.3f);
    vTaskDelay(2200);
    Move_Forward_Position(0.4f);
    vTaskDelay(2200);
    niMotorangle(90.0f);
    vTaskDelay(2200);
    Move_Forward_Position(0.1f);
    vTaskDelay(500);
    while (gray_right[3] != 0)
    {
        LineTracking();
        vTaskDelay(10);
    }
    Stop();
    vTaskDelay(500);
    if(delivery_count==2){
        niMotorangle(90.0f);
        vTaskDelay(2200);
        Move_Forward_Position(0.1f);
        vTaskDelay(500);
        while (gray_right[3] != 0)
        {
            LineTracking();
            vTaskDelay(10);
        }
        Move_Forward_Position(0.1f);
        vTaskDelay(500);
        while (gray_right[3] != 0)
        {
            LineTracking();
            vTaskDelay(10);
        }
        Stop();
        vTaskDelay(500);
        niMotorangle(90.0f);
        vTaskDelay(2200);
        Move_Forward_Position(0.8f);
        vTaskDelay(3000);
        red_end_flag=1;
    }
    finish_flag=1;
}
void Back_endC3_StateFunc(void *data){
    finish_flag=0;
    switch (delivery_count)
    {
    case 0:
        Move_Left_Position(0.35f);
        vTaskDelay(2200);
        Move_Forward_Position(0.45f);
        vTaskDelay(2200);
        Yuntai_set_Angle(85);
        vTaskDelay(1500);
        Solenoid_Close();
        Pump_Open();
        Sigancatch();
        vTaskDelay(2200);
        Siganmove(-100.0f);
        vTaskDelay(1500);
        Yuntai_set_Angle(65);
        vTaskDelay(1500);
        Move_Backward_Position(0.45f);
        vTaskDelay(2200);
        Move_Right_Position(0.35f);
        vTaskDelay(2200);
        Motorangle(180.0f);
        vTaskDelay(2200);
        delivery_count++;
        break;
    case 1:
        Move_Left_Position(0.25f);
        vTaskDelay(2200);
        Move_Forward_Position(0.45f);
        vTaskDelay(2200);
        Yuntai_set_Angle(45);
        vTaskDelay(1500);
        Solenoid_Close();
        Pump_Open();
        Sigancatch();
        vTaskDelay(2200);
        Siganmove(-100.0f);
        vTaskDelay(1500);
        Yuntai_set_Angle(65);
        vTaskDelay(1500);
        Move_Backward_Position(0.45f);
        vTaskDelay(2200);
        Move_Right_Position(0.25f);
        vTaskDelay(2200);
        Motorangle(180.0f);
        vTaskDelay(2200);
        delivery_count++;
        break;
    case 2:
        Pump_Close();
        Solenoid_Open();
        vTaskDelay(1500);
        break;
    }
    finish_flag=1;
}
    


   
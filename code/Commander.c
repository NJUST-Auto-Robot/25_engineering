#include "Commander.h"

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

extern bool ConditionA1(void *data);
extern bool ConditionA2(void *data);
extern bool ConditionA3(void *data);
extern bool ConditionA4(void *data);
extern bool ConditionA5(void *data);

int color_read=0;
int delivery_count=0;
int yellow_end_flag=0;
int finish_flag=0;

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

    fsm_Add_Transition(Begin, CarryA, ConditionA1);
    fsm_Add_Transition(CarryA, Delivery_beginA1, ConditionA2);
    fsm_Add_Transition(Delivery_beginA1, Delivery_endA1, ConditionA1);
    fsm_Add_Transition(Delivery_endA1, Back_beginA1, ConditionA1);
    fsm_Add_Transition(Back_beginA1, Back_endA1, ConditionA1);
    fsm_Add_Transition(Back_endA1, Delivery_beginA1, ConditionA3);
    fsm_Add_Transition(CarryA, Delivery_beginA2, ConditionA4);
    fsm_Add_Transition(Delivery_beginA2, Delivery_endA2, ConditionA1);
    fsm_Add_Transition(Delivery_endA2, Back_beginA2, ConditionA1);
    fsm_Add_Transition(Back_beginA2, Back_endA2, ConditionA1);
    fsm_Add_Transition(CarryA, Delivery_beginA3, ConditionA5);
    fsm_Add_Transition(Delivery_beginA3, Delivery_endA3, ConditionA1);
    fsm_Add_Transition(Delivery_endA3, Back_beginA3, ConditionA1);
    fsm_Add_Transition(Back_beginA3, Back_endA3, ConditionA1);


    fsm_Set_Initial_State(FsmYellow, Begin); // 设置初始状态
}

void motion_StateManager_Execute()
{
    fsm_Execute(FsmYellow, NULL); // 执行状态机
}

void Begin_StateFunc(void *data)
{
    int cross_ready=0;
    int cross_flag = 0;
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
    
    // last_state = current_state;
    }
    Stop();
    finish_flag=1;
    HAL_Delay(1500);
}
bool ConditionA1(void *data)
{
    return finish_flag==1;
}
void CarryA_StateFunc(void *data)
{
    finish_flag=0;
    Move_Right_Position(0.3f);
    HAL_Delay(1500);
    Move_Backward_Position(0.1f);
    HAL_Delay(1000);
    color_read=color_flag;
    Sigancatch();
    HAL_Delay(1000);
    Solenoid_Open();
    Pump_Open();
    Siganmove(-100.0f);
    HAL_Delay(1000);
    Move_Left_Position(0.3f);
    HAL_Delay(1500);
    Motorangle(180.0f);
    HAL_Delay(1500);
    finish_flag=1;
}
bool ConditionA2(void *data)
{
    return finish_flag==1&&color_read==YELLOWFLAG;
}
void Delivery_beginA1_StateFunc(void *data)
{
    finish_flag=0;
    while (gray_right[3]!= 0)
    {
        LineTracking();
    }
    Stop();
    Motorangle(-90.0f);
    HAL_Delay(1000);
    Move_Forward_Position(0.1f);
    HAL_Delay(1000);
    while (gray_right[4]!= 0 || gray_right[5] != 0)
    {
        LineTracking();
    }
    Stop();
    Move_Right_Position(0.6f);
}
void Delivery_endA1_StateFunc(void *data)
{
    switch (delivery_count)
    {
    case 0:
        Move_Forward_Position(0.15f);
        Yuntai_set_Angle(125);
        Pump_Close();
        Solenoid_Close();
        Yuntai_set_Angle(65);
        Move_Backward_Position(0.15f);
        break;
    
    case 1:
        Move_Forward_Position(0.15f);
        Yuntai_set_Angle(-5);
        Pump_Close();
        Solenoid_Close();
        Yuntai_set_Angle(65);
        Move_Backward_Position(0.15f);
        break;
    case 2:
        Pump_Close();
        Solenoid_Close();
        break;
    }
}
void Back_beginA1_StateFunc(void *data)
{
    if(delivery_count==2){
        Motorangle(-90.0f);
        Move_Forward_Position(0.6f);
    }
    else{
        Move_Left_Position(0.6f);
        Motorangle(180.0f);
        Move_Forward_Position(0.1f);
        while (gray_right[4]!= 0 || gray_right[5] != 0)
        {
            LineTracking();
        }
        Stop();
        Motorangle(90.0f);
        while (gray_right[4]!= 0 || gray_right[5] != 0)
        {
            LineTracking();
        }
        Stop();
    }       
    
}
void Back_endA1_StateFunc(void *data)
{
    switch (delivery_count)
    {
    case 0:
        Move_Right_Position(0.3f);
        Move_Forward_Position(0.15f);
        Yuntai_set_Angle(95);
        Sigancatch();
        Solenoid_Open();
        Pump_Open();
        Siganmove(-100.0f);
        Yuntai_set_Angle(65);
        Move_Left_Position(0.3f);
        Motorangle(180.0f);
        delivery_count++;
        break;
    case 1:
        Move_Right_Position(0.3f);
        Move_Forward_Position(0.15f);
        Yuntai_set_Angle(35);
        Sigancatch();
        Solenoid_Open();
        Pump_Open();
        Siganmove(-100.0f);
        Yuntai_set_Angle(65);
        Move_Left_Position(0.3f);
        Motorangle(180.0f);
        delivery_count++;
        break;
    case 2:
        delivery_count=0;
        yellow_end_flag=1;
        break;

    }
}
bool ConditionA3(void *data)
{
    return gray_right[4]== 0 && gray_right[5] == 0 && yellow_end_flag==0;
}
bool ConditionA4(void *data)
{
    return gray_right[4]== 0 && gray_right[5] == 0 && color_read==BLUEFLAG;
}
void Delivery_beginA2_StateFunc(void *data)
{
    int cross_flag = 0;
    while (cross_flag!=2)
    {
    LineTracking();
    if(gray_right[4]== 0 && gray_right[5] == 0)
    {
        if(gray_right[4]!= 0 || gray_right[5] != 0)
        cross_flag++;
    }
    }
    Stop();
    Motorangle(-90.0f);
    while (cross_flag!=4)
    {
    LineTracking();
    if(gray_right[4]== 0 && gray_right[5] == 0)
    {
        if(gray_right[4]!= 0 || gray_right[5] != 0)
        cross_flag++;
    }
    }
    Stop();
    Motorangle(90.0f);
    while (gray_right[4]!= 0 || gray_right[5] != 0)
        {
            LineTracking();
        }
    Stop();
    Move_Right_Position(0.3f);
    while (gray_right[4]!= 0 || gray_right[5] != 0)
        {
            LineTracking();
        }
    Stop();
    Motorangle(-90.0f);
}
void Delivery_endA2_StateFunc(void *data)
{
    switch (delivery_count)
    {
    case 0:
        Move_Forward_Position(0.15f);
        Yuntai_set_Angle(125);
        Pump_Close();
        Solenoid_Close();
        Yuntai_set_Angle(65);
        Move_Backward_Position(0.15f);
        break;
    
    case 1:
        Move_Forward_Position(0.15f);
        Yuntai_set_Angle(-5);
        Pump_Close();
        Solenoid_Close();
        Yuntai_set_Angle(65);
        Move_Backward_Position(0.15f);
        break;
    case 2:
        Pump_Close();
        Solenoid_Close();
        break;
    }
}
void Back_beginA2_StateFunc(void *data)
{
    int cross_flag = 0;
    if(delivery_count==2){
    Motorangle(-90.0f);
    Move_Forward_Position(0.6f);
    Move_Right_Position(0.3f);
    while (gray_right[4]!= 0 || gray_right[5] != 0)
    {
        LineTracking();
    }
    Stop();
    Move_Right_Position(0.3f);
    while (cross_flag!=4)
    {
    LineTracking();
    if(gray_right[4]== 0 && gray_right[5] == 0)
    {
        if(gray_right[4]!= 0 || gray_right[5] != 0)
        cross_flag++;
    }
    Stop();
    }
}
    else{
    Motorangle(-90.0f);
    Move_Forward_Position(0.6f);
    Move_Right_Position(0.3f);
    while (gray_right[4]!= 0 || gray_right[5] != 0)
    {
        LineTracking();
    }
    Stop();
    Motorangle(-90.0f);
    while (gray_right[4]!= 0 || gray_right[5] != 0)
    {
        LineTracking();
    }
    Stop();
    Motorangle(90.0f);
    while (cross_flag!=3)
    {
    LineTracking();
    if(gray_right[4]== 0 && gray_right[5] == 0)
    {
        if(gray_right[4]!= 0 || gray_right[5] != 0)
        cross_flag++;
    }
    }
    Stop();
}
}
void Back_endA2_StateFunc(void *data)
{
    switch (delivery_count)
    {
    case 0:
        Move_Right_Position(0.3f);
        Move_Forward_Position(0.15f);
        Yuntai_set_Angle(95);
        Sigancatch();
        Solenoid_Open();
        Pump_Open();
        Siganmove(-100.0f);
        Yuntai_set_Angle(65);
        Move_Left_Position(0.3f);
        Motorangle(180.0f);
        delivery_count++;
        break;
    case 1:
        Move_Right_Position(0.3f);
        Move_Forward_Position(0.15f);
        Yuntai_set_Angle(35);
        Sigancatch();
        Solenoid_Open();
        Pump_Open();
        Siganmove(-100.0f);
        Yuntai_set_Angle(65);
        Move_Left_Position(0.3f);
        Motorangle(180.0f);
        delivery_count++;
        break;
    case 2:
        delivery_count=0;
        yellow_end_flag=1;
        break;

    }
}
bool ConditionA5(void *data)
{
    return gray_right[4]== 0 && gray_right[5] == 0 && color_read==REDFLAG;
}
void Delivery_beginA3_StateFunc(void *data)
{
    int cross_flag = 0;
    while (cross_flag!=3)
    {
    LineTracking();
    if(gray_right[4]== 0 && gray_right[5] == 0)
    {
        if(gray_right[4]!= 0 || gray_right[5] != 0)
        cross_flag++;
    }
    }
    while(cross_flag!=6)
    {
    LineTracking();
    if(gray_front[6]== 0 && gray_front[7] == 0)
    {
        if(gray_front[6]!= 0 || gray_front[7] != 0)
        cross_flag++;
    }
    }
    Stop();
    Motorangle(-90.0f);
    while (gray_front[6]!= 0 || gray_front[7] != 0)
    {
        LineTracking();
    }
    Stop();
    Move_Left_Position(0.3f);
    Move_Forward_Position(0.6f);
    Motorangle(-90.0f);
}
void Delivery_endA3_StateFunc(void *data)
{
    switch (delivery_count)
    {
    case 0:
        Move_Forward_Position(0.15f);
        Yuntai_set_Angle(125);
        Pump_Close();
        Solenoid_Close();
        Yuntai_set_Angle(65);
        Move_Backward_Position(0.15f);
        break;
    
    case 1:
        Move_Forward_Position(0.15f);
        Yuntai_set_Angle(35);
        Pump_Close();
        Solenoid_Close();
        Yuntai_set_Angle(65);
        Move_Backward_Position(0.15f);
        break;
    case 2:
        Pump_Close();
        Solenoid_Close();
        break;
    }
}
void Back_beginA3_StateFunc(void *data)
{
    int cross_flag = 0;
    if(delivery_count==2){
        Motorangle(-90.0f);
        Move_Forward_Position(0.6f);
        Move_Left_Position(0.3f);
        while (gray_right[4]!= 0 || gray_right[5] != 0)
        {
            LineTracking();
        }
        Stop();
        Motorangle(90.0f);
        int cross_flag = 0;
        while (cross_flag!=6)
        {
            LineTracking();
            if(gray_right[4]== 0 && gray_right[5] == 0)
            {
                if(gray_right[4]!= 0 || gray_right[5] != 0)
                cross_flag++;
            }
        }
        Stop();
        Motorangle(90.0f);
        Move_Forward_Position(0.1f);
        while (gray_right[4]!= 0 || gray_right[5] != 0)
        {
            LineTracking();
        }
        Stop();
        Motorangle(-90.0f);
        Move_Forward_Position(0.1f);
        while (gray_right[4]!= 0 || gray_right[5] != 0)
        {
            LineTracking();
        }
        Stop();
    }
    else{
        Motorangle(-90.0f);
        Move_Forward_Position(0.6f);
        Move_Left_Position(0.3f);
        while (gray_right[4]!= 0 || gray_right[5] != 0)
        {
            LineTracking();
        }
        Stop();
        Motorangle(90.0f);
        while (cross_flag!=7)
        {
        LineTracking();
        if(gray_right[4]== 0 && gray_right[5] == 0)
        {
        if(gray_right[4]!= 0 || gray_right[5] != 0)
            cross_flag++;
        }
        }
    Stop();
    }       
}
void Back_endA3_StateFunc(void *data)
{
    switch (delivery_count)
    {
    case 0:
        Move_Right_Position(0.3f);
        Move_Forward_Position(0.15f);
        Yuntai_set_Angle(95);
        Sigancatch();
        Solenoid_Open();
        Pump_Open();
        Siganmove(-100.0f);
        Yuntai_set_Angle(65);
        Move_Left_Position(0.3f);
        Motorangle(180.0f);
        delivery_count++;
        break;
    case 1:
        Move_Right_Position(0.3f);
        Move_Forward_Position(0.15f);
        Yuntai_set_Angle(35);
        Sigancatch();
        Solenoid_Open();
        Pump_Open();
        Siganmove(-100.0f);
        Yuntai_set_Angle(65);
        Move_Left_Position(0.3f);
        Motorangle(180.0f);
        delivery_count++;
        break;
    case 2:
        delivery_count=0;
        yellow_end_flag=1;
        break;

    }
}   
#ifndef FSM_H
#define FSM_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// 状态转移的条件函数类型
typedef bool (*FSM_StateTransitionCondition)(void *data);

// 状态节点类型
typedef struct FSM_StateNode
{
    int id;                         // 状态 ID
    const char *name;               // 状态名称
    void (*state_func)(void *data); // 状态的执行函数
    struct FSM_StateTransition *transitions;   // 状态的转移结构体
    int transition_count;           // 转移条件的数量
} FSM_StateNode;

// 状态转移结构体
typedef struct FSM_StateTransition
{
    FSM_StateNode *target_state;            // 目标状态
    FSM_StateTransitionCondition condition; // 转移条件
} FSM_StateTransition;

// 状态机结构体
typedef struct FSM
{
    FSM_StateNode *current_state; // 当前状态
    FSM_StateNode **states;       // 状态集合
    int state_count;          // 状态数量
} FSM;


FSM *fsm_Create();
FSM_StateNode *fsm_Create_And_Add_State(FSM *fsm, int id, const char *name, void (*state_func)(void *));
void fsm_Add_State(FSM *fsm, FSM_StateNode *state);
void fsm_Add_Transition(FSM_StateNode *from_state, FSM_StateNode *to_state, FSM_StateTransitionCondition condition);
void fsm_Set_Initial_State(FSM *fsm, FSM_StateNode *initial_state);
void fsm_Execute(FSM *fsm, void *data);

#endif // FSM_H

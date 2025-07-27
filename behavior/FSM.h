#ifndef FSM_H
#define FSM_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// ״̬ת�Ƶ�������������
typedef bool (*FSM_StateTransitionCondition)(void *data);

// ״̬�ڵ�����
typedef struct FSM_StateNode
{
    int id;                         // ״̬ ID
    const char *name;               // ״̬����
    void (*state_func)(void *data); // ״̬��ִ�к���
    struct FSM_StateTransition *transitions;   // ״̬��ת�ƽṹ��
    int transition_count;           // ת������������
} FSM_StateNode;

// ״̬ת�ƽṹ��
typedef struct FSM_StateTransition
{
    FSM_StateNode *target_state;            // Ŀ��״̬
    FSM_StateTransitionCondition condition; // ת������
} FSM_StateTransition;

// ״̬���ṹ��
typedef struct FSM
{
    FSM_StateNode *current_state; // ��ǰ״̬
    FSM_StateNode **states;       // ״̬����
    int state_count;          // ״̬����
} FSM;


FSM *fsm_Create();
FSM_StateNode *fsm_Create_And_Add_State(FSM *fsm, int id, const char *name, void (*state_func)(void *));
void fsm_Add_State(FSM *fsm, FSM_StateNode *state);
void fsm_Add_Transition(FSM_StateNode *from_state, FSM_StateNode *to_state, FSM_StateTransitionCondition condition);
void fsm_Set_Initial_State(FSM *fsm, FSM_StateNode *initial_state);
void fsm_Execute(FSM *fsm, void *data);

#endif // FSM_H

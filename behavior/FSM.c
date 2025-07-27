#include "fsm.h"

// 创建一个新的状态机
FSM *fsm_Create()
{
    FSM *fsm = (FSM *)malloc(sizeof(FSM));
    fsm->current_state = NULL;
    fsm->states = NULL;
    fsm->state_count = 0;
    return fsm;
}

// 向状态机中添加一个状态
void fsm_Add_State(FSM *fsm, FSM_StateNode *state)
{
    fsm->state_count++;
    fsm->states = (FSM_StateNode **)realloc(fsm->states, sizeof(FSM_StateNode *) * fsm->state_count);
    fsm->states[fsm->state_count - 1] = state;
}

// 创建并注册一个状态节点
FSM_StateNode *fsm_Create_And_Add_State(FSM *fsm, int id, const char *name, void (*state_func)(void *))
{
    FSM_StateNode *state = (FSM_StateNode *)malloc(sizeof(FSM_StateNode));
    state->id = id;
    state->name = name;
    state->state_func = state_func;
    state->transitions = NULL;
    state->transition_count = 0;

    fsm_Add_State(fsm, state);
    return state;
}


// 向状态节点添加转移条件
void fsm_Add_Transition(FSM_StateNode *from_state, FSM_StateNode *to_state, FSM_StateTransitionCondition condition)
{
    from_state->transition_count++;
    from_state->transitions = (FSM_StateTransition *)realloc(from_state->transitions, sizeof(FSM_StateTransition) * from_state->transition_count);

    from_state->transitions[from_state->transition_count - 1].target_state = to_state;
    from_state->transitions[from_state->transition_count - 1].condition = condition;
}

// 设置状态机的初始状态
void fsm_Set_Initial_State(FSM *fsm, FSM_StateNode *initial_state)
{
    fsm->current_state = initial_state;
}

// 执行状态机，检查当前状态的转移条件
void fsm_Execute(FSM *fsm, void *data)
{
    if (fsm->current_state != NULL)
    {
        // 执行当前状态的函数
        fsm->current_state->state_func(data);

        // 检查状态转移条件
        for (int i = 0; i < fsm->current_state->transition_count; i++)
        {
            FSM_StateTransition *transition = &fsm->current_state->transitions[i];
            if (transition->condition(data))
            {
                fsm->current_state = transition->target_state;
                break; // 一次只做一个转移
            }
        }
    }
}

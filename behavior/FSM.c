#include "fsm.h"

// ����һ���µ�״̬��
FSM *fsm_Create()
{
    FSM *fsm = (FSM *)malloc(sizeof(FSM));
    fsm->current_state = NULL;
    fsm->states = NULL;
    fsm->state_count = 0;
    return fsm;
}

// ��״̬�������һ��״̬
void fsm_Add_State(FSM *fsm, FSM_StateNode *state)
{
    fsm->state_count++;
    fsm->states = (FSM_StateNode **)realloc(fsm->states, sizeof(FSM_StateNode *) * fsm->state_count);
    fsm->states[fsm->state_count - 1] = state;
}

// ������ע��һ��״̬�ڵ�
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


// ��״̬�ڵ����ת������
void fsm_Add_Transition(FSM_StateNode *from_state, FSM_StateNode *to_state, FSM_StateTransitionCondition condition)
{
    from_state->transition_count++;
    from_state->transitions = (FSM_StateTransition *)realloc(from_state->transitions, sizeof(FSM_StateTransition) * from_state->transition_count);

    from_state->transitions[from_state->transition_count - 1].target_state = to_state;
    from_state->transitions[from_state->transition_count - 1].condition = condition;
}

// ����״̬���ĳ�ʼ״̬
void fsm_Set_Initial_State(FSM *fsm, FSM_StateNode *initial_state)
{
    fsm->current_state = initial_state;
}

// ִ��״̬������鵱ǰ״̬��ת������
void fsm_Execute(FSM *fsm, void *data)
{
    if (fsm->current_state != NULL)
    {
        // ִ�е�ǰ״̬�ĺ���
        fsm->current_state->state_func(data);

        // ���״̬ת������
        for (int i = 0; i < fsm->current_state->transition_count; i++)
        {
            FSM_StateTransition *transition = &fsm->current_state->transitions[i];
            if (transition->condition(data))
            {
                fsm->current_state = transition->target_state;
                break; // һ��ֻ��һ��ת��
            }
        }
    }
}

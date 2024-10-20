#pragma once
#include "FSMState.h"

class InteractionState :
    public FSMState
{

public:
    InteractionState(StateMachine* onwer);
    ~InteractionState();

public:
    virtual void Enter();
    virtual void Update(float deltaTime);
    virtual void Exit();
};


#pragma once
#include "FSMState.h"

class BlackCatMoveState :
    public FSMState
{
public:
    BlackCatMoveState(StateMachine* owner);
    ~BlackCatMoveState();

public:
    virtual void Enter();
    virtual void Update(float deltaTime);
    virtual void Exit();
};


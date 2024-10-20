#pragma once
#include "FSMState.h"

class NPC1IdleState :
    public FSMState
{
public:
    NPC1IdleState(StateMachine* owner);
    ~NPC1IdleState();

public:
    virtual void Enter();
    virtual void Update(float deltaTime);
    virtual void Exit();

};


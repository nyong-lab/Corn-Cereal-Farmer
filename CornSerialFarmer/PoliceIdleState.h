#pragma once
#include "FSMState.h"

class PoliceIdleState :
    public FSMState
{
public:
    PoliceIdleState(StateMachine* owner);
    ~PoliceIdleState();

public:
	virtual void Enter();
	virtual void Update(float deltaTime);
	virtual void Exit();
};


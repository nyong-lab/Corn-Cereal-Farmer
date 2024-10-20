#pragma once
#include "FSMState.h"

class FarmNoWaterState :
    public FSMState
{
public:
    FarmNoWaterState(StateMachine* owner);
    ~FarmNoWaterState();

public:
	virtual void Enter();
	virtual void Update(float deltaTime);
	virtual void Exit();
};


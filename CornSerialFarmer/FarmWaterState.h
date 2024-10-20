#pragma once
#include "FSMState.h"

class FarmWaterState :
    public FSMState
{
public:
    FarmWaterState(StateMachine* owner);
    ~FarmWaterState();

public:
	virtual void Enter();
	virtual void Update(float deltaTime);
	virtual void Exit();
};


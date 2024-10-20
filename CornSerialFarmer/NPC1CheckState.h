#pragma once
#include "FSMState.h"

class NPC1CheckState :
    public FSMState
{
public:
    NPC1CheckState(StateMachine* owner);
    ~NPC1CheckState();

public:
	virtual void Enter();
	virtual void Update(float deltaTime);
	virtual void Exit();
};


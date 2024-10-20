#pragma once
#include "FSMState.h"

class NPC2IdleState :
    public FSMState
{

public:
    NPC2IdleState(StateMachine* owner);
    ~NPC2IdleState();

public:
	virtual void Enter();
	virtual void Update(float deltaTime);
	virtual void Exit();

};


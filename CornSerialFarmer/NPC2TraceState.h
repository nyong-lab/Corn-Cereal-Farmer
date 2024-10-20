#pragma once
#include "FSMState.h"

class NPC2TraceState :
    public FSMState
{
public:
    NPC2TraceState(StateMachine* owner);
    ~NPC2TraceState();

public:
	virtual void Enter();
	virtual void Update(float deltaTime);
	virtual void Exit();
};


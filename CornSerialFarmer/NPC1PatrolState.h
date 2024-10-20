#pragma once

#include "FSMState.h"

class NPC1PatrolState 
    : public FSMState
{
public:
    NPC1PatrolState(StateMachine* owner);
    ~NPC1PatrolState();

public:
	virtual void Enter();
	virtual void Update(float deltaTime);
	virtual void Exit();
};


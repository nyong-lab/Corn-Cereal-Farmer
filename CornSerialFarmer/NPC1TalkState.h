#pragma once
#include "FSMState.h"

class NPC1TalkState :
    public FSMState
{
public:
    NPC1TalkState(StateMachine* owner);
    ~NPC1TalkState();

public:
	virtual void Enter();
	virtual void Update(float deltaTime);
	virtual void Exit();
};


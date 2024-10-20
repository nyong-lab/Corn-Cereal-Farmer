#pragma once
#include "FSMState.h"

/// <summary>
/// 작성일 : 2023.08.14
/// 작성자 : 고윤서
/// 
/// NPC2의 Return(귀환)을 정의하는 클래스
/// </summary>

class NPC2ReturnState :
    public FSMState
{
public:
    NPC2ReturnState(StateMachine* owner);
    ~NPC2ReturnState();

public:
	virtual void Enter();
	virtual void Update(float deltaTime);
	virtual void Exit();
};


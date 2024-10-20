#pragma once
#include "FSMState.h"

/// <summary>
/// 작성일 : 2023.08.16
/// 작성자 : 고윤서
/// 
/// 경찰의 순찰 상태를 정의하는 클래스
/// </summary>

class PolicePatrolState :
    public FSMState
{
public:
    PolicePatrolState(StateMachine* owner);
    ~PolicePatrolState();

public:
	virtual void Enter();
	virtual void Update(float deltaTime);
	virtual void Exit();
};


#pragma once
#include "FSMState.h"
/// <summary>
/// 작성일 : 2023.08.16
/// 작성자 : 고윤서
/// 
/// 경찰의 추적 상태를 정의하는 클래스
/// </summary>

class PoliceTraceState 
	: public FSMState
{
public:
	PoliceTraceState(StateMachine* onwer);
	~PoliceTraceState();

public:
	virtual void Enter();
	virtual void Update(float deltaTime);
	virtual void Exit();
};


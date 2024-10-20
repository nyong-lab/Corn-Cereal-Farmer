#pragma once
#include "FSMState.h"

/// <summary>
/// 작성일 : 2023.08.09
/// 초기 작성자 : 고윤서
/// 
/// 기본상태 Idle을 정의하는 클래스
/// </summary>

class StateMachine;
class IdleState 
	: public FSMState
{

public:
	IdleState(StateMachine* owner);
	~IdleState();

public:
	virtual void Enter();
	virtual void Update(float deltaTime);
	virtual void Exit();

};


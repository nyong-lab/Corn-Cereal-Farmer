#pragma once
#include "FSMState.h"


/// <summary>
/// 작성일 : 2023.08.16
/// 작성자 : 고윤서
/// 
/// 경찰의 시체 발견 상태를 정의하는 클래스
/// </summary>

class PoliceFindState :
    public FSMState
{
public:
    PoliceFindState(StateMachine* owner);
    ~PoliceFindState();

public:
	virtual void Enter();
	virtual void Update(float deltaTime);
	virtual void Exit();
};


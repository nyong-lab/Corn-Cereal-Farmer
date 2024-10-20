#pragma once
#include "FSMState.h"
/// <summary>
/// 작성일 : 2023.08.16
/// 작성자 : 고윤서
/// 
/// Police의 범인검거 상태를 정의하는 클래스
/// </summary>

class PoliceCatchState :
    public FSMState
{
public:
    PoliceCatchState(StateMachine* owner);
    ~PoliceCatchState();

public:
	virtual void Enter();
	virtual void Update(float deltaTime);
	virtual void Exit();
};


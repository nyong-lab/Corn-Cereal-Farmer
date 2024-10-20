#pragma once
#include "FSMState.h"
#include "ZicoMath.h"

/// <summary>
/// 작성일 : 2023.08.09
/// 초기 작성자 : 고윤서
/// 
/// 움직이는 상태 walk을 정의하는 클래스
/// </summary>


class WalkState :
    public FSMState
{
public:
    WalkState(StateMachine* owner);
    ~WalkState();

public:
	virtual void Enter();
	virtual void Update(float deltaTime);
	virtual void Exit();

};

 
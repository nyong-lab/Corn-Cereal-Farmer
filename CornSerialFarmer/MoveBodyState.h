#pragma once
#include "FSMState.h"

/// <summary>
/// 작성일 : 2023/08.17
/// 작성자 : 고윤서
/// 
/// 농부가 시체를 옮기는 상태를 정의하는 클래스
/// </summary>

class MoveBodyState :
    public FSMState
{
public:
    MoveBodyState(StateMachine* owner);
    ~MoveBodyState();

public:
	virtual void Enter();
	virtual void Update(float deltaTime);
	virtual void Exit();
};


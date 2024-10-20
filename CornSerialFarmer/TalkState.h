#pragma once
#include "FSMState.h"

/// <summary>
/// 작성일 : 2023.08.11
/// 초기 작성자 : 고윤서
/// 
/// 상호작용 중 Talk을 정의하는 클래스
/// </summary>

class TalkState :
    public FSMState
{
public:
    TalkState(StateMachine* owner);
	~TalkState();

public:
	virtual void Enter();
	virtual void Update(float deltaTime);
	virtual void Exit();
};


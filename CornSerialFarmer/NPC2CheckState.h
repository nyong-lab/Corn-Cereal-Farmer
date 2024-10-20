#pragma once
#include "FSMState.h"

/// <summary>
/// 작성일 : 2023.08.14
/// 작성자 : 고윤서
/// 
/// NPC2의 시체 확인 상태를 정의하는 클래스
/// </summary>

class NPC2CheckState :
    public FSMState
{
public:
    NPC2CheckState(StateMachine* owner);
    ~NPC2CheckState();

public:
	virtual void Enter();
	virtual void Update(float deltaTime);
	virtual void Exit();
};


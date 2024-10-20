#pragma once
#include "FSMState.h"

/// <summary>
/// 작성일: 2023.08.14
/// 작성자: 고윤서
/// 
/// npc1의 시체로 이동하는 상태를 정의하는 클래스
/// </summary>

class StateMachine;

class NPC1FindState :
    public FSMState
{
public:
    NPC1FindState(StateMachine* owner);
    ~NPC1FindState();

public:
	virtual void Enter();
	virtual void Update(float deltaTime);
	virtual void Exit();

};


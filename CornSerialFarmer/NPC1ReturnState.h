#pragma once
#include "FSMState.h"

/// <summary>
/// 작성일 : 2023.08.11
/// 작성자 : 고윤서
/// 
/// 이벤트 발생 후 스폰장소로 돌아가는 상태
/// </summary>

class StateMachine;

class NPC1ReturnState :
    public FSMState
{
public:
    NPC1ReturnState(StateMachine* owner);
    ~NPC1ReturnState();

public:
	virtual void Enter();
	virtual void Update(float deltaTime);
	virtual void Exit();

};


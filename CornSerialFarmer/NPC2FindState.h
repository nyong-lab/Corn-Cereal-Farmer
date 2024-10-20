#pragma once
#include "FSMState.h"

/// <summary>
/// 작성일 : 2023.08.14
/// 작성자 : 고윤서
/// 
/// NPC2의 시체로 이동 상태를 정의하는 클래스
/// </summary>

class NPC2FindState :
    public FSMState
{
public:
    NPC2FindState(StateMachine* owner);
    ~NPC2FindState();

public:
    virtual void Enter();
    virtual void Update(float deltaTime);
    virtual void Exit();
};


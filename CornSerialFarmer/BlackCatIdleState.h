#pragma once
#include "FSMState.h"

/// <summary>
/// 작성일 : 2023.08.15
/// 작성자 : 고윤서
/// 
/// Cat의 멈춤 상태를 정의하는 클래스
/// </summary>

class BlackCatIdleState :
    public FSMState
{
public:
    BlackCatIdleState(StateMachine* owner);
    ~BlackCatIdleState();

public:
    virtual void Enter();
    virtual void Update(float deltaTime);
    virtual void Exit();
};


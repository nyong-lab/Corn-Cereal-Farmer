#pragma once
#include "FSMState.h"

/// <summary>
/// 작성일 : 2023.08.17
/// 작성자 : 고윤서
/// 
/// 농부의 물 주는 상태를 정의하는 클래스
/// </summary>

class WateringState :
    public FSMState
{
public:
    WateringState(StateMachine* owner);
    ~WateringState();

public:
    virtual void Enter();
    virtual void Update(float deltaTime);
    virtual void Exit();
};


#pragma once
#include "FSMState.h"
/// <summary>
/// 작성일 : 2023.08.18
/// 작성자 : 고윤서
/// 
/// 경찰이 나타나지 않는 상태(아침)를 정의한다.
/// </summary>

class PoliceDieState :
    public FSMState
{
public:
    PoliceDieState(StateMachine* owner);
    ~PoliceDieState();

public:
    virtual void Enter();
    virtual void Update(float deltaTime);
    virtual void Exit();
};


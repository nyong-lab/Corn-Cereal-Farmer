#pragma once
#include "FSMState.h"

/// <summary>
/// 작성일 : 2023.08.17
/// 작성자 : 고윤하
/// 
/// Farmer가 농작물을 수확하는 상태를 정의하는 클래스
/// </summary>

class HarvestState :
    public FSMState
{
public:
    HarvestState(StateMachine* owner);
    ~HarvestState();

public:
    virtual void Enter();
    virtual void Update(float deltaTime);
    virtual void Exit();
};


#pragma once
#include "StateMachine.h"

#include "FarmNoWaterState.h"
#include "FarmWaterState.h"

/// <summary>
/// 작성일 : 2023.08.15
/// 작성자 : 고윤서
/// 
/// Farm의 FSM
/// </summary>


class FarmFSM :
    public StateMachine
{

public:
    FarmFSM(GameObject* owner);
    ~FarmFSM();

public:
    //상태들
    FarmNoWaterState m_FarmNoWaterState;
    FarmWaterState m_FarmWaterState;

    virtual void Update(float deltaTime) override;
};


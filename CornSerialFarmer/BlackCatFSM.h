#pragma once
#include "StateMachine.h"

#include "BlackCatIdleState.h"
#include "BlackCatMoveState.h"

/// <summary>
/// 작성일 : 2023.08.15
/// 작성자 : 고윤서
/// 
/// BlackCat의 FSM
/// </summary>

class BlackCatFSM :
    public StateMachine
{

public:
    BlackCatFSM(GameObject* owner);
    ~BlackCatFSM();

public:
    //상태들
    BlackCatIdleState m_BlackCatIdleState;
    BlackCatMoveState m_BlackCatMoveState;

    virtual void Update(float deltaTime) override;

};


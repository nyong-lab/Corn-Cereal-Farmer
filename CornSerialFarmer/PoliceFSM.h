#pragma once
#include "StateMachine.h"

#include "PoliceCatchState.h"
#include "PoliceFindState.h"
#include "PolicePatrolState.h"
#include "PoliceTraceState.h"
#include "PoliceIdleState.h"
#include "PoliceDieState.h"

/// <summary>
/// 작성일 : 2023.08.16
/// 작성자 : 고윤서
/// 
/// Police의 FSM
/// </summary>

class PoliceFSM :
    public StateMachine
{
public:
    PoliceFSM(GameObject* owner);
    ~PoliceFSM();

public:
    //상태들
    PoliceCatchState m_PoliceCatchState;
    PoliceFindState m_PoliceFindState;
    PolicePatrolState m_PolicePatroState;
    PoliceTraceState m_PoliceTraceState;
    PoliceIdleState m_PoliceIdleState;
    PoliceDieState m_PoliceDieState;

    virtual void Update(float deltaTime) override;
};


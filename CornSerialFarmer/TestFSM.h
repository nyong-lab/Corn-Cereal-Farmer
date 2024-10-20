   #pragma once
#include "StateMachine.h"

#include "IdleState.h"
#include "WalkState.h"
#include "TalkState.h"
#include "WateringState.h"
#include "HarvestState.h"
#include "MoveBodyState.h"
#include "InteractionState.h"

/// <summary>
/// 최초 작성일 : 2023.08.09
/// 작성자 : 고윤서 
///
/// 테스트 용 FSM 구현
/// 하지만 이것은 테스트가 아닌 농부의 FSM이 되엇다.
/// </summary>


class TestFSM :
    public StateMachine
{
public:
    TestFSM(GameObject* owner);
    ~TestFSM();

public:
    //상태들
    IdleState           m_IdleState;
    WalkState           m_WalkState;
    TalkState           m_TalkState;
    WateringState       m_WateringState;
    HarvestState        m_HarvestState;
    MoveBodyState       m_MoveBodyState;
    InteractionState    m_InteractionState;

    virtual void Update(float deltaTime) override;

};

 
#pragma once
#include "FSMState.h"
/// <summary>
/// 작성일 : 2023.08.14
/// 작성자 : 고윤서
/// 
/// NPC2의 대화상태를 정의하는 클래스
/// </summary>

class NPC2TalkState :
    public FSMState
{
public:
    NPC2TalkState(StateMachine* owner);
    ~NPC2TalkState();

public:
    virtual void Enter();
    virtual void Update(float deltaTime);
    virtual void Exit();

};


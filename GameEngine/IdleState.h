#pragma once
#include "FSMState.h"

/// <summary>
/// �ۼ��� : 2023.08.08
/// �ʱ� �ۼ��� : ������
/// 
/// �⺻���� Idle�� �����ϴ� Ŭ����
/// </summary>

class IdleState :
    public FSMState
{

public:
    IdleState(StateMachine* owner);
    ~IdleState();

public:
	virtual void Enter();
	virtual void Update();
	virtual void Exit();
	virtual bool CheckTransition();
};


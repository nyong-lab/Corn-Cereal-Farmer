#pragma once
#include <string>
using std::string;

/// <summary>
/// ���� �ۼ��� : 2023.08.08
/// ���� �ۼ��� : ������
/// 
/// ���� Ŭ�������� �θ� Ŭ����
/// 
/// </summary>

class StateMachine;

class FSMState
{

public:
	StateMachine* m_Machine; // ���¸� ���ư��� ����
	string m_FSMState; // ����


public:
	FSMState(StateMachine* machine, string fsmState);
	virtual ~FSMState();


public:
	void SetOwner(StateMachine* owner) { m_Machine = owner; }
	string& GetName() { return m_FSMState; }

	virtual void Enter() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Exit() = 0;

};


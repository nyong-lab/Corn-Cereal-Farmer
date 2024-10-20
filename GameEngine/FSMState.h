#pragma once
#include <string>
using std::string;

/// <summary>
/// 최초 작성일 : 2023.08.08
/// 최초 작성자 : 고윤서
/// 
/// 상태 클래스들의 부모 클래스
/// 
/// </summary>

class StateMachine;

class FSMState
{

public:
	StateMachine* m_Machine; // 상태를 돌아가게 해줌
	string m_FSMState; // 상태


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


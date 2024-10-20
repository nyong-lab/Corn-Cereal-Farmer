#pragma once
#include <map>
#include <string>
#include "ZicoMath.h"
using std::map;
using std::string;

/// <summary>
///  최초 작성일 : 2023.8.08
///  작성자 : 고윤서
/// 
/// FSM을 담당하게될 클래스
/// </summary>

//전방선언
class FSMState;
class GameObject;

class StateMachine
{
public:
	map<string, FSMState*> m_FSMStates; // 생성된 state들을 저장해두는 map

	FSMState* m_CurrentState; //현재 상태
	FSMState* m_InitialState; //초기 상태

	GameObject* m_Owner; // 주인
	string m_DetailState; // 상태의 상태 = 세부적인 상태를 의미

public:
	StateMachine();
	~StateMachine();

public:
	virtual void Update(float deltaTime);
	void ChangeState(string& stateType);
	void ChangeDetailState(string& detailType);
	void SetInitialState(string& stateType);
	void AddState(FSMState* fsmState);
	virtual void Finalize();



};


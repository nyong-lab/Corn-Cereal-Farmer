#pragma once
#include <map>
#include <string>
#include "ZicoMath.h"
using std::map;
using std::string;

/// <summary>
///  ���� �ۼ��� : 2023.8.08
///  �ۼ��� : ������
/// 
/// FSM�� ����ϰԵ� Ŭ����
/// </summary>

//���漱��
class FSMState;
class GameObject;

class StateMachine
{
public:
	map<string, FSMState*> m_FSMStates; // ������ state���� �����صδ� map

	FSMState* m_CurrentState; //���� ����
	FSMState* m_InitialState; //�ʱ� ����

	GameObject* m_Owner; // ����
	string m_DetailState; // ������ ���� = �������� ���¸� �ǹ�

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


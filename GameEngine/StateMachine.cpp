#include "pch.h"
#include "StateMachine.h"

#include "FSMState.h"
#include "GameObject.h"


StateMachine::StateMachine()
	: m_CurrentState(nullptr)
	, m_InitialState(nullptr)
	, m_Owner(nullptr)
	, m_DetailState("Idle")
{

}

StateMachine::~StateMachine()
{	
	
}

void StateMachine::Update(float deltaTime)
{
	//�ʱ� ���·� ����
	if (m_CurrentState == nullptr)
	{
		ChangeState(m_InitialState->GetName());
		return;
	}
		

	//update Action
	//���� �������� state�� Update�� �����Ŵ
	m_CurrentState->Update(deltaTime); 

}

void StateMachine::ChangeState(string& stateType)
{
	//���� ���¸� ������ ���� Exit() ����
	if (m_CurrentState)
	{
		m_CurrentState->Exit();
	}

	auto thisState = m_FSMStates.find(stateType);
	
	if (thisState != m_FSMStates.end())
	{
		m_CurrentState = thisState->second;

		//���ο� ���°� ���۵Ǳ� ���� Enter() ����
		m_CurrentState->Enter();
	}

}

void StateMachine::ChangeDetailState(string& detailType)
{
	m_DetailState = detailType;
}

void StateMachine::SetInitialState(string& stateType)
{
	auto thisState = m_FSMStates.find(stateType);

	if (thisState != m_FSMStates.end())
	{
		m_CurrentState = thisState->second;
	}
}

void StateMachine::AddState(FSMState* fsmState)
{
	m_FSMStates.emplace(fsmState->GetName(), fsmState);
}

void StateMachine::Finalize()
{
	for (auto& k : m_FSMStates)
	{
		k.second = nullptr;
	}

	map<string, FSMState*>().swap(m_FSMStates);
	m_FSMStates.clear();


}

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
	//초기 상태로 변경
	if (m_CurrentState == nullptr)
	{
		ChangeState(m_InitialState->GetName());
		return;
	}
		

	//update Action
	//현재 실행중인 state의 Update를 실행시킴
	m_CurrentState->Update(deltaTime); 

}

void StateMachine::ChangeState(string& stateType)
{
	//현재 상태를 끝내기 위해 Exit() 실행
	if (m_CurrentState)
	{
		m_CurrentState->Exit();
	}

	auto thisState = m_FSMStates.find(stateType);
	
	if (thisState != m_FSMStates.end())
	{
		m_CurrentState = thisState->second;

		//새로운 상태가 시작되기 위해 Enter() 실행
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

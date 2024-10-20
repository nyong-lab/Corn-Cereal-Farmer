#include "IdleState.h"
#include "StateMachine.h"

#include "GameObject.h"
#include "Component.h"
#include "Transform.h"
#include "Animation.h"
#include "Animator.h"
#include "BoxCollider.h"

IdleState::IdleState(StateMachine* owner)
	:FSMState(owner, "Idle")
{

}

IdleState::~IdleState()
{

}

void IdleState::Enter()
{
	
}

void IdleState::Update(float deltaTime)
{	
	if (m_Machine->m_DetailState.compare("IdleRight") == 0)
	{
		m_Machine->m_Owner->GetComponent<Animator>()->Play(L"farmerIdleRight", true);
	}
	if (m_Machine->m_DetailState.compare("IdleLeft") == 0)
	{
		m_Machine->m_Owner->GetComponent<Animator>()->Play(L"farmerIdleLeft", true);
	}
	if (m_Machine->m_DetailState.compare("IdleBack") == 0)
	{
		m_Machine->m_Owner->GetComponent<Animator>()->Play(L"farmerIdleBack", true);
	}
	if (m_Machine->m_DetailState.compare("IdleFront") == 0)
	{
		m_Machine->m_Owner->GetComponent<Animator>()->Play(L"farmerIdleFront", true);
	}

	//OutputDebugString(TEXT("Idle\n"));
}

void IdleState::Exit()
{

}


#include "PoliceFindState.h"
#include "StateMachine.h"

#include "GameObject.h"
#include "Component.h"
#include "Transform.h"
#include "Animator.h"
#include "Animation.h"

PoliceFindState::PoliceFindState(StateMachine* owner)
	:FSMState(owner, "PoliceFind")
{

}

PoliceFindState::~PoliceFindState()
{

}

void PoliceFindState::Enter()
{

}

void PoliceFindState::Update(float deltaTime)
{
	if (m_Machine->m_DetailState.compare("PoliceIdleRight") == 0)
	{
		m_Machine->m_Owner->GetComponent<Animator>()->Play(L"PoliceIdleRight", true);
	}
	if (m_Machine->m_DetailState.compare("PoliceIdleLeft") == 0)
	{
		m_Machine->m_Owner->GetComponent<Animator>()->Play(L"PoliceIdleLeft", true);
	}
	if (m_Machine->m_DetailState.compare("PoliceIdleBack") == 0)
	{
		m_Machine->m_Owner->GetComponent<Animator>()->Play(L"PoliceIdleBack", true);
	}
	if (m_Machine->m_DetailState.compare("PoliceIdleFront") == 0)
	{
		m_Machine->m_Owner->GetComponent<Animator>()->Play(L"PoliceIdleFront", true);
	}
}

void PoliceFindState::Exit()
{

}

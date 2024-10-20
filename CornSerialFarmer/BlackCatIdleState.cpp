#include "BlackCatIdleState.h"
#include "StateMachine.h"

#include "GameObject.h"
#include "Component.h"
#include "Transform.h"
#include "Animation.h"
#include "Animator.h"


BlackCatIdleState::BlackCatIdleState(StateMachine* owner)
	:FSMState(owner, "BlackCatIdle")
{
}

BlackCatIdleState::~BlackCatIdleState()
{

}

void BlackCatIdleState::Enter()
{
}

void BlackCatIdleState::Update(float deltaTime)
{
	if (m_Machine->m_DetailState.compare("IdleRight") == 0)
	{
		m_Machine->m_Owner->GetComponent<Animator>()->Play(L"blackCatIdleRight", true);
	}
	if (m_Machine->m_DetailState.compare("IdleLeft") == 0)
	{
		m_Machine->m_Owner->GetComponent<Animator>()->Play(L"blackCatIdleLeft", true);
	}
	if (m_Machine->m_DetailState.compare("IdleBack") == 0)
	{
		m_Machine->m_Owner->GetComponent<Animator>()->Play(L"blackCatIdleBack", true);
	}
	if (m_Machine->m_DetailState.compare("IdleFront") == 0)
	{
		m_Machine->m_Owner->GetComponent<Animator>()->Play(L"blackCatIdleFront", true);
	}
}

void BlackCatIdleState::Exit()
{
}

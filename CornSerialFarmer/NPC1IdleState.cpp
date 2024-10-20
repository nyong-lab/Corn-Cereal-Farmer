#include "NPC1IdleState.h"
#include "StateMachine.h"

#include "GameObject.h"
#include "Component.h"
#include "Transform.h"
#include "Animation.h"
#include "Animator.h"

NPC1IdleState::NPC1IdleState(StateMachine* owner)
	:FSMState(owner, "NPC1Idle")
{

}

NPC1IdleState::~NPC1IdleState()
{

}

void NPC1IdleState::Enter()
{

}

void NPC1IdleState::Update(float deltaTime)
{
	if (m_Machine->m_DetailState.compare("IdleRight") == 0)
	{
		m_Machine->m_Owner->GetComponent<Animator>()->Play(L"NPCIdleRight", true);
	}
	if (m_Machine->m_DetailState.compare("IdleLeft") == 0)
	{
		m_Machine->m_Owner->GetComponent<Animator>()->Play(L"NPCIdleLeft", true);
	}
	if (m_Machine->m_DetailState.compare("IdleBack") == 0)
	{
		m_Machine->m_Owner->GetComponent<Animator>()->Play(L"NPCIdleBack", true);
	}
	if (m_Machine->m_DetailState.compare("IdleFront") == 0)
	{
		m_Machine->m_Owner->GetComponent<Animator>()->Play(L"NPCIdleFront", true);
	}
}

void NPC1IdleState::Exit()
{

}

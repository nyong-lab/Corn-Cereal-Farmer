#include "NPC2CheckState.h"
#include "StateMachine.h"

#include "GameObject.h"
#include "Component.h"
#include "Transform.h"
#include "Animation.h"
#include "Animator.h"
#include "Collider.h"
#include "BoxCollider.h"

NPC2CheckState::NPC2CheckState(StateMachine* owner)
	:FSMState(owner, "NPC2Check")
{

}

NPC2CheckState::~NPC2CheckState()
{

}

void NPC2CheckState::Enter()
{
	m_Machine->m_Owner->GetObjectChild("NPCTextBubble")->GetComponent<Animator>()->Play(L"QuestionMark", true);
	m_Machine->m_Owner->GetObjectChild("NPCTextBubble")->SetActivate(true);
}

void NPC2CheckState::Update(float deltaTime)
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

void NPC2CheckState::Exit()
{
	m_Machine->m_Owner->GetObjectChild("NPCTextBubble")->SetActivate(false);
}

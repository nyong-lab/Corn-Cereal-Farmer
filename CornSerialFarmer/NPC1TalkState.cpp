#include "NPC1TalkState.h"
#include "StateMachine.h"

#include "GameObject.h"
#include "Component.h"
#include "Transform.h"
#include "Animation.h"
#include "Animator.h"
#include "TextRenderer.h"
#include "MonoBehaviour.h"

#include "NPC1Script.h"

NPC1TalkState::NPC1TalkState(StateMachine* owner)
	:FSMState(owner, "NPC1Talk")
{

}

NPC1TalkState::~NPC1TalkState()
{

}

void NPC1TalkState::Enter()
{
	m_Machine->m_Owner->GetObjectChild("NPCTextBubble")->GetComponent<Animator>()->Play(L"TextBubble3", true);
	wstring dateText = dynamic_cast<NPC1Script*>(m_Machine->m_Owner->GetComponent<MonoBehaviour>())->textOut;
	m_Machine->m_Owner->GetObjectChild("NPCTextBubble")->GetComponent<TextRenderer>()->SetTextColor(COLOR::BLACK);
	m_Machine->m_Owner->GetObjectChild("NPCTextBubble")->GetComponent<TextRenderer>()->SetText(dateText.c_str());
	m_Machine->m_Owner->GetObjectChild("NPCTextBubble")->SetActivate(true);
}

void NPC1TalkState::Update(float deltaTime)
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

void NPC1TalkState::Exit()
{
	m_Machine->m_Owner->GetObjectChild("NPCTextBubble")->SetActivate(false);
	wstring dateText2 = L" ";
	m_Machine->m_Owner->GetObjectChild("NPCTextBubble")->GetComponent<TextRenderer>()->SetTextColor(COLOR::WHITE);
	m_Machine->m_Owner->GetObjectChild("NPCTextBubble")->GetComponent<TextRenderer>()->SetText(dateText2.c_str());
	
}

#include "TalkState.h"
#include "StateMachine.h"

#include "GameObject.h"
#include "Component.h"
#include "Transform.h"
#include "Animation.h"
#include "Animator.h"
#include "TextRenderer.h"

#include "FarmerScript.h"

TalkState::TalkState(StateMachine* owner)
	:FSMState(owner, "Talk")
{

}

TalkState::~TalkState()
{

}

void TalkState::Enter()
{
	m_Machine->m_Owner->GetObjectChild("farmerTextBubble")->GetComponent<Animator>()->Play(L"TextBubble", true);
	wstring dateText = dynamic_cast<FarmerScript*>(m_Machine->m_Owner->GetComponent<MonoBehaviour>())->textOut;
	m_Machine->m_Owner->GetObjectChild("farmerTextBubble")->GetComponent<TextRenderer>()->SetTextColor(COLOR::BLACK);
	m_Machine->m_Owner->GetObjectChild("farmerTextBubble")->GetComponent<TextRenderer>()->SetText(dateText.c_str());
	m_Machine->m_Owner->GetObjectChild("farmerTextBubble")->SetActivate(true);
	
}

void TalkState::Update(float deltaTime)
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
}

void TalkState::Exit()
{
	m_Machine->m_Owner->GetObjectChild("farmerTextBubble")->SetActivate(false);
	wstring dateText2 = L" ";
	m_Machine->m_Owner->GetObjectChild("farmerTextBubble")->GetComponent<TextRenderer>()->SetTextColor(COLOR::WHITE);
	m_Machine->m_Owner->GetObjectChild("farmerTextBubble")->GetComponent<TextRenderer>()->SetText(dateText2.c_str());
}

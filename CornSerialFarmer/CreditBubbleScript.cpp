#include "CreditBubbleScript.h"
#include "TextRenderer.h"
#include "ResourceManager.h"
#include "Image.h"
#include "ImageRenderer.h"

CreditBubbleScript::CreditBubbleScript() :
	MonoBehaviour(typeid(this).name())
{
}

CreditBubbleScript::~CreditBubbleScript()
{
}

void CreditBubbleScript::Start()
{
}

void CreditBubbleScript::Update(float deltaTime)
{
	if (m_IsPlaying) m_TimePassed += deltaTime;

	if (m_StringSize < m_Text.size() && m_IsPlaying)
	{
		m_StringSize += 20 * deltaTime;
	}

// 	if (m_StringSize >= m_Text.size() && m_IsPlaying)
// 	{
// 		m_IsPlaying = false;
// 	}

	std::wstring temp;
	temp.assign(m_Text.begin(), m_Text.begin() + (int)m_StringSize);
	m_TextRenderer->SetText(temp);

	if (m_TimePassed >= 5.f)
	{
		m_StringSize = 0;
		m_SpeechBubble->SetImage(ResourceManager::GetInstance()->LoadResource<Image>(L"CreditBubbleImageNone", L"/EndingCredit/creditBubbleNone.png")->GetImage());
		m_TimePassed = 0.f;
		m_IsPlaying = false;
	}

}

void CreditBubbleScript::FixedUpdate(float deltaTime)
{
}

void CreditBubbleScript::Finalize()
{
}

void CreditBubbleScript::BtnCallBackFunc()
{
	if (!m_IsPlaying && m_StringSize < m_Text.size())
	{
		m_IsPlaying = true;
	}
}

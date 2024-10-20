#include "BlackScreenScript.h"

#include "ResourceManager.h"
#include "Image.h"
#include "TextRenderer.h"
#include "ImageRenderer.h"
#include "GameObject.h"

BlackScreenScript::BlackScreenScript()
	: MonoBehaviour(typeid(this).name())
{

}

BlackScreenScript::~BlackScreenScript()
{

}

void BlackScreenScript::Start()
{
	m_BlackScreen = GetGameObject()->GetComponent<ImageRenderer>();
	m_BlackScreen->SetOpacity(0.f);
}

void BlackScreenScript::Update(float deltaTime)
{
	if (m_StringSize < m_Text.size() && m_IsPlaying)
	{
		m_StringSize += 20 * deltaTime;
	}

	if (m_StringSize >= m_Text.size() && m_IsPlaying)
	{
		m_IsPlaying = false;
	}

	std::wstring temp;
	temp.assign(m_Text.begin(), m_Text.begin() + (int)m_StringSize);
	m_EventText->SetText(temp);
}

void BlackScreenScript::PlayText(bool isDay, std::wstring eventText)
{
	m_IsPlaying = true;
	m_Text = eventText;
	m_IsDay = isDay;

	// 낮이면
	if (isDay)
	{
		m_DayIcon->SetImage(
			ResourceManager::GetInstance()->LoadResource<Image>(L"DayIcon-Sun", L"/Image/UI/Sun.png")->GetImage()
		);
		m_DayText->SetText(L"낮이 되었습니다...");
		m_DayText->SetTextColor(COLOR::WHITE);
		m_EventText->SetTextColor(COLOR::SUN);
	}
	// 밤이면
	else
	{
		m_DayIcon->SetImage(
			ResourceManager::GetInstance()->LoadResource<Image>(L"DayIcon-Moon", L"/Image/UI/Moon.png")->GetImage()
		);
		m_DayText->SetText(L"밤이 되었습니다...");
		m_DayText->SetTextColor(COLOR::WHITE);
		m_EventText->SetTextColor(COLOR::MOON);
	}

}

void BlackScreenScript::DisabledBlackScreen()
{
	// 초기화
	m_Text = L"";
	m_StringSize = 0;
	m_IsPlaying = false;

	m_EventText->SetText(L"");
	m_DayText->SetText(L"");
	m_DayIcon->SetImage(
		ResourceManager::GetInstance()->LoadResource<Image>(L"DayIcon-None", L"/Image/UI/None.png")->GetImage()
	);

	m_BlackScreen->SetOpacity(0.f);
}

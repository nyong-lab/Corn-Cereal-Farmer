#include "BlackScreen.h"
#include "Define.h"
#include "GameplayStatics.h"

#include "Transform.h"

#include "ResourceManager.h"
#include "Image.h"

#include "UI.h"
#include "ImageRenderer.h"
#include "TextRenderer.h"
#include "Panel.h"
#include "Font.h"

#include "BlackScreenScript.h"

BlackScreen::BlackScreen()
	: GameObject("BlackScreen", OBJECT_TYPE::UI)
{
	// Set Position & Size
	GetTransform()->SetLocalPosition(Vector2(960.f, 540.f));
	GetTransform()->SetSize(Vector2(1920.f, 1080.f));

	// Component
	ImageRenderer* blackScreenRender = new ImageRenderer(
		ResourceManager::GetInstance()->LoadResource<Image>(L"BlackScreen", L"/Image/UI/black.png")->GetImage());
	AddComponent(blackScreenRender);

	/// Icon (¹ã / ³·) -----------------------------------------------------------------------------------------

	m_DayIcon = new GameObject("DayIcon", OBJECT_TYPE::UI);
	m_DayIcon->GetTransform()->SetLocalPosition(Vector2(-10.f, -270.f));
	m_DayIcon->GetTransform()->SetSize(Vector2(161.f, 160.f));

	ImageRenderer* dayImage = new ImageRenderer(
		ResourceManager::GetInstance()->LoadResource<Image>(L"DayIcon-None", L"/Image/UI/None.png")->GetImage());
	m_DayIcon->AddComponent(dayImage);

	// Add Object
	AddObjectChild(m_DayIcon);

	/// Alert (¹ã / ³·) ----------------------------------------------------------------------------------------

	GameObject* dayAlert = new GameObject("DayAlert", OBJECT_TYPE::UI);
	dayAlert->GetTransform()->SetLocalPosition(Vector2(0.f, -170.f));

	// Dat & Night Text
	TextRenderer* dayAlertTextRender = new TextRenderer(
		Vector2(0.f, 0.f),
		L"",
		ResourceManager::GetInstance()->LoadResource<Font>(L"BitBit48", L"/Font/DNFBitBitTTF.ttf", L"´øÆÄ ºñÆ®ºñÆ®Ã¼ TTF", 48.f)->Getfont(),
		COLOR::WHITE
	);
	ResourceManager::GetInstance()->LoadResource<Font>(L"BitBit48")->SetHorizontalAlign(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	ResourceManager::GetInstance()->LoadResource<Font>(L"BitBit48")->SetVerticalAlign(DWRITE_TEXT_ALIGNMENT_CENTER);
	dayAlertTextRender->SetTextAlignMiddle();
	dayAlert->AddComponent(dayAlertTextRender);

	// Add Object
	AddObjectChild(dayAlert);

	/// Alert (ÀÌº¥Æ®) ------------------------------------------------------------------------------------------

	GameObject* eventAlert = new GameObject("EventAlert", OBJECT_TYPE::UI);
	eventAlert->GetTransform()->SetLocalPosition(Vector2(0.f, 170.f));

	// Alert Text
	TextRenderer* eventAlertTextRender = new TextRenderer(
		Vector2(0.f, 0.f),
		L"",
		ResourceManager::GetInstance()->LoadResource<Font>(L"Galmuri9_16", L"/Font/Galmuri9.ttf", L"Galmuri9", 16.f)->Getfont(),
		COLOR::MOON
	);
	ResourceManager::GetInstance()->LoadResource<Font>(L"Galmuri9_16")->SetHorizontalAlign(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	ResourceManager::GetInstance()->LoadResource<Font>(L"Galmuri9_16")->SetVerticalAlign(DWRITE_TEXT_ALIGNMENT_CENTER);
	eventAlertTextRender->SetTextAlignMiddle();
	eventAlert->AddComponent(eventAlertTextRender);

	// Add Object
	AddObjectChild(eventAlert);

	/// Script ------------------------------------------------------------------------------------------

	m_BlackScreenScript = new BlackScreenScript();
	AddComponent(m_BlackScreenScript);

	m_BlackScreenScript->m_DayIcon = dayImage;
	m_BlackScreenScript->m_DayText = dayAlertTextRender;
	m_BlackScreenScript->m_EventText = eventAlertTextRender;
}

BlackScreen::~BlackScreen()
{

}
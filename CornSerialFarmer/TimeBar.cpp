#include "TimeBar.h"
#include "Define.h"

#include "Transform.h"

#include "ResourceManager.h"
#include "Image.h"
#include "Font.h"

#include "UI.h"
#include "ImageRenderer.h"
#include "TextRenderer.h"
#include "Panel.h"

TimeBar::TimeBar()
	: GameObject("TimeBar", OBJECT_TYPE::UI)
{
	// Set Position & Size
	GetTransform()->SetLocalPosition(Vector2(960.f, 120.f));
	GetTransform()->SetSize(Vector2(692.f, 44.f));

	// Empty UI
	UI* timeBarBaseUI = new Panel();
	AddComponent(timeBarBaseUI);

	// Base Image
	ImageRenderer* timeBarBaseImage = new ImageRenderer(
		ResourceManager::GetInstance()->LoadResource<Image>(L"TimeBarBaseImage", L"/UI/timebarBase.png")->GetImage());
	AddComponent(timeBarBaseImage);

	/// Time Bar

	GameObject* timeBar = new GameObject("TimeBar", OBJECT_TYPE::UI);
	AddObjectChild(timeBar);

	// Set Size
	timeBar->GetTransform()->SetSize(Vector2(668.f, 20.f));

	// Empty UI
	UI* timeBarUI = new Panel();
	timeBar->AddComponent(timeBarUI);

	// Time Bar Image
	m_TimeBarImage = new ImageRenderer(
		ResourceManager::GetInstance()->LoadResource<Image>(L"TimeBarImageSun", L"/UI/timebarSun.png")->GetImage(),
		Vector2(0.f, 0.f),
		Vector2(0.f, 0.f),
		Vector2(0.f, 44.f)
		);
	timeBar->AddComponent(m_TimeBarImage);

	/// Time Bar ICON

	GameObject* timeBarIcon = new GameObject("TimeBarIcon", OBJECT_TYPE::UI);
	AddObjectChild(timeBarIcon);

	// Set Size
	timeBarIcon->GetTransform()->SetSize(Vector2(865.f, 171.f));

	// Empty UI
	UI* timeBarIconUI = new Panel();
	timeBarIcon->AddComponent(timeBarIconUI);

	// Time Bar Icon Image
	m_TimeBarIconImage = new ImageRenderer(
		ResourceManager::GetInstance()->LoadResource<Image>(L"TimeBarIconSun", L"/UI/timeiconSun.png")->GetImage());
	timeBarIcon->AddComponent(m_TimeBarIconImage);

	/// Date Text

	GameObject* dateText = new GameObject("DateText", OBJECT_TYPE::UI);
	dateText->GetTransform()->SetSize(Vector2(222.f, 81.f));
	AddObjectChild(dateText);

	// Empty UI
	UI* dateTextUI = new Panel();
	dateText->AddComponent(dateTextUI);

	// Date Base Image Renderer
	ImageRenderer* dateBaseImage = new ImageRenderer(
		ResourceManager::GetInstance()->LoadResource<Image>(L"DateBaseImage", L"/UI/datebox.png")->GetImage(),
		Vector2(0.f, -68.f));
	dateText->AddComponent(dateBaseImage);

	// Date Text Renderer

	m_DateTextRenderer = new TextRenderer(
		Vector2(0.f, -90.f),
		L"1일차 낮",
		ResourceManager::GetInstance()->LoadResource<Font>(L"BitBit48", L"/Font/DNFBitBitTTF.ttf", L"던파 비트비트체 TTF", 48.f)->Getfont(),
		COLOR::TIMEBAR
		);
	ResourceManager::GetInstance()->LoadResource<Font>(L"BitBit48")->SetHorizontalAlign(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	ResourceManager::GetInstance()->LoadResource<Font>(L"BitBit48")->SetVerticalAlign(DWRITE_TEXT_ALIGNMENT_CENTER);
	m_DateTextRenderer->SetTextAlignMiddle();
	dateText->AddComponent(m_DateTextRenderer);
}

TimeBar::~TimeBar()
{

}

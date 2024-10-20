#include "ExplainWindow.h"
#include "Define.h"
#include "GameplayStatics.h"

#include "Transform.h"

#include "ResourceManager.h"
#include "Image.h"
#include "Panel.h"
#include "ImageRenderer.h"
#include "TextRenderer.h"
#include "Font.h"

#include "ExplainWindowScript.h"

ExplainWindow::ExplainWindow()
	: GameObject("ExplainWindow", OBJECT_TYPE::UI)
{
	// Set Position & Size
	GetTransform()->SetLocalPosition(Vector2(1726.f, 580.f));
	GetTransform()->SetSize(Vector2(337.f, 89.f));

	// Base UI
	UI* explainWindowUI = new Panel();
	AddComponent(explainWindowUI);

	// Base Image
	ImageRenderer* explainWindowImage = new ImageRenderer(
		ResourceManager::GetInstance()->LoadResource<Image>(L"ExplainWindowImage", L"/Image/UI/object/OBJ_4558.png")->GetImage());
	AddComponent(explainWindowImage);

	TextRenderer* explainText = new TextRenderer(
		Vector2(0.f, -21.f),
		L"",
		ResourceManager::GetInstance()->LoadResource<Font>(L"Galmuri9_19", L"/Font/Galmuri9.ttf", L"Galmuri9", 19.f)->Getfont()
		, COLOR::WHITE
	);
	ResourceManager::GetInstance()->LoadResource<Font>(L"Galmuri9_19")->SetHorizontalAlign(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	ResourceManager::GetInstance()->LoadResource<Font>(L"Galmuri9_19")->SetVerticalAlign(DWRITE_TEXT_ALIGNMENT_CENTER);
	explainText->SetTextAlignMiddle();
	AddComponent(explainText);

	ExplainWindowScript* explainWindowScript = new ExplainWindowScript();
	explainWindowScript->SetTextRenderer(explainText);
	explainWindowScript->SetImageRenderer(explainWindowImage);
	AddComponent(explainWindowScript);
}

ExplainWindow::~ExplainWindow()
{

}

#include "TrueEnding.h"
#include "GameObject.h"
#include "ImageRenderer.h"
#include "ResourceManager.h"
#include "Image.h"
#include "panel.h"
#include "Transform.h"
#include "TextRenderer.h"
#include "CutSceneScript.h"
#include "Font.h"
#include "Button.h"

void TrueEnding::Enter()
{

	GameObject* trueEnding = new GameObject("TrueEnding", OBJECT_TYPE::UI);
	trueEnding->GetTransform()->SetLocalPosition({ 1920.f / 2.f, 1080.f / 2.f });
	trueEnding->GetTransform()->SetSize({ 1920.f, 1080.f });
	Panel* trueEndingPanel = new Panel();
	ImageRenderer* trueEndingRender = new ImageRenderer(
		nullptr,
		{},
		{},
		{ 1920.f, 1080.f }
	);
	trueEnding->AddComponent(trueEndingPanel);
	trueEnding->AddComponent(trueEndingRender);
	AddGameObject(trueEnding);



	GameObject* trueEndingText = new GameObject("trueEndingText", OBJECT_TYPE::UI);
	trueEndingText->GetTransform()->SetLocalPosition({ 0.f, 255.f });
	Panel* trueEndingTextPanel = new Panel();
	TextRenderer* trueEndingTextRender = new TextRenderer({},
		L"",
		ResourceManager::GetInstance()->LoadResource<Font>(L"Galmuri9_28", L"/Font/Galmuri9.ttf", L"Galmuri9", 28.f)->Getfont(),
		COLOR::WHITE);
	ResourceManager::GetInstance()->LoadResource<Font>(L"Galmuri9_28")->SetHorizontalAlign(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
	ResourceManager::GetInstance()->LoadResource<Font>(L"Galmuri9_28")->SetVerticalAlign(DWRITE_TEXT_ALIGNMENT_CENTER);
	trueEndingTextRender->SetTextAlignMiddle();
	CutSceneScript* trueEndingScript = new CutSceneScript;
	trueEndingScript->m_TextRenderer = trueEndingTextRender;
	trueEndingScript->m_ImageRenderer = trueEndingRender;

	trueEndingScript->m_CutSceneImage.push_back(ResourceManager::GetInstance()->LoadResource<Image>(L"TrueEnding1", L"/CutScene/TrueEnding/1.png"));
	trueEndingScript->m_CutSceneImage.push_back(ResourceManager::GetInstance()->LoadResource<Image>(L"TrueEnding2", L"/CutScene/TrueEnding/2.png"));
	trueEndingScript->m_CutSceneImage.push_back(ResourceManager::GetInstance()->LoadResource<Image>(L"TrueEnding3", L"/CutScene/TrueEnding/3.png"));
	trueEndingScript->m_CutSceneImage.push_back(ResourceManager::GetInstance()->LoadResource<Image>(L"TrueEnding4", L"/CutScene/TrueEnding/4.png"));
	trueEndingScript->m_CutSceneImage.push_back(ResourceManager::GetInstance()->LoadResource<Image>(L"TrueEnding5", L"/CutScene/TrueEnding/5.png"));
	trueEndingScript->m_CutSceneImage.push_back(ResourceManager::GetInstance()->LoadResource<Image>(L"TrueEnding6", L"/CutScene/TrueEnding/6.png"));

	trueEndingScript->m_Text.push_back(L"");
	trueEndingScript->m_Text.push_back(L"");
	trueEndingScript->m_Text.push_back(L"");
	trueEndingScript->m_Text.push_back(L"");
	trueEndingScript->m_Text.push_back(L"");
	trueEndingScript->m_Text.push_back(L"The End");


	trueEndingScript->m_NextSceneName = "BloodStartScene";


	trueEndingText->AddComponent(trueEndingScript);
	trueEndingText->AddComponent(trueEndingTextPanel);
	trueEndingText->AddComponent(trueEndingTextRender);
	trueEnding->AddObjectChild(trueEndingText);


	{
		GameObject* trueEndingSpace = new GameObject("trueEndingSpace", OBJECT_TYPE::UI);
		trueEndingSpace->GetTransform()->SetLocalPosition({ 700.f, 450.f });
		trueEndingSpace->GetTransform()->SetSize({ 433.f, 84.f });
		ImageRenderer* trueEndingSpaceRender = new ImageRenderer(
			ResourceManager::GetInstance()->LoadResource<Image>(L"SpaceButtonHover", L"/CutScene/SpaceBar/1_2.png")->GetImage(),
			{},
			{},
			{ 1920.f, 1080.f }
		);
		Button* spacebutton = new Button(
			[trueEndingSpaceRender, trueEndingScript](BUTTON_EVENT event) {
				if (event == BUTTON_EVENT::DEFAULT) {
					trueEndingScript->m_IsButtonHandled = false;

				}
		if (event == BUTTON_EVENT::HOVER) {
			trueEndingScript->m_IsButtonHandled = true;
			trueEndingSpaceRender->SetImage(
				ResourceManager::GetInstance()->LoadResource<Image>(L"SpaceButtonHover", L"/CutScene/SpaceBar/1_2.png")->GetImage()
			);

			// Sound
		}
		if (event == BUTTON_EVENT::DOWN) {
			trueEndingScript->m_IsButtonHandled = true;
			trueEndingSpaceRender->SetImage(
				ResourceManager::GetInstance()->LoadResource<Image>(L"SpaceButtonDown", L"/CutScene/SpaceBar/1_1.png")->GetImage()
			);
		}
		if (event == BUTTON_EVENT::CLICK) {
			trueEndingScript->m_IsButtonHandled = true;
			trueEndingScript->BtnCallBack();
		}
			}
		);

		trueEndingScript->m_SpaceRenderer = trueEndingSpaceRender;

		trueEndingSpace->AddComponent(spacebutton);
		trueEndingSpace->AddComponent(trueEndingSpaceRender);
		trueEnding->AddObjectChild(trueEndingSpace);
	}

}

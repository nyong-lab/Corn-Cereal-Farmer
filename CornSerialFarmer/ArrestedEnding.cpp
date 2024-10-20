#include "ArrestedEnding.h"
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

void ArrestedEnding::Enter()
{

	GameObject* arrestedEnding = new GameObject("ArrestedEnding", OBJECT_TYPE::UI);
	arrestedEnding->GetTransform()->SetLocalPosition({ 1920.f / 2.f, 1080.f / 2.f });
	arrestedEnding->GetTransform()->SetSize({ 1920.f, 1080.f });
	Panel* arrestedEndingPanel = new Panel();
	ImageRenderer* arrestedEndingRender = new ImageRenderer(
		nullptr,
		{},
		{},
		{ 1920.f, 1080.f }
	);
	arrestedEnding->AddComponent(arrestedEndingPanel);
	arrestedEnding->AddComponent(arrestedEndingRender);
	AddGameObject(arrestedEnding);



	GameObject* arrestedEndingText = new GameObject("arrestedEndingText", OBJECT_TYPE::UI);
	arrestedEndingText->GetTransform()->SetLocalPosition({ 0.f, 255.f });
	Panel* arrestedEndingTextPanel = new Panel();
	TextRenderer* arrestedEndingTextRender = new TextRenderer({},
		L"",
		ResourceManager::GetInstance()->LoadResource<Font>(L"Galmuri9_28", L"/Font/Galmuri9.ttf", L"Galmuri9", 28.f)->Getfont(),
		COLOR::WHITE);
	ResourceManager::GetInstance()->LoadResource<Font>(L"Galmuri9_28")->SetHorizontalAlign(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
	ResourceManager::GetInstance()->LoadResource<Font>(L"Galmuri9_28")->SetVerticalAlign(DWRITE_TEXT_ALIGNMENT_CENTER);
	arrestedEndingTextRender->SetTextAlignMiddle();
	CutSceneScript* arrestedEndingScript = new CutSceneScript;
	arrestedEndingScript->m_TextRenderer = arrestedEndingTextRender;
	arrestedEndingScript->m_ImageRenderer = arrestedEndingRender;

	arrestedEndingScript->m_CutSceneImage.push_back(ResourceManager::GetInstance()->LoadResource<Image>(L"ArrestedEnding1", L"/CutScene/ArrestedEnding/1.png"));
	arrestedEndingScript->m_CutSceneImage.push_back(ResourceManager::GetInstance()->LoadResource<Image>(L"ArrestedEnding2", L"/CutScene/ArrestedEnding/2.png"));
	arrestedEndingScript->m_CutSceneImage.push_back(ResourceManager::GetInstance()->LoadResource<Image>(L"ArrestedEnding3", L"/CutScene/ArrestedEnding/3.png"));
	arrestedEndingScript->m_CutSceneImage.push_back(ResourceManager::GetInstance()->LoadResource<Image>(L"ArrestedEnding4", L"/CutScene/ArrestedEnding/4.png"));
	arrestedEndingScript->m_CutSceneImage.push_back(ResourceManager::GetInstance()->LoadResource<Image>(L"ArrestedEnding5", L"/CutScene/ArrestedEnding/5.png"));

	arrestedEndingScript->m_Text.push_back(L"");
	arrestedEndingScript->m_Text.push_back(L"");
	arrestedEndingScript->m_Text.push_back(L"\"이건 시체잖아 ? !\"");
	arrestedEndingScript->m_Text.push_back(L"<시골 마을에 숨어있던>\n<연쇄살인범 검거>");
	arrestedEndingScript->m_Text.push_back(L"The End");


	arrestedEndingScript->m_NextSceneName = "BloodStartScene";


	arrestedEndingText->AddComponent(arrestedEndingScript);
	arrestedEndingText->AddComponent(arrestedEndingTextPanel);
	arrestedEndingText->AddComponent(arrestedEndingTextRender);
	arrestedEnding->AddObjectChild(arrestedEndingText);


	{
		GameObject* arrestedEndingSpace = new GameObject("arrestedEndingSpace", OBJECT_TYPE::UI);
		arrestedEndingSpace->GetTransform()->SetLocalPosition({ 700.f, 450.f });
		arrestedEndingSpace->GetTransform()->SetSize({ 433.f, 84.f });
		ImageRenderer* arrestedEndingSpaceRender = new ImageRenderer(
			ResourceManager::GetInstance()->LoadResource<Image>(L"SpaceButtonHover", L"/CutScene/SpaceBar/1_2.png")->GetImage(),
			{},
			{},
			{ 1920.f, 1080.f }
		);
		Button* spacebutton = new Button(
			[arrestedEndingSpaceRender, arrestedEndingScript](BUTTON_EVENT event) {
				if (event == BUTTON_EVENT::DEFAULT) {
					arrestedEndingScript->m_IsButtonHandled = false;

				}
		if (event == BUTTON_EVENT::HOVER) {
			arrestedEndingScript->m_IsButtonHandled = true;
			arrestedEndingSpaceRender->SetImage(
				ResourceManager::GetInstance()->LoadResource<Image>(L"SpaceButtonHover", L"/CutScene/SpaceBar/1_2.png")->GetImage()
			);

			// Sound
		}
		if (event == BUTTON_EVENT::DOWN) {
			arrestedEndingScript->m_IsButtonHandled = true;
			arrestedEndingSpaceRender->SetImage(
				ResourceManager::GetInstance()->LoadResource<Image>(L"SpaceButtonDown", L"/CutScene/SpaceBar/1_1.png")->GetImage()
			);
		}
		if (event == BUTTON_EVENT::CLICK) {
			arrestedEndingScript->m_IsButtonHandled = true;
			arrestedEndingScript->BtnCallBack();
		}
			}
		);

		arrestedEndingScript->m_SpaceRenderer = arrestedEndingSpaceRender;

		arrestedEndingSpace->AddComponent(spacebutton);
		arrestedEndingSpace->AddComponent(arrestedEndingSpaceRender);
		arrestedEnding->AddObjectChild(arrestedEndingSpace);
	}

}

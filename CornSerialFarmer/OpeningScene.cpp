#include "OpeningScene.h"
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

void OpeningScene::Enter()
{

	GameObject* opening1 = new GameObject("Opening1", OBJECT_TYPE::UI);
	opening1->GetTransform()->SetLocalPosition({ 1920.f / 2.f, 1080.f / 2.f });
	opening1->GetTransform()->SetSize({ 1920.f, 1080.f });
	Panel* opening1Panel = new Panel();
	ImageRenderer* opening1Render = new ImageRenderer(
		nullptr,
		{},
		{},
		{ 1920.f, 1080.f }
	);
	opening1->AddComponent(opening1Panel);
	opening1->AddComponent(opening1Render);
	AddGameObject(opening1);

	GameObject* openingText1 = new GameObject("OpeningText1", OBJECT_TYPE::UI);
	openingText1->GetTransform()->SetLocalPosition({ 0.f, 255.f });
	Panel* openingText1Panel = new Panel();
	TextRenderer* openingText1Render = new TextRenderer({},
		L"",
		ResourceManager::GetInstance()->LoadResource<Font>(L"Galmuri9_28", L"/Font/Galmuri9.ttf", L"Galmuri9", 28.f)->Getfont(),
		COLOR::WHITE);
	ResourceManager::GetInstance()->LoadResource<Font>(L"Galmuri9_28")->SetHorizontalAlign(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
	ResourceManager::GetInstance()->LoadResource<Font>(L"Galmuri9_28")->SetVerticalAlign(DWRITE_TEXT_ALIGNMENT_CENTER);
	openingText1Render->SetTextAlignMiddle();
	CutSceneScript* openingText1Script = new CutSceneScript;
	openingText1Script->m_TextRenderer = openingText1Render;
	openingText1Script->m_ImageRenderer = opening1Render;

	openingText1Script->m_CutSceneImage.push_back(ResourceManager::GetInstance()->LoadResource<Image>(L"Opening1", L"/CutScene/Opening/1.png"));
	openingText1Script->m_CutSceneImage.push_back(ResourceManager::GetInstance()->LoadResource<Image>(L"Opening2", L"/CutScene/Opening/2.png"));
	openingText1Script->m_CutSceneImage.push_back(ResourceManager::GetInstance()->LoadResource<Image>(L"Opening3", L"/CutScene/Opening/3.png"));
	openingText1Script->m_CutSceneImage.push_back(ResourceManager::GetInstance()->LoadResource<Image>(L"Opening4", L"/CutScene/Opening/4.png"));
	openingText1Script->m_CutSceneImage.push_back(ResourceManager::GetInstance()->LoadResource<Image>(L"Opening5", L"/CutScene/Opening/5.png"));

	openingText1Script->m_Text.push_back(L"어느 평화로운 작은 시골 마을...");
	openingText1Script->m_Text.push_back(L"옥수수밭을 일구는 농부가 있습니다.");
	openingText1Script->m_Text.push_back(L"그러나 평화로운 이곳에는...");
	openingText1Script->m_Text.push_back(L"작은 비밀이 있습니다");
	openingText1Script->m_Text.push_back(L"농사 일을 열심히 하면서\n농부의 Secret도 지켜볼까요?");

	openingText1Script->m_NextSceneName = "MainScene";


	openingText1->AddComponent(openingText1Script);
	openingText1->AddComponent(openingText1Panel);
	openingText1->AddComponent(openingText1Render);
	opening1->AddObjectChild(openingText1);


	{
		GameObject* opening1Space = new GameObject("Opening1Space", OBJECT_TYPE::UI);
		opening1Space->GetTransform()->SetLocalPosition({ 700.f, 450.f });
		opening1Space->GetTransform()->SetSize({ 433.f, 84.f });
		ImageRenderer* openingSpace1Render = new ImageRenderer(
			ResourceManager::GetInstance()->LoadResource<Image>(L"SpaceButtonHover", L"/CutScene/SpaceBar/1_2.png")->GetImage(),
			{},
			{},
			{ 1920.f, 1080.f }
		);
		Button* spacebutton = new Button(
			[openingSpace1Render, openingText1Script](BUTTON_EVENT event) {
				if (event == BUTTON_EVENT::DEFAULT) {
					openingText1Script->m_IsButtonHandled = false;

				}
				if (event == BUTTON_EVENT::HOVER) {
					openingText1Script->m_IsButtonHandled = true;
					openingSpace1Render->SetImage(
						ResourceManager::GetInstance()->LoadResource<Image>(L"SpaceButtonHover", L"/CutScene/SpaceBar/1_2.png")->GetImage()
					);

					// Sound
				}
				if (event == BUTTON_EVENT::DOWN) {
					openingText1Script->m_IsButtonHandled = true;
					openingSpace1Render->SetImage(
						ResourceManager::GetInstance()->LoadResource<Image>(L"SpaceButtonDown", L"/CutScene/SpaceBar/1_1.png")->GetImage()
					);
				}
				if (event == BUTTON_EVENT::CLICK) {
					openingText1Script->m_IsButtonHandled = true;
					openingText1Script->BtnCallBack();
				}
			}
		);

		openingText1Script->m_SpaceRenderer = openingSpace1Render;

		opening1Space->AddComponent(spacebutton);
		opening1Space->AddComponent(openingSpace1Render);
		opening1->AddObjectChild(opening1Space);
	}


}

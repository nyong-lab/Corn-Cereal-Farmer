#include "GameOver.h"
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

void GameOver::Enter()
{

	GameObject* gameOver = new GameObject("GameOver", OBJECT_TYPE::UI);
	gameOver->GetTransform()->SetLocalPosition({ 1920.f / 2.f, 1080.f / 2.f });
	gameOver->GetTransform()->SetSize({ 1920.f, 1080.f });
	Panel* gameOverPanel = new Panel();
	ImageRenderer* gameOverRender = new ImageRenderer(
		nullptr,
		{},
		{},
		{ 1920.f, 1080.f }
	);
	gameOver->AddComponent(gameOverPanel);
	gameOver->AddComponent(gameOverRender);
	AddGameObject(gameOver);



	GameObject* gameOverText = new GameObject("gameOverText", OBJECT_TYPE::UI);
	gameOverText->GetTransform()->SetLocalPosition({ 0.f, 255.f });
	Panel* gameOverTextPanel = new Panel();
	TextRenderer* gameOverTextRender = new TextRenderer({},
		L"",
		ResourceManager::GetInstance()->LoadResource<Font>(L"Galmuri9_28", L"/Font/Galmuri9.ttf", L"Galmuri9", 28.f)->Getfont(),
		COLOR::WHITE);
	ResourceManager::GetInstance()->LoadResource<Font>(L"Galmuri9_28")->SetHorizontalAlign(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
	ResourceManager::GetInstance()->LoadResource<Font>(L"Galmuri9_28")->SetVerticalAlign(DWRITE_TEXT_ALIGNMENT_CENTER);
	gameOverTextRender->SetTextAlignMiddle();
	CutSceneScript* gameOverScript = new CutSceneScript;
	gameOverScript->m_TextRenderer = gameOverTextRender;
	gameOverScript->m_ImageRenderer = gameOverRender;

	gameOverScript->m_CutSceneImage.push_back(ResourceManager::GetInstance()->LoadResource<Image>(L"GameOver1", L"/CutScene/GameOver/1.png"));

	gameOverScript->m_Text.push_back(L"<½Ã°ñ ¸¶À»¿¡ ¼û¾îÀÖ´ø>\n<¿¬¼â»ìÀÎ¹ü °Ë°Å>");

	gameOverScript->m_NextSceneName = "StartScene";


	gameOverText->AddComponent(gameOverScript);
	gameOverText->AddComponent(gameOverTextPanel);
	gameOverText->AddComponent(gameOverTextRender);
	gameOver->AddObjectChild(gameOverText);


	{
		GameObject* gameOverSpace = new GameObject("gameOverSpace", OBJECT_TYPE::UI);
		gameOverSpace->GetTransform()->SetLocalPosition({ 700.f, 450.f });
		gameOverSpace->GetTransform()->SetSize({ 433.f, 84.f });
		ImageRenderer* gameOverSpaceRender = new ImageRenderer(
			ResourceManager::GetInstance()->LoadResource<Image>(L"SpaceButtonHover", L"/CutScene/SpaceBar/1_2.png")->GetImage(),
			{},
			{},
			{ 1920.f, 1080.f }
		);
		Button* spacebutton = new Button(
			[gameOverSpaceRender, gameOverScript](BUTTON_EVENT event) {
				if (event == BUTTON_EVENT::DEFAULT) {
					gameOverScript->m_IsButtonHandled = false;

				}
		if (event == BUTTON_EVENT::HOVER) {
			gameOverScript->m_IsButtonHandled = true;
			gameOverSpaceRender->SetImage(
				ResourceManager::GetInstance()->LoadResource<Image>(L"SpaceButtonHover", L"/CutScene/SpaceBar/1_2.png")->GetImage()
			);

			// Sound
		}
		if (event == BUTTON_EVENT::DOWN) {
			gameOverScript->m_IsButtonHandled = true;
			gameOverSpaceRender->SetImage(
				ResourceManager::GetInstance()->LoadResource<Image>(L"SpaceButtonDown", L"/CutScene/SpaceBar/1_1.png")->GetImage()
			);
		}
		if (event == BUTTON_EVENT::CLICK) {
			gameOverScript->m_IsButtonHandled = true;
			gameOverScript->BtnCallBack();
		}
			}
		);

		gameOverScript->m_SpaceRenderer = gameOverSpaceRender;

		gameOverSpace->AddComponent(spacebutton);
		gameOverSpace->AddComponent(gameOverSpaceRender);
		gameOver->AddObjectChild(gameOverSpace);
	}

}

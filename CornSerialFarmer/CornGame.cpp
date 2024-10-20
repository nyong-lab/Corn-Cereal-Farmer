#include "CornGame.h"
#include "Panel.h"
#include "Define.h"
#include "../Math/Vector2.h"
#include "Transform.h"
#include "Image.h"
#include "ImageRenderer.h"
#include "ResourceManager.h"
#include "CornGameManagerScript.h"
#include "MiniGameCornScipt.h"
#include "CountDown.h"
#include "Animator.h"
#include "Animation.h"

CornGame::CornGame() :
	GameObject("CornGame", OBJECT_TYPE::UI)
{
	GetTransform()->SetLocalPosition(Vector2{ 1920.f * 0.5f, 1080.f * 0.5f });

	/// <summary>
	/// ∏ﬁ¿Œ
	/// </summary>
	GetTransform()->SetSize(Vector2{ 900, 700 });
	UI* panel = new Panel;
	AddComponent(panel);
	ImageRenderer* cornGameRender= new ImageRenderer(
		ResourceManager::GetInstance()->LoadResource<Image>(L"CornGameImage", L"/Minigame/mini_game_1.png")->GetImage(),
		{}, {}, GetTransform()->GetSize());
	AddComponent(cornGameRender);
	

	GameObject* alternativeBG = new GameObject("CornGame2", OBJECT_TYPE::UI);
	alternativeBG->GetTransform()->SetSize(Vector2{ 900, 700 });
	UI* panel2 = new Panel;
	alternativeBG->AddComponent(panel2);
	ImageRenderer* cornGameRender2 = new ImageRenderer(
		ResourceManager::GetInstance()->LoadResource<Image>(L"CornGameImage2", L"/Minigame/mini_game_2.png")->GetImage(),
		{}, {}, alternativeBG->GetTransform()->GetSize());
	cornGameRender2->SetOpacity(0.f);
	alternativeBG->AddComponent(cornGameRender2);
	AddObjectChild(alternativeBG);



	
	GameObject* cornGameManager = new GameObject("CornGameManager", OBJECT_TYPE::DEFAULT);
	CornGameManagerScript* cornGameManagerScript = new CornGameManagerScript;
	cornGameManagerScript->m_Renderer = cornGameRender2;
	cornGameManager->AddComponent(cornGameManagerScript);
	this->AddObjectChild(cornGameManager);

	for (int i = 0; i < 4; ++i)
	{
		GameObject* corn = new GameObject("Corn", OBJECT_TYPE::DEFAULT);
		corn->GetTransform()->SetSize({ 96.f, 96.f });
		MiniGameCornScipt* cornScript = new MiniGameCornScipt;
		ImageRenderer* cornRender = new ImageRenderer(
			ResourceManager::GetInstance()->LoadResource<Image>(L"CornFocusImage", L"/Image/item/cornFocus.png")->GetImage(),
			{}, {}, corn->GetTransform()->GetSize());

		corn->AddComponent(cornScript);
		corn->AddComponent(cornRender);

		Vector2 pos = {};
		if (i == 0) pos = Vector2(-200, 140);
		else if (i == 1) pos = Vector2(-300, 50);
		else if (i == 2) pos = Vector2(100, -93);
		else if (i == 3) pos = Vector2(-30, 83);

		cornScript->GetTransform()->SetLocalPosition(pos);
		
		cornScript->m_Renderer = cornRender;
		this->AddObjectChild(corn);

		
	}

	CountDown* countDown = new CountDown;
	countDown->GetTransform()->SetLocalPosition({ 0.f, -450.f });
	AddObjectChild(countDown);

	/// Explain Text
	GameObject* explainCornGameText = new GameObject("ExplainCornGameText", OBJECT_TYPE::UI);
	explainCornGameText->GetTransform()->SetLocalPosition(Vector2(0.f, -20.f));
	explainCornGameText->GetTransform()->SetSize(Vector2(900, 700));
	// Image
	ImageRenderer* cornGameText = new ImageRenderer(
		ResourceManager::GetInstance()->LoadResource<Image>(L"ExplainCornGameText", L"/Minigame/mini_game_Text1.png")->GetImage());
	explainCornGameText->AddComponent(cornGameText);
	// Add Object
	AddObjectChild(explainCornGameText);


	/// Explain Animation1
	GameObject* explainCornGame = new GameObject("ExplainCornGame", OBJECT_TYPE::UI);
	explainCornGame->GetTransform()->SetLocalPosition(Vector2(600.f, -200.f));
	explainCornGame->GetTransform()->SetSize(Vector2(188.f, 176.f));
	// Animator
	Animator* cornGameAnimator = new Animator(
		ResourceManager::GetInstance()->LoadResource<Image>(L"ExplainCornGame", L"/Minigame/mini_game_click_sheet.png")->GetImage());
	cornGameAnimator->CreateAnimation(L"CornClickAnimation", Vector2(0, 0), Vector2(188, 176), Vector2(0, 0), Vector2(188, 0), 0.2f, 4);
	cornGameAnimator->Play(L"CornClickAnimation", true);
	explainCornGame->AddComponent(cornGameAnimator);
	// Add Object
	AddObjectChild(explainCornGame);


	/// Explain Animation2
	GameObject* explainCornGame2 = new GameObject("ExplainCornGame2", OBJECT_TYPE::UI);
	explainCornGame2->GetTransform()->SetLocalPosition(Vector2(300.f, -50.f));
	explainCornGame2->GetTransform()->SetSize(Vector2(138.f, 176.f));
	// Animator
	Animator* cornGameAnimator2 = new Animator(
		ResourceManager::GetInstance()->LoadResource<Image>(L"ExplainCornGame2", L"/Minigame/mini_game_A2.png")->GetImage());
	cornGameAnimator2->CreateAnimation(L"CornPushAnimation", Vector2(0, 0), Vector2(138, 176), Vector2(0, 0), Vector2(138, 0), 0.15f, 7);
	cornGameAnimator2->Play(L"CornPushAnimation", true);
	explainCornGame2->AddComponent(cornGameAnimator2);
	// Add Object
	AddObjectChild(explainCornGame2);
}

CornGame::~CornGame()
{

}

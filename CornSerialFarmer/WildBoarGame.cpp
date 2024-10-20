#include "WildBoarGame.h"
#include "Panel.h"
#include "Define.h"
#include "../Math/Vector2.h"
#include "Transform.h"
#include "PrimitiveRenderer.h"
#include "MonoBehaviour.h"
#include "ImageRenderer.h"
#include "ResourceManager.h"
#include "Image.h"
#include "Animator.h"
#include "WildBoarCatchScript.h"
#include "CountDown.h"

WildBoarGame::WildBoarGame() :
	GameObject("WildBoarGame", OBJECT_TYPE::UI)
{
	GetTransform()->SetLocalPosition(Vector2{ 1920.f * 0.5f, 1080.f * 0.5f });

	GetTransform()->SetSize(Vector2{ 900.f, 700.f });
	UI* panel = new Panel;
	AddComponent(panel);
	ImageRenderer* WildBoarGameImage = new ImageRenderer(
		ResourceManager::GetInstance()->LoadResource<Image>(L"WildBoarGameImage", L"/Minigame/mini_game_3.png")->GetImage(),
		{}, {}, GetTransform()->GetSize());
	AddComponent(WildBoarGameImage);




	GameObject* wildBoar = new GameObject("WildBoar", OBJECT_TYPE::UI);
	wildBoar->GetTransform()->SetSize({ 176, 124 });
	Animator* animator = new Animator(ResourceManager::GetInstance()->LoadResource<Image>(L"WildBoar", L"/Minigame/wild_boar.png")->GetImage());
	wildBoar->AddComponent(animator);
	animator->CreateAnimation(L"BoarLeft", Vector2(0, 0), Vector2(176, 124), Vector2(0, 0), Vector2(176, 0), 0.1f, 4);
	animator->CreateAnimation(L"BoarRight", Vector2(0, 0), Vector2(176, 124), Vector2(0, 124), Vector2(176, 0), 0.1f, 4);




	animator->Play(L"BoarLeft", true);
	WildBoarCatchScript* wbcScript = new WildBoarCatchScript;
	wbcScript->m_Anim = animator;
	wildBoar->AddComponent(wbcScript);
	AddObjectChild(wildBoar);


	{
		GameObject* hitEffect = new GameObject("HitEffectObj", OBJECT_TYPE::UI);
		hitEffect->GetTransform()->SetSize({ 252, 252 });

		Animator* hitAnim = new Animator(ResourceManager::GetInstance()->LoadResource<Image>(L"boar_effect", L"/Minigame/boar_effect.png")->GetImage());
		hitAnim->CreateAnimation(L"HitEffect", {}, Vector2(252, 252), Vector2(0, 0), Vector2(252, 0), 0.05f, 6);
		hitEffect->AddComponent(hitAnim);
		AddObjectChild(hitEffect);

		wbcScript->m_HitAnim = hitAnim;
	}


	CountDown* countDown = new CountDown;
	countDown->GetTransform()->SetLocalPosition({ 0.f, -450.f });
	AddObjectChild(countDown);

	/// Explain Text
	GameObject* explainWildBoarGameText = new GameObject("ExplainWildBoarGameText", OBJECT_TYPE::UI);
	explainWildBoarGameText->GetTransform()->SetLocalPosition(Vector2(0.f, -20.f));
	explainWildBoarGameText->GetTransform()->SetSize(Vector2(900, 700));
	// Image
	ImageRenderer* wildBoarGameText = new ImageRenderer(
		ResourceManager::GetInstance()->LoadResource<Image>(L"ExplainWildBoarGameText", L"/Minigame/mini_game_Text3.png")->GetImage());
	explainWildBoarGameText->AddComponent(wildBoarGameText);
	// Add Object
	AddObjectChild(explainWildBoarGameText);


	/// Explain Animation
	GameObject* explainWildBoarGame = new GameObject("ExplainWildBoarGame", OBJECT_TYPE::UI);
	explainWildBoarGame->GetTransform()->SetLocalPosition(Vector2(600.f, -200.f));
	explainWildBoarGame->GetTransform()->SetSize(Vector2(188.f, 176.f));
	// Animator
	Animator* WildBoarGameAnimator = new Animator(
		ResourceManager::GetInstance()->LoadResource<Image>(L"ExplainWildBoarGame", L"/Minigame/mini_game_click_sheet.png")->GetImage());
	WildBoarGameAnimator->CreateAnimation(L"WildBoarClickAnimation", Vector2(0, 0), Vector2(188, 176), Vector2(0, 0), Vector2(188, 0), 0.2f, 4);
	WildBoarGameAnimator->Play(L"WildBoarClickAnimation", true);
	explainWildBoarGame->AddComponent(WildBoarGameAnimator);
	// Add Object
	AddObjectChild(explainWildBoarGame);

}

WildBoarGame::~WildBoarGame()
{

}

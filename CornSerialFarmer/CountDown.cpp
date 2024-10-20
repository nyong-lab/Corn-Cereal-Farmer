#include "CountDown.h"
#include "Panel.h"
#include "Define.h"
#include "../Math/Vector2.h"
#include "Transform.h"
#include "Image.h"
#include "ImageRenderer.h"
#include "ResourceManager.h"
#include "CornGameManagerScript.h"
#include "MiniGameCornScipt.h"
#include "Animator.h"
#include "CountDownScript.h"

CountDown::CountDown()
	: GameObject("CountDown", OBJECT_TYPE::UI)
{


	GetTransform()->SetSize(Vector2{ 112.f, 108.f });
	UI* panel = new Panel;
	AddComponent(panel);
	Animator* animator = new Animator(ResourceManager::GetInstance()->LoadResource<Image>(L"cooltime_mark", L"/Minigame/cooltime_mark.png")->GetImage());
	AddComponent(animator);
	animator->CreateAnimation(L"CountDownAnim", Vector2(0, 0), 
		Vector2(112.f, 108.f), 
		Vector2(2128.f, 0.f),
		Vector2(-112.f, 0), 
		0.25f, 20);
	CountDownScript* cdScript = new CountDownScript;
	cdScript->m_Animator = animator;
	AddComponent(cdScript);

}

CountDown::~CountDown()
{

}

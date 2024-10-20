#include "BlackCatScript.h"
#include "Transform.h"
#include "EventManager.h"
#include "Input.h"
#include "GameObject.h"

#include <typeinfo>
#include "../GraphicsEngine/GraphicsEngine.h"

#include "StateMachine.h"
#include "BlackCatFSM.h"

#include "Sound.h"
#include "SoundManager.h"
#include "ResourceManager.h"

BlackCatScript::BlackCatScript()
	: MonoBehaviour(typeid(this).name())
	, m_BlackCatStateMachine(nullptr)
	, directionCheck(0)
	, detailState("IdleFront")
	, blackCatState("BlackCatIdle")
	, count(0)
	, timeCount(0)
	, randomDirection(0)
	, isSave(false)
{
}

BlackCatScript::~BlackCatScript()
{	

}

void BlackCatScript::Start()
{
	Vector2 pos{ 0,0 };
	GetTransform()->SetLocalPosition(pos);

	m_BlackCatStateMachine = new BlackCatFSM(GetGameObject());

	//필요한 이벤트 메니저 생성
}

void BlackCatScript::Update(float deltaTime)
{
	if (count > 100)
	{
		randomDirection = rand() % 5;
		count = 0;
	}

	if (randomDirection == 0)
	{
		detailState = "MoveBack";
		blackCatState = "BlackCatMove";
		directionCheck = 0;
	}
		
	if (randomDirection == 1)
	{
		detailState = "MoveFront";
		blackCatState = "BlackCatMove";
		directionCheck = 1;
	}
	if (randomDirection == 2)
	{
		detailState = "MoveLeft";
		blackCatState = "BlackCatMove";
		directionCheck = 2;
	}
	if (randomDirection == 3)
	{
		detailState = "MoveRight";
		blackCatState = "BlackCatMove";
		directionCheck = 3;
	}
	if (randomDirection == 4)
	{
		blackCatState = "BlackCatIdle";
	}

	if (blackCatState.compare("BlackCatIdle") == 0)
	{
		if (directionCheck == 0)
			detailState = "IdleBack";
		else if (directionCheck == 1)
			detailState = "IdleFront";
		else if (directionCheck == 2)
			detailState = "IdleLeft";
		else if (directionCheck == 3)
			detailState = "IdleRight";
	}

	if (isSave == true)
	{
		blackCatState = "BlackCatIdle";
		detailState = "IdleFront";
		timeCount += deltaTime;
		
		if (action)
		{
			GetGameObject()->GetObjectChild("blackCatChild")->SetActivate(true);
			SoundManager::GetInstance()->PlaySoundSFX(
				ResourceManager::GetInstance()->LoadResource<Sound>(L"CatMeowSFX", L"/Sound/SFX/Interaction/Cat_Meow.mp3")->GetSound());
			action = false;
		}

	

		if (timeCount > 2)
		{
			//action = true;
			isSave = false;
			timeCount = 0;
			GetGameObject()->GetObjectChild("blackCatChild")->SetActivate(false);
		}
	}

	count++;

	m_BlackCatStateMachine->ChangeDetailState(detailState);
	m_BlackCatStateMachine->ChangeState(blackCatState);
	m_BlackCatStateMachine->Update(deltaTime);
}

void BlackCatScript::FixedUpdate(float deltaTime)
{
}

void BlackCatScript::Finalize()
{
	m_BlackCatStateMachine->Finalize();
	delete m_BlackCatStateMachine;
}

void BlackCatScript::OnCollisionEnter(const Manifold& collision)
{
}

void BlackCatScript::OnCollisionStay(const Manifold& collision)
{
}

void BlackCatScript::OnCollisionExit(const Manifold& collision)
{
}

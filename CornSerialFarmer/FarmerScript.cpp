#include "FarmerScript.h"

#include "Transform.h"
#include "Animator.h"
#include "Animation.h"
#include "EventManager.h"
#include "TextRenderer.h"
#include "GameObject.h"
#include "Input.h"
#include <typeinfo>
#include "../GraphicsEngine/GraphicsEngine.h"

#include "TestFSM.h"

#include "MonoBehaviour.h"
#include "NPC1Script.h"
#include "ObjectDataScript.h"
#include "Camera.h"

#include "BlackCatScript.h"
#include "GameManagerScript.h"
#include "TextManagerScript.h"
#include "QuestManagerScript.h"
#include "Scene.h"

#include "FarmScript.h"

// Sound
#include "ResourceManager.h"
#include "SoundManager.h"
#include "Sound.h"

FarmerScript::FarmerScript()
	: MonoBehaviour(typeid(this).name())
	, speed(500)
	, diagonalSpeed(300)
	, timeCount(0)
	, m_FarmerStateMachine(nullptr)
	, directionCheck(4)
	, Farmerstate("Idle")
	, detailState("IdleFront")
	, collisionCheck(false)
	, deadBodyCollisionCheck(false)
	, farmCollisionCheck(false)
	, buildingCollisionCheck(false)
	, isWatering(false)
	, isPlayerTalkingState(false)
	, isNPCTalking(false)
	, haveDeadBody(false)
	, hideDeadBody(false)
	, isGameOver(false)
	, isMorning(true)
	, isNight(true)
	, m_ScriptMapKey("")
	, textOut(L"")
	, manager(nullptr)
	, isInterection(false)
	, isHarvest(false)
	, textManager(nullptr)
{

}

FarmerScript::~FarmerScript()
{
	
}

void FarmerScript::Start()
{
	Vector2 pos{ 360.f, 0.f };
	sponPos = Vector2(360.f, 200.f);
	GetTransform()->SetLocalPosition(pos);

	Vector2 scale{ 1,1 };
	GetTransform()->SetLocalScale(scale);

	//FSM초기화
	m_FarmerStateMachine = new TestFSM(GetGameObject());

	// 이벤트
	EventManager::GetInstance()->RegisterClient("FarmerWatering", MakeCallInfo(&FarmerScript::FarmerWatering));
	EventManager::GetInstance()->RegisterClient("FarmerInteraction", MakeCallInfo(&FarmerScript::FarmerInteraction));
	EventManager::GetInstance()->RegisterClient("FarmerHarvest", MakeCallInfo(&FarmerScript::FarmerHarvest));
}

void FarmerScript::Update(float deltaTime)
{
	Farmerstate = "Idle";
	speed = 800;
	diagonalSpeed = speed / 1.414f;

	if (Input::GetKey(KEY::D))
	{
		Farmerstate = "Walk";
		detailState = "WalkRight";
		directionCheck = 1;
	}
	if (Input::GetKey(KEY::A))
	{
		Farmerstate = "Walk";
		detailState = "WalkLeft";
		directionCheck = 2;
	}
	if (Input::GetKey(KEY::W))
	{
		Farmerstate = "Walk";
		detailState = "WalkBack";
		directionCheck = 3;
	}
	if (Input::GetKey(KEY::S))
	{
		Farmerstate = "Walk";
		detailState = "WalkFront";
		directionCheck = 4;
	}

	//대각선 움직임
	if (Input::GetKey(KEY::S) && Input::GetKey(KEY::A))
	{
		Farmerstate = "Walk";
		detailState = "WalkDownLeft";
		directionCheck = 2;
	}

	if (Input::GetKey(KEY::S) && Input::GetKey(KEY::D))
	{
		Farmerstate = "Walk";
		detailState = "WalkDownRight";
		directionCheck = 1;
	}
	if (Input::GetKey(KEY::W) && Input::GetKey(KEY::A))
	{
		Farmerstate = "Walk";
		detailState = "WalkUpLeft";
		directionCheck = 2;
	}
	if (Input::GetKey(KEY::W) && Input::GetKey(KEY::D))
	{
		Farmerstate = "Walk";
		detailState = "WalkUpRight";
		directionCheck = 1;
	}

	if (Farmerstate.compare("Idle") == 0)
	{
		if (directionCheck == 1)
			detailState = "IdleRight";
		if (directionCheck == 2)
			detailState = "IdleLeft";
		if (directionCheck == 3)
			detailState = "IdleBack";
		if (directionCheck == 4)
			detailState = "IdleFront";
	}

	if (isWatering == true && isNPCTalking == false)
	{
		Farmerstate = "Watering";
		if (dynamic_cast<Animator*>(GetGameObject()->GetComponent<Animator>())->FindAnimation(L"farmerWatering")->IsAnimationFinished() == true)
		{
			isWatering = false;
			Farmerstate = "Idle";
			dynamic_cast<Animator*>(GetGameObject()->GetComponent<Animator>())->FindAnimation(L"farmerWatering")->SetFrame(0);
		}
	}

	if (isHarvest == true)
	{
		Farmerstate = "Harvest";
		if (dynamic_cast<Animator*>(GetGameObject()->GetComponent<Animator>())->FindAnimation(L"farmerHarvest")->IsAnimationFinished() == true)
		{
			isHarvest = false;
			Farmerstate = "Idle";
			dynamic_cast<Animator*>(GetGameObject()->GetComponent<Animator>())->FindAnimation(L"farmerHarvest")->SetFrame(0);
		}
	}

	if (isInterection == true)
	{
		Farmerstate = "Interaction";
		if (dynamic_cast<Animator*>(GetGameObject()->GetComponent<Animator>())->FindAnimation(L"farmerInteraction")->IsAnimationFinished() == true)
		{
			isInterection = false;
			Farmerstate = "Idle";
			dynamic_cast<Animator*>(GetGameObject()->GetComponent<Animator>())->FindAnimation(L"farmerInteraction")->SetFrame(0);
		}
	}

	//시체 끌기 이벤트
	if (haveDeadBody == true)
	{
		Farmerstate = "MoveBody";
		speed = 300;
		diagonalSpeed = speed / 1.414f;

		timeCount += deltaTime;

		if (timeCount > 7)
		{
			speed = 100;
			diagonalSpeed = speed / 1.414f;
			textOut = L"시체가 너무 \n 무거워...";
		}
		
	}

	//대화상태 진입
	if (isNPCTalking == true)
	{
		Farmerstate = "Idle";

		if (isPlayerTalkingState == true)
		{
			int num = directionCheck % 3;
			textOut = textManager->ScriptMap[m_ScriptMapKey][num];
			Farmerstate = "Talk";
		}

	}
	if (manager->isMorning == true)
	{
		//시체를 가지고 있을 경우, 게임오버
		if (haveDeadBody == true)
		{
			manager->m_IsGameOver = true;
		}
	}

	if (manager->m_IsDay == false && isNight == true )
	{
		isNight = false;
		isMorning = true;
		
		//필요한 초기화
		Farmerstate = "Idle";
		isNPCTalking = false;
		isPlayerTalkingState = false;
		isWatering = false;
		isHarvest = false;
		isInterection = false;
		speed = 500;
		diagonalSpeed = 300;

	}
	if (manager->m_IsDay == true && isMorning == true && manager->isMorning == false)
	{
		isNight = true;
		isMorning = false;

		GetTransform()->SetLocalPosition(sponPos);
	
		//필요한 초기화
		Farmerstate = "Idle";
		isNPCTalking = false;
		isPlayerTalkingState = false;
		isWatering = false;
		isHarvest = false;
		isInterection = false;

	}

	//게임오버 당함
	if (isGameOver == true)
	{
		Farmerstate = "Idle";
	}

	m_FarmerStateMachine->ChangeDetailState(detailState);
	m_FarmerStateMachine->ChangeState(Farmerstate);
	m_FarmerStateMachine->Update(deltaTime);

	// 시체 숨길 수 있다는 화살표 상호작용 띄우냐 마냐 
	if (manager->m_IsDay == false)
	{
		if (haveDeadBody)
		{
			for (auto& object : manager->m_QuestManager->m_QuestObjects)
			{
				if (object->GetName() != "CatBowl" && object->GetName() != "Tree")
				{
					for (auto& objectChild : object->GetObjectChildren())
					{
						if (objectChild->GetObjectType() == OBJECT_TYPE::INTERACTION_ARROW)
						{
							objectChild->SetActivate(true);
						}
					}
				}
			}
		}
		else
		{
			for (auto& object : manager->m_QuestManager->m_QuestObjects)
			{
				if (object->GetName() != "CatBowl" && object->GetName() != "Tree")
				{
					for (auto& objectChild : object->GetObjectChildren())
					{
						if (objectChild->GetObjectType() == OBJECT_TYPE::INTERACTION_ARROW)
						{
							objectChild->SetActivate(false);
						}
					}
				}
			}
		}
	}
	

	if (Input::GetKeyDown(KEY::H))
	{
		GetTransform()->SetLocalPosition(sponPos);
		Farmerstate = "Walk";
		isNPCTalking = false;
		isPlayerTalkingState = false;

	}
}

void FarmerScript::FixedUpdate(float deltaTime)
{

}

void FarmerScript::Finalize()
{
	m_FarmerStateMachine->Finalize();
	delete m_FarmerStateMachine;
}


void FarmerScript::OnCollisionEnter(const Manifold& collision)
{
	collisionCheck = true;

 	if (collision.otherObject->GetObjectType() == OBJECT_TYPE::BUILDING || collision.otherObject->GetObjectType() == OBJECT_TYPE::NPC || collision.otherObject->GetObjectType() == OBJECT_TYPE::ADDITINAL)
 	{
		string stringObjectKey = collision.otherObject->GetName();

		if (stringObjectKey.compare("police1") != 0 && stringObjectKey.compare("police2") != 0 && stringObjectKey.compare("police3") != 0 && stringObjectKey.compare("police4") != 0)
		{
			// Explain Window
			if (stringObjectKey == "Pond" && dynamic_cast<ObjectDataScript*>(collision.otherObject->GetComponent<MonoBehaviour>())->inabilityGetWater)
			{
				wstring texts = textManager->explainMap[stringObjectKey][1];
				EventManager::GetInstance()->SendEvent("ShowExplainWindow", texts);
			}
			else
			{
				wstring texts = textManager->explainMap[stringObjectKey][0];
				EventManager::GetInstance()->SendEvent("ShowExplainWindow", texts);
			}
		}
	}
}

void FarmerScript::OnCollisionStay(const Manifold& collision)
{
	if (Input::GetKeyDown(KEY::SPACE))
	{
		if (collision.otherObject->GetObjectParent())
		{
			if (collision.otherObject->GetObjectParent()->GetName() == "blackCat")
			{
				if (collision.otherObject->GetObjectParent()->GetActivate())
				{
					dynamic_cast<BlackCatScript*>(collision.otherObject->GetObjectParent()->GetComponent<MonoBehaviour>())->isSave = true;
					dynamic_cast<BlackCatScript*>(collision.otherObject->GetObjectParent()->GetComponent<MonoBehaviour>())->action = true;
				}
			}
		}
	
		if (collision.otherObject->GetObjectType() != OBJECT_TYPE::FARM)
		{
			for (auto& iter : manager->m_QuestManager->m_QuestObjects)
			{
				if (iter == collision.otherObject)
				{
					if (manager->m_IsDay == false)
					{
						// 집에 시체 있나 확인
						if (dynamic_cast<ObjectDataScript*>(iter->GetComponent<MonoBehaviour>())->isDeadBodyHave == true && haveDeadBody == false)
						{
							haveDeadBody = true;
							dynamic_cast<ObjectDataScript*>(iter->GetComponent<MonoBehaviour>())->isDeadBodyHave = false; //시체 집에 없음
							collision.otherObject->GetObjectChild("houseTextBubble")->SetActivate(false);	//말풍선 없앰
						}

						//시체 옮김
						else if (dynamic_cast<ObjectDataScript*>(iter->GetComponent<MonoBehaviour>())->isDeadBodyHave == false && haveDeadBody == true && iter->GetName().compare("CatBowl") != 0 && iter->GetName().compare("Tree") != 0 && iter->GetName().compare("wildBoarChild") != 0)
						{
							haveDeadBody = false;
							collision.otherObject->GetObjectChild("houseTextBubble")->SetActivate(true); // 시체 집에 있음
							dynamic_cast<ObjectDataScript*>(collision.otherObject->GetComponent<MonoBehaviour>())->isDeadBodyHave = true;	//말풍선 생김
							manager->m_DeadBodySpot = GetTransform()->GetLocalPosition();
							timeCount = 0;
						}
					}

					break;
				}
			}

			/// 밭 관련 퀘스트는 플레이어 에임으로 관리한다. (리지드 바디 + 밭 선택 조작감)
			// 밭 제외 퀘스트 관련
			for (auto& iter : manager->m_QuestManager->m_QuestObjects)
			{
				if (iter == collision.otherObject)
				{
					manager->Interaction(collision.otherObject);
					break;
				}
			}
		}
	}
}

void FarmerScript::OnCollisionExit(const Manifold& collision)
{
	collisionCheck = false;
	deadBodyCollisionCheck = false;
	farmCollisionCheck = false;
	buildingCollisionCheck = false;
	isNPCTalking = false;
	

	// Explain Window
	wstring texts = L"";
	EventManager::GetInstance()->SendEvent("ShowExplainWindow", texts);

	GetGameObject()->GetObjectChild("farmerTextBubble")->SetActivate(false);
}

void FarmerScript::FarmerWatering(std::any)
{
	isWatering = true;
}

void FarmerScript::FarmerInteraction(std::any)
{
	isInterection = true;
}

void FarmerScript::FarmerHarvest(std::any)
{
	isHarvest = true;
}

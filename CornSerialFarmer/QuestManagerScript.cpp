#include "QuestManagerScript.h"


#include <random>
#include <cassert>

#include "../GraphicsEngine/GraphicsEngine.h"
#include "TextRenderer.h"
#include "ImageRenderer.h"
#include "Image.h"

#include "ResourceManager.h"

#include "GameObject.h"
#include "Scene.h"
#include "MainScene.h"
#include "Transform.h"

#include "ItemSlot.h"
#include "QuestList.h"

#include "ItemManagerScript.h"
#include "GameManagerScript.h"
#include "FarmScript.h"
#include "FarmerScript.h"
#include "WildBoarScript.h"
#include "ObjectDataScript.h"
#include "BlackCatScript.h"
#include "Animator.h"
#include "TextManagerScript.h"

#include "EventManager.h"
#include "SoundManager.h"
#include "Sound.h"

#include "ZicoMath.h"

#include "CameraScript.h"
#include "Animation.h"
#include "GameplayStatics.h"


QuestManagerScript::QuestManagerScript()
	: MonoBehaviour(typeid(this).name())
	, m_IsCornQuestStepUp(false)
	, m_QuestUiList(nullptr)
	, m_ItemManager(nullptr)
	, m_QuestUiIndex(0)
	, m_InteractionCount(0)
	, m_QuestItemList{ 0, }
	, m_questReset(false)
	, m_CornQuestCount(1)
	, m_FailWildBoar(false)
	, m_ApplyFarm(true)
	, m_CatObject(nullptr)
	, m_PondObject(nullptr)
	, m_Player(nullptr)
	, m_SaveCat(true)
	, m_WildBoar(nullptr)
	, m_Camera(nullptr)
	, m_CompleteAllActiveQuests(false)
{

}

QuestManagerScript::~QuestManagerScript()
{

}


/// 오브젝트 ID 
/// 
/// 창고A : 1000
/// 창고B : 2000
///	창고C : 3000
/// 창고D : 4000
/// 집 : 5000
/// 밭 : 6000 
/// 연못 : 7000   
/// 나무 : 8000
/// 고양이 밥통: 9000
/// 맷돼지 : 10000
/// 
void QuestManagerScript::Start()
{
	// 옥수수 퀘스트
	m_QuestList.insert(make_pair(10, QuestData("옥수수 밭에 씨 뿌리기 1단계", { 1000 })));	//창고A
	m_QuestList.insert(make_pair(11, QuestData("옥수수 밭에 씨 뿌리기 2단계", { 6000 })));	//밭

	//m_QuestList.insert(make_pair(20, QuestData("옥수수 밭의 잡초 뽑기", { 6000 })));	//밭

	m_QuestList.insert(make_pair(30, QuestData("옥수수 밭에 비료 주기 1단계", { 4000 })));	//창고D
	m_QuestList.insert(make_pair(31, QuestData("옥수수 밭에 비료 주기 2단계", { 6000 })));	//밭

	m_QuestList.insert(make_pair(40, QuestData("옥수수 밭에 물 주기 1단계", { 2000 })));	//창고B
	m_QuestList.insert(make_pair(41, QuestData("옥수수 밭에 물 주기 2단계", { 7000 })));	//연못
	m_QuestList.insert(make_pair(42, QuestData("옥수수 밭에 물 주기 3단계", { 6000 })));	//밭

	m_QuestList.insert(make_pair(50, QuestData("옥수수 수확하기 1단계", { 3000 })));	//창고C
	m_QuestList.insert(make_pair(51, QuestData("옥수수 수확하기 2단계", { 6000 })));	//밭

	// 잡일 퀘스트
	m_QuestList.insert(make_pair(60, QuestData("뗄감 보충하기 1단계", { 4000 })));	 // 창고D
	m_QuestList.insert(make_pair(61, QuestData("뗄감 보충하기 2단계", { 8000 })));	 // 나무
	m_QuestList.insert(make_pair(62, QuestData("뗄감 보충하기 3단계", { 5000 })));	 // 집

	m_QuestList.insert(make_pair(70, QuestData("창고 정리하기", { 1000 })));	// 창고A

	m_QuestList.insert(make_pair(80, QuestData("고양이 밥 주기 1단계", { 5000 })));	// 집
	m_QuestList.insert(make_pair(81, QuestData("고양이 밥 주기 2단계", { 9000 })));	// 고양이

	m_QuestList.insert(make_pair(90, QuestData("창고 문 열기 1단계", { 5000 })));	// 집
	m_QuestList.insert(make_pair(91, QuestData("창고 문 열기 2단계", { 3000 })));	// 창고C

	// 긴급 퀘스트
	m_QuestList.insert(make_pair(100, QuestData("고양이 구하기", { 7000 })));	// 연못

	// 밤 퀘스트
	m_QuestList.insert(make_pair(999, QuestData("경찰의 눈을 피해서 시체 숨기기", { 100000 })));
	m_QuestList.insert(make_pair(1000, QuestData("맷돼지 쫒아내기", { 10000 })));	//맷돼지

	// 이벤트 임시.
	EventManager::GetInstance()->RegisterClient("WildBoarClear", MakeCallInfo(&QuestManagerScript::WildBoarClear));
	EventManager::GetInstance()->RegisterClient("WildBoarFail", MakeCallInfo(&QuestManagerScript::WildBoarFail));
	EventManager::GetInstance()->RegisterClient("WareHouseClear", MakeCallInfo(&QuestManagerScript::WareHouseClear));
	EventManager::GetInstance()->RegisterClient("WareHouseFail", MakeCallInfo(&QuestManagerScript::WareHouseFail));
	EventManager::GetInstance()->RegisterClient("CornGameClear", MakeCallInfo(&QuestManagerScript::CornGameClear));
	EventManager::GetInstance()->RegisterClient("CornGameFail", MakeCallInfo(&QuestManagerScript::CornGameFail));
}

void QuestManagerScript::Update(float deltaTime)
{
	/*for (auto& questObject : m_QuestObjects)
	{
		for (auto& activeQuest : m_ActiveQuests)
		{
			if (dynamic_cast<ObjectDataScript*>(questObject->GetComponent<MonoBehaviour>())->id == activeQuest.second.objectId)
			{
				for (auto& questObjectChild : questObject->GetObjectChildren())
				{
					if (questObjectChild->GetObjectType() == OBJECT_TYPE::INTERACTION_ARROW)
					{
						questObjectChild->SetActivate(true);
					}
				}
			}
		}
	}*/
}

void QuestManagerScript::Finalize()
{
	for (auto& itemIter : m_QuestItemList)
	{
		if (itemIter != nullptr)
		{
			delete itemIter;
			itemIter = nullptr;
		}
	}
}


void QuestManagerScript::WildBoarClear(std::any)
{
	// 미니 게임 성공 시 
	m_ApplyFarm = true;

	++(m_ActiveQuests.find(1000)->second.questStep);

	if (m_ActiveQuests.find(1000)->second.questStep == m_ActiveQuests.find(1000)->second.maxQuestStep)
	{
		m_ActiveQuests.find(1000)->second.isComplete = true;

		m_QuestUiList->m_CheckBoxImage[m_ActiveQuests.find(1000)->second.uiOrder]->SetImage
		(
			ResourceManager::GetInstance()->LoadResource<Image>(L"Check", L"/UI/check.png")->GetImage()
		);
	}
	else
	{
		m_ActiveQuests.find(1000)->second.objectId = m_QuestList[1000 + 1].objectId;
	}


	dynamic_cast<WildBoarScript*>(m_WildBoar->GetComponent<MonoBehaviour>())->m_IsClear = true;

	m_WildBoar->SetActivate(true);
}

void QuestManagerScript::WildBoarFail(std::any)
{
	m_WildBoar->SetActivate(true);
	m_WildBoar->GetObjectChild("wildBoarExclamationMark")->SetActivate(true);
}

void QuestManagerScript::WareHouseClear(std::any)
{
	// 키 삭제
	m_ItemManager->DeleteItem(KEY_);
	KEY_ = nullptr;

	m_ItemManager->ApplyItemSlot();

	++(m_ActiveQuests.find(90)->second.questStep);

	if (m_ActiveQuests.find(90)->second.questStep == m_ActiveQuests.find(90)->second.maxQuestStep)
	{
		m_ActiveQuests.find(90)->second.isComplete = true;

		m_QuestUiList->m_CheckBoxImage[m_ActiveQuests.find(90)->second.uiOrder]->SetImage
		(
			ResourceManager::GetInstance()->LoadResource<Image>(L"Check", L"/UI/check.png")->GetImage()
		);
	}
	else
	{
		m_ActiveQuests.find(90)->second.objectId = m_QuestList[91 + 1].objectId;
	}


	for (auto& object : m_QuestObjects)
	{
		if (object->GetName() == "WarehouseC")
		{
			if (dynamic_cast<ObjectDataScript*>(object->GetComponent<MonoBehaviour>())->interactionArrowCount == 0)
			{
				object->GetObjectChild("warehouseCInteractionArrow")->SetActivate(false);
				break;
			}
			else
			{
				--(dynamic_cast<ObjectDataScript*>(object->GetComponent<MonoBehaviour>())->interactionArrowCount);
			}
		}
	}

}

void QuestManagerScript::WareHouseFail(std::any)
{

}

void QuestManagerScript::CornGameClear(std::any)
{
	++(m_ActiveQuests.find(70)->second.questStep);

	if (m_ActiveQuests.find(70)->second.questStep == m_ActiveQuests.find(70)->second.maxQuestStep)
	{
		m_ActiveQuests.find(70)->second.isComplete = true;

		m_QuestUiList->m_CheckBoxImage[m_ActiveQuests.find(70)->second.uiOrder]->SetImage
		(
			ResourceManager::GetInstance()->LoadResource<Image>(L"Check", L"/UI/check.png")->GetImage()
		);
	}
	else
	{
		m_ActiveQuests.find(70)->second.objectId = m_QuestList[70 + 1].objectId;
	}
	
	for (auto& object : m_QuestObjects)
	{
		if (object->GetName() == "WareHouseA")
		{
			if (dynamic_cast<ObjectDataScript*>(object->GetComponent<MonoBehaviour>())->interactionArrowCount == 0)
			{
				object->GetObjectChild("warehouseAInteractionArrow")->SetActivate(false);
				break;
			}
			else
			{
				--(dynamic_cast<ObjectDataScript*>(object->GetComponent<MonoBehaviour>())->interactionArrowCount);
			}
		}
	}
}

void QuestManagerScript::CornGameFail(std::any)
{

}

/// <summary>
/// 퀘스트 생성 (게임 매니저에서 시간에 흐름에 따라서 불러온다)
/// 긴급 퀘스트 및 밤퀘스트는 게임 매니저에서 시간에 흐름에 맞춰 생성한다.
/// </summary>
void QuestManagerScript::CreateQuest(int dayCount, bool isMorning)
{
	if (isMorning)
	{
		// 활성화된 퀘스트 및 퀘스트 UI 초기화
		ClearQuest();

		// 옥수수 퀘스트 생성 
		CreateCornQuest();

		// 잡일 퀘스트 랜덤 생성
		CreateChoresRandomQuest();

		// 퀘스트 UI 생성
		CreateQuestUi();

		// 퀘스트 상호작용 화살표 생성
		CreateQuestInteractionArrow();
	}

	else
	{
		// 활성화된 퀘스트 및 퀘스트 UI 초기화
		ClearQuest();

		// 퀘스트 UI 생성
		CreateQuestUi();

		// 밤 기본 퀘스트 문구 생성 (경찰의 눈을 피해서 시체를 숨기기)
		CreateBasicNightQuest();

		// 밤 시체 숨기기 가능한 구역 상호작용 화살표 생성
		CreateNightInteractionArrow();
	}
}

/// <summary>
/// 옥수수 퀘스트 진행 단계에 따라서 퀘스트를 생성
/// </summary>
void QuestManagerScript::CreateCornQuest()
{
	//m_CornQuestCount
	switch (m_CornQuestCount)
	{
		case 1:
			m_ActiveQuests.insert(make_pair(10, ActiveQuestData(1000, 2, L"옥수수밭에 씨 뿌리기"))); // 옥수수 밭 씨 뿌리기
			m_ActiveQuests.insert(make_pair(40, ActiveQuestData(2000, 3, L"옥수수밭에 물 주기"))); // 옥수수 밭 물 주기
			break;
		case 2:
			//m_ActiveQuests.insert(make_pair(20, ActiveQuestData(6000, 1, L"옥수수밭의 잡초 뽑기"))); // 옥수수 밭 잡초 뽑기
			m_ActiveQuests.insert(make_pair(30, ActiveQuestData(4000, 2, L"옥수수밭에 비료 주기"))); // 옥수수 밭 비료 주기
			m_ActiveQuests.insert(make_pair(40, ActiveQuestData(2000, 3, L"옥수수밭에 물 주기"))); // 옥수수 밭 물 주기
			break;
		case 3:
			m_ActiveQuests.insert(make_pair(30, ActiveQuestData(4000, 2, L"옥수수밭에 비료 주기"))); // 옥수수 밭 비료 주기
			m_ActiveQuests.insert(make_pair(40, ActiveQuestData(2000, 3, L"옥수수밭에 물 주기"))); // 옥수수 밭 물 주기
			break;
		case 4:
			m_ActiveQuests.insert(make_pair(30, ActiveQuestData(4000, 2, L"옥수수밭에 비료 주기"))); // 옥수수 밭 비료 주기
			m_ActiveQuests.insert(make_pair(40, ActiveQuestData(2000, 3, L"옥수수밭에 물 주기"))); // 옥수수 밭 물 주기
			break;
		case 5:
			m_ActiveQuests.insert(make_pair(50, ActiveQuestData(3000, 2, L"옥수수 수확하기"))); // 옥수수 수확하기		
			break;

		default:
			assert(nullptr && "옥수수 퀘스트 단계 수치 오류");
	}
}

/// <summary>
/// 랜덤 으로 잡일 퀘스트를 뽑아내는 함수 
/// </summary>
void QuestManagerScript::CreateChoresRandomQuest()
{
	// 시드값을 얻기 위한 random_device 생성.
	std::random_device rd;

	// random_device 를 통해 난수 생성 엔진을 초기화 한다.
	std::mt19937 gen(rd());

	// 1 부터 4 까지 균등하게 나타나는 난수열을 생성하기 위해 균등 분포 정의.
	std::uniform_int_distribution<int> dis(1, 4);
	//dis(gen)
	switch (dis(gen))
	{
		case 1:
			m_ActiveQuests.insert(make_pair(60, ActiveQuestData(4000, 3, L"뗄감 보충하기")));
			break;
		case 2:
			m_ActiveQuests.insert(make_pair(70, ActiveQuestData(1000, 1, L"창고 정리하기")));
			break;
		case 3:
			m_ActiveQuests.insert(make_pair(80, ActiveQuestData(5000, 2, L"고양이 밥 주기")));
			EventManager::GetInstance()->SendEvent("CatBowlEmpty", nullptr);
			break;
		case 4:
			m_ActiveQuests.insert(make_pair(90, ActiveQuestData(5000, 2, L"창고 문 열기")));
			break;

		default:
			assert(nullptr && "난수 값 오류");
	}
}  

/// <summary>
/// 긴급 퀘스트 랜덤 생성
/// </summary>
void QuestManagerScript::CreateEmergencyRandomQuest()
{
	//// 시드값을 얻기 위한 random_device 생성.
	//std::random_device rd;

	//// random_device 를 통해 난수 생성 엔진을 초기화 한다.
	//std::mt19937 gen(rd());

	//// 1 부터 4 까지 균등하게 나타나는 난수열을 생성하기 위해 균등 분포 정의.
	//std::uniform_int_distribution<int> dis(1);

	//int questId = 0;
	//switch (dis(gen))
	//{
	//	case 1:
	//		questId = 100;
	//		m_ActiveQuests.insert(make_pair(100, ActiveQuestData(7000, 1, L"고양이 구하기")));
	//		break;

	//	default:
	//		assert(nullptr && "난수 값 오류");
	//}


	int uiIndex = m_ActiveQuests.size();
	m_QuestUiList->m_QuestText[uiIndex]->SetTextColor(COLOR::EMERGENCY);

	int questId = 100;
	m_ActiveQuests.insert(make_pair(100, ActiveQuestData(7000, 1, L"고양이 구하기", m_QuestUiIndex)));

	// 퀘스트 UI 에 적용시킨다.
	m_QuestUiList->m_QuestText[m_QuestUiIndex]->SetText((m_ActiveQuests.find(questId))->second.questName);

	++m_QuestUiIndex;

	// 고양이를 멈춰두고 비활성화 시킨 다음
	// 연못시트를 고양이 빠진 시트로 변경시키기

	// 고양이 비활성화
	m_SaveCat = false;
	m_CatObject->SetActivate(false);
	m_CatObject->GetTransform()->SetLocalPosition({ 10000.f,10000.f });
	m_PondObject->GetObjectChild("PondCat")->SetActivate(true);
	//m_PondObject->GetObjectChild("pondExclamationMark")->SetActivate(true);

	m_Camera->m_Target = m_PondObject;
	m_Camera->m_TargetOn = false;
	m_Camera->m_SmoothMoveToTarget = true;
}

/// <summary>
/// 밤 퀘스트 랜덤 생성
/// </summary>
void QuestManagerScript::CreateNightRandomQuest()
{
	//// 시드값을 얻기 위한 random_device 생성.
	//std::random_device rd;

	//// random_device 를 통해 난수 생성 엔진을 초기화 한다.
	//std::mt19937 gen(rd());

	//// 1 부터 4 까지 균등하게 나타나는 난수열을 생성하기 위해 균등 분포 정의.
	//std::uniform_int_distribution<int> dis(1);

	//int questId = 0;
	//switch (dis(gen))
	//{
	//	case 1:
	//		questId = 1000;
	//		m_ActiveQuests.insert(make_pair(1000, ActiveQuestData(10000, 1, L"멧돼지 쫒아내기")));
	//		break;	

	//	default:
	//		assert(nullptr && "난수 값 오류");
	//}

	int uiIndex = m_ActiveQuests.size();
	m_QuestUiList->m_QuestText[uiIndex]->SetTextColor(COLOR::EMERGENCY);

	int questId = 1000;
	m_ActiveQuests.insert(make_pair(1000, ActiveQuestData(10000, 1, L"멧돼지 쫒아내기", m_QuestUiIndex)));

	// 퀘스트 UI 에 적용시킨다.
	m_QuestUiList->m_QuestText[m_QuestUiIndex]->SetText((m_ActiveQuests.find(questId))->second.questName);

	++m_QuestUiIndex;

	// 씬에 멧돼지를 생성시킨다.
	GameManagerScript* gameManagerScript = nullptr;
	const auto& gameObjects = GetGameObject()->GetScene()->GetGameObjects();
	for (auto& object : gameObjects)
	{
		if (object->GetName() == "wildBoar")
		{
			CreateWildBoar(object);
		}
	}

	m_ApplyFarm = false;

	m_Camera->m_Target = m_WildBoar;
	m_Camera->m_TargetOn = false;
	m_Camera->m_SmoothMoveToTarget = true;
}

/// <summary>
/// 활성화된 퀘스트를 이용하여 퀘스트 UI 에 적용 
/// </summary>
void QuestManagerScript::CreateQuestUi()
{
	// 활성화된 퀘스트들을 퀘스트 UI 에 적용
	m_QuestUiIndex = 0;

	for (auto& quest : m_ActiveQuests)
	{
		m_QuestUiList->m_QuestText[m_QuestUiIndex]->SetTextColor(COLOR::QUESTLIST);

		quest.second.uiOrder = m_QuestUiIndex;
		m_QuestUiList->m_QuestText[m_QuestUiIndex]->SetText(quest.second.questName);
		++m_QuestUiIndex;
	}
}

/// <summary>
/// 퀘스트에 필요한 아이템을 만든다.
/// </summary>
Item* QuestManagerScript::CreateQuestItem(ITEM_TYPE itemType)
{
	int index = static_cast<int>(itemType);

	switch (index)
	{
		case 0:
		{
			Item* ax = new Item(L"ax", L"도끼", ITEM_TYPE::AX, false);
			AX_ = ax;
			return ax;
		}
		case 1:
		{
			Item* bag = new Item(L"bag", L"빈 자루", ITEM_TYPE::BAG, true, 18);
			BAG_ = bag;
			return bag;
		}
		case 2:
		{
			Item* catfood = new Item(L"catfood", L"사료포대", ITEM_TYPE::CATFOOD, false);
			CATFOOD_ = catfood;
			return catfood;
		}
		case 3:
		{
			Item* corn = new Item(L"corn", L"옥수수", ITEM_TYPE::CORN, false);
			CORN_ = corn;
			return corn;
		}
		case 4:
		{
			Item* fertilizer = new Item(L"fertilizer", L"비료포대", ITEM_TYPE::FERTILIZER, true, 18);
			FERTILIZER_ = fertilizer;
			return fertilizer;
		}
		case 5:
		{
			Item* firewood = new Item(L"firewood", L"뗄감", ITEM_TYPE::FIREWOOD, false);
			FIREWOOD_ = firewood;
			return firewood;
		}
		case 6:
		{
			Item* seed = new Item(L"seed", L"씨앗", ITEM_TYPE::SEED, true, 18);
			SEED_ = seed;
			return seed;
		}
		case 7:
		{
			Item* emptyWatering = new Item(L"emptyWatering", L"물뿌리개", ITEM_TYPE::EMPTYWATERING, false);
			EMPTYWATERING_ = emptyWatering;
			return emptyWatering;
		}
		case 8:
		{
			Item* watering = new Item(L"watering", L"물뿌리개", ITEM_TYPE::WATERING, false);
			WATERING_ = watering;
			return watering;
		}
		case 9:
		{
			Item* key = new Item(L"key", L"열쇠", ITEM_TYPE::KEY, false);
			KEY_ = key;
			return key;
		}

		default:
			assert(nullptr && "아이템 타입 체크");
			return 0;
	}
}

void QuestManagerScript::DeleteAllItem()
{
	for (auto& item : m_QuestItemList)
	{
		if (item != nullptr)
		{
			if (item->m_ItemKeyName != L"corn")
			{
				delete item;
				item = nullptr;
			}
		}
	}

	for (auto& item : m_ItemManager->m_ItemList)
	{
		if (item != nullptr)
		{
			if (item->m_ItemKeyName != L"corn")
			{
				item = nullptr;
			}
		}
	}

	m_ItemManager->ApplyItemSlot();
}

/// <summary>
/// 스캔한 ObjectId 값을 퀘스트를 찾아내고 
/// 찾아낸 퀘스트와 진행도를 알아내고 
/// 진행도에 맞는 퀘스트를 불러낸다.
/// </summary>
void QuestManagerScript::CheckQuest(int scanObjectId, GameObject* scanObject)
{
	int questId = 0; // 찾아낼 퀘스트 아이디
	int prevInteractionCount = 0; 	// 상효작용 횟수 체크	
	bool completeQuest = false; // 완료된 퀘스트 인지 체크

	if (m_InteractionCount != 0)
	{
		prevInteractionCount = m_InteractionCount;
	}


	// 활설화 중인 퀘스트를 검사한다. 
	for (auto& quest : m_ActiveQuests)
	{
		// 완료된 퀘스트라면 넘긴다. (퀘스트를 넣은 순서대로 검사하기 때문에 순서 배치를 잘하거나 구조를 한번 더 고민해봐야함)
		if (quest.second.isComplete)
		{
			completeQuest = true;
			continue;
		}

		// 퀘스트 objectId 가 스캔한 objectId 와 같다면
		if (quest.second.objectId == scanObjectId)
		{
			// 해당 퀘스트 아이디 + 퀘스트 단계를 더해서 퀘스트 진행도에 맞는 퀘스트 아이디 값을 얻어낸다.
			questId = quest.first + quest.second.questStep;

			// 퀘스트 아이디를 활용해서 상호작용
			bool stepUp = InteractionQuest(questId, scanObject);

			// 퀘스트 진행도 증가
			if (stepUp)
			{
				++(quest.second.questStep);

				for (auto& scanObjectChild : scanObject->GetObjectChildren())
				{
					if (scanObjectChild->GetObjectType() == OBJECT_TYPE::INTERACTION_ARROW)
					{
						if (scanObjectChild->GetName() == "warehouseAInteractionArrow" || scanObjectChild->GetName() == "warehouseCInteractionArrow" || scanObjectChild->GetName() == "warehouseDInteractionArrow")
						{
							if (dynamic_cast<ObjectDataScript*>(scanObjectChild->GetComponent<MonoBehaviour>())->interactionArrowCount == 0)
							{
								scanObjectChild->SetActivate(false);
								break;
							}
							else
							{
								--(dynamic_cast<ObjectDataScript*>(scanObjectChild->GetComponent<MonoBehaviour>())->interactionArrowCount);

								if (dynamic_cast<ObjectDataScript*>(scanObjectChild->GetComponent<MonoBehaviour>())->interactionArrowCount == 0)
								{
									scanObjectChild->SetActivate(false);
									break;
								}
							}
						}
						else
						{
							scanObjectChild->SetActivate(false);
							break;
						}

						//scanObjectChild->SetActivate(false);
					}
				}
			}

			// 테스트
			// 퀘스트 완료 이미지 테스트 코드
			//quest.second.questStep = quest.second.maxQuestStep;

			// 퀘스트 단계를 확인하여 끝에 도달했다면 해당하는 퀘스트는 완료 처리한다.
			if (quest.second.questStep == quest.second.maxQuestStep)
			{
				quest.second.isComplete = true;

				// UI 변경 (퀘스트 완료 -> 체크 박스에 체크된 이미지)
				m_QuestUiList->m_CheckBoxImage[quest.second.uiOrder]->SetImage
				(
					ResourceManager::GetInstance()->LoadResource<Image>(L"Check", L"/UI/check.png")->GetImage()
				);
			}

			// 진행중인 퀘스트 진행도가 증가했으니 그에 맞춰 상호작용 시켜야 할 오브젝트 Id 최신화
			else
			{
				if (stepUp)
				{
					quest.second.objectId = m_QuestList[questId + 1].objectId;

					for (auto& object : m_QuestObjects)
					{
						if (object->GetObjectType() == OBJECT_TYPE::FARM)
						{
							continue;
						}
						if (quest.second.objectId == dynamic_cast<ObjectDataScript*>(object->GetComponent<MonoBehaviour>())->id)
						{
							for (auto& objectChild : object->GetObjectChildren())
							{
								if (objectChild->GetObjectType() == OBJECT_TYPE::INTERACTION_ARROW)
								{
									if (objectChild->GetName() == "warehouseAInteractionArrow" || objectChild->GetName() == "warehouseCInteractionArrow" || objectChild->GetName() == "warehouseDInteractionArrow")
									{
										++(dynamic_cast<ObjectDataScript*>(objectChild->GetComponent<MonoBehaviour>())->interactionArrowCount);
										objectChild->SetActivate(true);
										break;
									}
									else
									{
										objectChild->SetActivate(true);
										break;
									}
								}
							}
						}
					}
				}
			}

			if (prevInteractionCount != m_InteractionCount)
			{
				return;
			}
		}
	}

	if (completeQuest)
	{
		return;
	}

	//assert(nullptr && "스캔한 오브젝트가 해당하는 퀘스트가 없음");
}

/// <summary>
/// 해당 퀘스트를 찾아내고 알맞는 상호작용을 시킨다.
/// EX. 창고에서 빈 물뿌리개를 획득 -> 다음 단계 퀘스트로 넘어가짐 (물뿌리개에 물 채우기)
/// </summary>
bool QuestManagerScript::InteractionQuest(int questId, GameObject* scanObject)
{
	switch (questId)
	{
		/// 옥수수 퀘스트 ------------------------------------
		case 10:	// 옥수수 밭에 씨 뿌리기 1단계 
		{
			SoundManager::GetInstance()->PlaySoundSFX(
				ResourceManager::GetInstance()->LoadResource<Sound>(L"SeedSFX", L"/Sound/SFX/Interaction/Item_Pickup.mp3")->GetSound());

			// 씨앗 생성
			Item* seed = CreateQuestItem(ITEM_TYPE::SEED);

			// 아이템 추가
			m_ItemManager->AddItem(seed);

			// 상호 작용 횟수 증가
			++m_InteractionCount;

			return true;
		}
		case 11:	// 옥수수 밭에 씨 뿌리기 2단계
		{
			// 들고 있는 아이템이 있는지 체크
			if (m_ItemManager->GetCurrentFocusItem() != nullptr)
			{
				// 들고 있는 아이템이 씨앗인지 체크
				if (m_ItemManager->GetCurrentFocusItem()->m_ItemKeyName == L"seed")
				{
					FarmScript* farm = dynamic_cast<FarmScript*>(scanObject->GetObjectParent()->GetComponent<MonoBehaviour>());

					if (farm->detailState == "NoSeed" && farm->isInteraction == false && farm->isDestroyFarm == false)
					{
						EventManager::GetInstance()->SendEvent("FarmerInteraction", nullptr);

						SoundManager::GetInstance()->PlaySoundSFX(
							ResourceManager::GetInstance()->LoadResource<Sound>(L"SeedSFX", L"/Sound/SFX/Farm/Seed.wav")->GetSound());

						m_Player->GetObjectChild("farmerEffect")->GetComponent<Animator>()->FindAnimation(L"farmerEffectAnimation")->SetFrame(0);
						m_Player->GetObjectChild("farmerEffect")->GetComponent<Animator>()->Play(L"farmerEffectAnimation", false);
						farm->detailState = "Seed";
						farm->fakeSeed = true;

						farm->isInteraction = true;
						int& completeCornQuestCount = farm->completeQuestCount;
						++completeCornQuestCount;

						if (completeCornQuestCount == 2)
						{
							if (!m_IsCornQuestStepUp)
							{
								m_IsCornQuestStepUp = true;
							}
						}

						// 씨앗 개수가 0 이 아니라면 1개씩 사용
						if (SEED_->m_ItemCount != 0)
						{
							SEED_->m_ItemCount -= 1;

							if (SEED_->m_ItemCount == 1)
							{
								SEED_->m_IsCountable = false;
							}
						}

						// 0 이면 아이템 삭제
						if (SEED_->m_ItemCount == 0)
						{
							m_ItemManager->DeleteItem(SEED_);
							SEED_ = nullptr;

							m_ItemManager->ApplyItemSlot();

							return true;
						}

						m_ItemManager->ApplyItemSlot();

						// 상호 작용 횟수 증가
						++m_InteractionCount;
					}
				}
			}

			return false;
		}
		//case 20:	// 옥수수 밭의 잡초 뽑기 2단계
		//{
		//	// 옥수수 퀘스트 완료 카운트 1 증가
		//	++m_DayCompleteCornQuestCount;

		//	EventManager::GetInstance()->SendEvent("FarmCompleteQuestCount", nullptr);

		//	// 상호 작용 횟수 증가
		//	++m_InteractionCount;

		//	return true;
		//}
		case 30:	// 옥수수 밭에 비료 주기 1단계
		{
			SoundManager::GetInstance()->PlaySoundSFX(
				ResourceManager::GetInstance()->LoadResource<Sound>(L"SeedSFX", L"/Sound/SFX/Interaction/Item_Pickup.mp3")->GetSound());

			// 비료포대 생성
			Item* fertilizer = CreateQuestItem(ITEM_TYPE::FERTILIZER);

			// 아이템 추가
			m_ItemManager->AddItem(fertilizer);

			// 상호 작용 횟수 증가
			++m_InteractionCount;

			return true;
		}
		case 31:	// 옥수수 밭에 비료 주기 2단계
		{
			// 들고 있는 아이템이 있는지 체크
			if (m_ItemManager->GetCurrentFocusItem() != nullptr)
			{
				// 들고 있는 아이템이 비료인지 체크
				if (m_ItemManager->GetCurrentFocusItem()->m_ItemKeyName == L"fertilizer")
				{
					FarmScript* farm = dynamic_cast<FarmScript*>(scanObject->GetObjectParent()->GetComponent<MonoBehaviour>());
					string farmState = farm->detailState;
					if ((farmState == "Seed" || farmState == "First" || farmState == "Second") && !(farm->isInteraction))
					{
						// 상호작용 모션 이벤트 On
						EventManager::GetInstance()->SendEvent("FarmerInteraction", nullptr);

						/*SoundManager::GetInstance()->PlaySoundSFX(
							ResourceManager::GetInstance()->LoadResource<Sound>(L"FertilizerSFX", L"/Sound/SFX/Farm/Digging_Dirt_With_Hand (1).mp3")->GetSound());*/

						SoundManager::GetInstance()->PlaySoundSFX(
							ResourceManager::GetInstance()->LoadResource<Sound>(L"FertilizerSFX", L"/Sound/SFX/Farm/Digging_Dirt_With_Hand (2).mp3")->GetSound());

						// 비료 이미지 On
						int index = farm->farmNumber;
						for (auto farmChild : scanObject->GetObjectParent()->GetObjectChildren())
						{
							if (farmChild->GetName() == "SecondFarmChildFertilizer" + to_string(index) || farmChild->GetName() == "FirstFarmChildFertilizer" + to_string(index))
							{
								farmChild->SetActivate(true);
							}
						}

						// 상호작용 bool 변수 on
						farm->isInteraction = true;

						// 옥수수 2가지 퀘스트 중 1
						int& completeCornQuestCount = farm->completeQuestCount;
						++completeCornQuestCount;

						if (completeCornQuestCount == 2)
						{
							if (!m_IsCornQuestStepUp)
							{
								m_IsCornQuestStepUp = true;
							}
						}

						// 비료 개수가 0 이 아니라면 1개 줄이기
						if (FERTILIZER_->m_ItemCount != 0)
						{
							FERTILIZER_->m_ItemCount -= 1;

							if (FERTILIZER_->m_ItemCount == 1)
							{
								FERTILIZER_->m_IsCountable = false;
							}
						}

						// 0이라면 아이템 삭제
						if (FERTILIZER_->m_ItemCount == 0)
						{
							m_ItemManager->DeleteItem(FERTILIZER_);
							FERTILIZER_ = nullptr;

							m_ItemManager->ApplyItemSlot();

							return true;
						}

						m_ItemManager->ApplyItemSlot();

						// 상호 작용 횟수 증가
						++m_InteractionCount;
					}
				}
			}

			return false;
		}
		case 40:	// 옥수수 밭에 물 주기 1단계	
		{
			SoundManager::GetInstance()->PlaySoundSFX(
				ResourceManager::GetInstance()->LoadResource<Sound>(L"SeedSFX", L"/Sound/SFX/Interaction/Item_Pickup.mp3")->GetSound());

			// 빈 물뿌리개 생성
			Item* emptyWatering = CreateQuestItem(ITEM_TYPE::EMPTYWATERING);

			// 아이템 추가	
			m_ItemManager->AddItem(emptyWatering);

			// 상호 작용 횟수 증가
			++m_InteractionCount;

			return true;
		}
		case 41:	// 옥수수 밭에 물 주기 2단계
		{
			// 들고 있는 아이템이 있는지 체크
			if (m_ItemManager->GetCurrentFocusItem() != nullptr)
			{
				// 들고 있는 아이템이 빈 물뿌리개 인지 체크
				if (m_ItemManager->GetCurrentFocusItem()->m_ItemKeyName == L"emptyWatering")
				{
					if (dynamic_cast<ObjectDataScript*>(scanObject->GetComponent<MonoBehaviour>())->inabilityGetWater == false)
					{
						EventManager::GetInstance()->SendEvent("FarmerInteraction", nullptr);

						SoundManager::GetInstance()->PlaySoundSFX(
							ResourceManager::GetInstance()->LoadResource<Sound>(L"FertilizerSFX", L"/Sound/SFX/Interaction/Water_Filled.mp3")->GetSound());

						// 빈 물뿌리개 삭제
						m_ItemManager->DeleteItem(EMPTYWATERING_);
						EMPTYWATERING_ = nullptr;

						// 물뿌리개 생성 및 추가
						Item* watering = CreateQuestItem(ITEM_TYPE::WATERING);

						m_ItemManager->AddItem(watering);

						// 상호 작용 횟수 증가
						++m_InteractionCount;

						return true;
					}
					/*else
					{
						string stringObjectKey = scanObject->GetName();

						if (stringObjectKey.compare("pond") != 0)
						{
							m_Player->GetObjectChild("farmerTextBubble")->SetActivate(true);

							wstring texts = dynamic_cast<FarmerScript*>(m_Player->GetComponent<MonoBehaviour>())->textManager->explainMap[stringObjectKey][1];
							m_Player->GetObjectChild("farmerTextBubble")->GetComponent<TextRenderer>()->SetTextColor(COLOR::EMERGENCY);
							m_Player->GetObjectChild("farmerTextBubble")->GetComponent<TextRenderer>()->SetText(texts);
						}
					}*/
				}
			}

			return false;
		}
		case 42:	// 옥수수 밭에 물 주기 3단계
		{
			// 물 뿌리개는 8번 물을 뿌리고 삭제해야 시켜야 한다.
			static int waterCount = 18;
			if (m_questReset)
			{
				waterCount = 18;
				m_questReset = false;
			}

			// 들고 있는 아이템이 있는지 체크
			if (m_ItemManager->GetCurrentFocusItem() != nullptr)
			{
				// 들고 있는 아이템이 물뿌리개 인지 체크
				if (m_ItemManager->GetCurrentFocusItem()->m_ItemKeyName == L"watering")
				{
					FarmScript* farm = dynamic_cast<FarmScript*>(scanObject->GetObjectParent()->GetComponent<MonoBehaviour>());
					if (farm->farmState == "FarmNoWater" && farm->isDestroyFarm == false)
					{
						farm->farmState = "FarmWater";

						SoundManager::GetInstance()->PlaySoundSFX(
							ResourceManager::GetInstance()->LoadResource<Sound>(L"WateringSFX", L"/Sound/SFX/Farm/Watering_Plants.mp3")->GetSound());

						int& completeCornQuestCount = farm->completeQuestCount;
						++completeCornQuestCount;

						if (completeCornQuestCount == 2)
						{
							if (!m_IsCornQuestStepUp)
							{
								m_IsCornQuestStepUp = true;
							}
						}

						--waterCount;

						// 물 뿌리기 모션
						EventManager::GetInstance()->SendEvent("FarmerWatering", nullptr);

						// 남은 물 뿌리기 횟수가 0 이라면 
						if (waterCount == 0)
						{
							// 물뿌리개 삭제
							m_ItemManager->DeleteItem(WATERING_);
							WATERING_ = nullptr;

							m_ItemManager->ApplyItemSlot();

							return true;
						}

						// 상호 작용 횟수 증가
						++m_InteractionCount;
					}
				}
			}

			return false;
		}
		case 50:	// 옥수수 수확하기 1단계
		{
			SoundManager::GetInstance()->PlaySoundSFX(
				ResourceManager::GetInstance()->LoadResource<Sound>(L"SeedSFX", L"/Sound/SFX/Interaction/Item_Pickup.mp3")->GetSound());

			// 빈 자루 생성
			Item* bag = CreateQuestItem(ITEM_TYPE::BAG);

			// 아이템 추가	
			m_ItemManager->AddItem(bag);

			// 상호 작용 횟수 증가
			++m_InteractionCount;

			return true;
		}
		case 51:	// 옥수수 수확하기 2단계
		{
			// 들고 있는 아이템이 있는지 체크
			if (m_ItemManager->GetCurrentFocusItem() != nullptr)
			{
				// 들고 있는 아이템이 물뿌리개 인지 체크
				if (m_ItemManager->GetCurrentFocusItem()->m_ItemKeyName == L"bag")
				{
					FarmScript* farm = dynamic_cast<FarmScript*>(scanObject->GetObjectParent()->GetComponent<MonoBehaviour>());

					if (farm->detailState == "Third")
					{
						EventManager::GetInstance()->SendEvent("FarmerHarvest", nullptr);

						SoundManager::GetInstance()->PlaySoundSFX(
							ResourceManager::GetInstance()->LoadResource<Sound>(L"HarvestSFX", L"/Sound/SFX/Farm/Harvest_Crop.mp3")->GetSound());

						m_Player->GetObjectChild("farmerEffect")->GetComponent<Animator>()->FindAnimation(L"farmerEffectAnimation")->SetFrame(0);
						m_Player->GetObjectChild("farmerEffect")->GetComponent<Animator>()->Play(L"farmerEffectAnimation", false);

						farm->detailState = "NoSeed";

						bool createCorn = true;
						for (auto& item : m_ItemManager->m_ItemList)
						{
							if (item != nullptr)
							{
								if (item->m_ItemKeyName == L"corn")
								{
									if (item->m_IsCountable == false)
									{
										item->m_IsCountable = true;
										++(item->m_ItemCount);
										createCorn = false;
									}
									else
									{
										++(item->m_ItemCount);
										createCorn = false;
									}
								}
							}
						}

						if (createCorn)
						{
							Item* corn = CreateQuestItem(ITEM_TYPE::CORN);
							m_ItemManager->AddItem(corn);
						}

						if (BAG_->m_ItemCount != 0)
						{
							BAG_->m_ItemCount -= 1;

							if (BAG_->m_ItemCount == 1)
							{
								BAG_->m_IsCountable = false;
							}
						}

						if (BAG_->m_ItemCount == 0)
						{
							m_ItemManager->DeleteItem(BAG_);
							BAG_ = nullptr;

							m_ItemManager->ApplyItemSlot();

							return true;
						}

						m_ItemManager->ApplyItemSlot();

						// 상호 작용 횟수 증가
						++m_InteractionCount;

						return false;
					}
				}
			}

			return false;
		}

		/// 잡일 퀘스트 ------------------------------------
		case 60:	// 뗄감 보충하기 1단계
		{
			SoundManager::GetInstance()->PlaySoundSFX(
				ResourceManager::GetInstance()->LoadResource<Sound>(L"SeedSFX", L"/Sound/SFX/Interaction/Item_Pickup.mp3")->GetSound());

			// 도끼 생성
			Item* ax = CreateQuestItem(ITEM_TYPE::AX);

			// 아이템 추가	
			m_ItemManager->AddItem(ax);

			// 상호 작용 횟수 증가
			++m_InteractionCount;

			return true;
		}
		case 61:	// 뗄감 보충하기 2단계
		{
			// 들고 있는 아이템이 있는지 체크
			if (m_ItemManager->GetCurrentFocusItem() != nullptr)
			{
				// 도끼를 들고 있는지
				if (m_ItemManager->GetCurrentFocusItem()->m_ItemKeyName == L"ax")
				{
					EventManager::GetInstance()->SendEvent("FarmerInteraction", nullptr);

					SoundManager::GetInstance()->PlaySoundSFX(
						ResourceManager::GetInstance()->LoadResource<Sound>(L"FertilizerSFX", L"/Sound/SFX/Interaction/Cut_Down_Tree_With_Axe.mp3")->GetSound());

					// 도끼 삭제
					m_ItemManager->DeleteItem(AX_);
					AX_ = nullptr;

					// 뗄감 생성
					Item* firewood = CreateQuestItem(ITEM_TYPE::FIREWOOD);
					m_ItemManager->AddItem(firewood);

					// 상호 작용 횟수 증가
					++m_InteractionCount;

					return true;
				}
			}

			return false;
		}
		case 62:	// 뗄감 보충하기 3단계
		{
			// 들고 있는 아이템이 있는지 체크
			if (m_ItemManager->GetCurrentFocusItem() != nullptr)
			{
				// 뗄감을 들고 있는지
				if (m_ItemManager->GetCurrentFocusItem()->m_ItemKeyName == L"firewood")
				{
					SoundManager::GetInstance()->PlaySoundSFX(
						ResourceManager::GetInstance()->LoadResource<Sound>(L"SeedSFX", L"/Sound/SFX/Interaction/Item_Pickup.mp3")->GetSound());

					// 뗄감 삭제
					m_ItemManager->DeleteItem(FIREWOOD_);
					FIREWOOD_ = nullptr;

					m_ItemManager->ApplyItemSlot();

					// 상호 작용 횟수 증가
					++m_InteractionCount;

					return true;
				}
			}

			return false;
		}
		case 70:	// 창고 정리하기
			/// 미니 게임 발동하는 코드 넣어주기 

			EventManager::GetInstance()->SendEvent("CornGame", nullptr);

			SoundManager::GetInstance()->PlaySoundSFX(
				ResourceManager::GetInstance()->LoadResource<Sound>(L"SeedSFX", L"/Sound/SFX/Interaction/Item_Pickup.mp3")->GetSound());

			// 상호 작용 횟수 증가
			++m_InteractionCount;

			return false;
		case 80:	// 고양이 밥 주기 1단계
		{
			SoundManager::GetInstance()->PlaySoundSFX(
				ResourceManager::GetInstance()->LoadResource<Sound>(L"SeedSFX", L"/Sound/SFX/Interaction/Item_Pickup.mp3")->GetSound());

			// 사료포대 생성
			Item* catfood = CreateQuestItem(ITEM_TYPE::CATFOOD);

			// 아이템 추가	
			m_ItemManager->AddItem(catfood);

			// 상호 작용 횟수 증가
			++m_InteractionCount;

			return true;
		}
		case 81:	// 고양이 밥 주기 2단계
		{
			// 들고 있는 아이템이 있는지 체크
			if (m_ItemManager->GetCurrentFocusItem() != nullptr)
			{
				// 사료포대를 들고 있는지
				if (m_ItemManager->GetCurrentFocusItem()->m_ItemKeyName == L"catfood")
				{
					EventManager::GetInstance()->SendEvent("FarmerInteraction", nullptr);

					SoundManager::GetInstance()->PlaySoundSFX(
						ResourceManager::GetInstance()->LoadResource<Sound>(L"FertilizerSFX", L"/Sound/SFX/Interaction/catFood_Pouring.mp3")->GetSound());

					// 사료포대 삭제
					m_ItemManager->DeleteItem(CATFOOD_);

					CATFOOD_ = nullptr;

					m_ItemManager->ApplyItemSlot();

					EventManager::GetInstance()->SendEvent("CatBowlFull", nullptr);

					// 상호 작용 횟수 증가
					++m_InteractionCount;

					return true;
				}
			}

			return false;
		}
		case 90:	// 창고 문 열기 1단계
		{
			SoundManager::GetInstance()->PlaySoundSFX(
				ResourceManager::GetInstance()->LoadResource<Sound>(L"SeedSFX", L"/Sound/SFX/Interaction/Item_Pickup.mp3")->GetSound());

			// 열쇠 생성
			Item* key = CreateQuestItem(ITEM_TYPE::KEY);

			// 아이템 추가	
			m_ItemManager->AddItem(key);

			// 상호 작용 횟수 증가
			++m_InteractionCount;

			return true;
		}
		case 91:	// 창고 문 열기 2단계
		{
			// 들고 있는 아이템이 있는지 체크
			if (m_ItemManager->GetCurrentFocusItem() != nullptr)
			{
				// 열쇠를 들고 있는지
				if (m_ItemManager->GetCurrentFocusItem()->m_ItemKeyName == L"key")
				{
					/// 미니 게임
					EventManager::GetInstance()->SendEvent("WareHouseGame", nullptr);

					// 상호 작용 횟수 증가
					++m_InteractionCount;
				}
			}

			return false;
		}

		/// 긴급 퀘스트  ----------------------------------
		case 100:	// 고양이 구하기
		{
			EventManager::GetInstance()->SendEvent("FarmerInteraction", nullptr);

			dynamic_cast<BlackCatScript*>(m_CatObject->GetComponent<MonoBehaviour>())->isSave = true;
			dynamic_cast<BlackCatScript*>(m_CatObject->GetComponent<MonoBehaviour>())->action = true;
			/*m_CatObject->GetObjectChild("blackCatChild")->SetActivate(true);

			SoundManager::GetInstance()->StopSoundSFX();

			SoundManager::GetInstance()->PlaySoundSFX(
				ResourceManager::GetInstance()->LoadResource<Sound>(L"CatMeowSFX", L"/Sound/SFX/Interaction/Cat_Meow.mp3")->GetSound());*/

			Vector2 playerPosition = m_Player->GetTransform()->GetLocalPosition();
			Vector2 pondPosition = m_PondObject->GetTransform()->GetLocalPosition();


			if (playerPosition.x > pondPosition.x)
			{
				m_CatObject->GetTransform()->SetLocalPosition(playerPosition + Vector2{ 70.f, 0.f });
			}
			else
			{
				m_CatObject->GetTransform()->SetLocalPosition(playerPosition + Vector2{ -70.f, 0.f });
			}

			m_CatObject->SetActivate(true);
			m_PondObject->GetObjectChild("PondCat")->SetActivate(false);
			//m_PondObject->GetObjectChild("pondExclamationMark")->SetActivate(false);

			m_SaveCat = true;

			// 상호 작용 횟수 증가
			++m_InteractionCount;

			return true;
		}

		/// 밤 퀘스트  ------------------------------------
		case 1000:	// 맷돼지 쫒아내기	
		{
			if (dynamic_cast<WildBoarScript*>(scanObject->GetObjectParent()->GetComponent<MonoBehaviour>())->m_IsCollision)
			{
				/// 미니 게임
				EventManager::GetInstance()->SendEvent("WildBoarGame", nullptr);

				m_WildBoar->SetActivate(false);
				m_WildBoar->GetObjectChild("wildBoarExclamationMark")->SetActivate(false);

				// 상호 작용 횟수 증가
				++m_InteractionCount;
			}

			return false;
		}
	}

	assert(nullptr && "해당하는 퀘스트가 없음");

	return false;
}

/// <summary>
/// 활성화 퀘스트 및 UI 초기화
/// </summary>
void QuestManagerScript::ClearQuest()
{
	// 퀘스트 초기화 true (InteractionQuest 에서 사용 예정)
	m_questReset = true;

	// 활성화된 퀘스트 초기화
	m_ActiveQuests.clear();

	// 퀘스트 UI 초기화
	for (int index = 0; index < QUEST_UI_COUNT; index++)
	{
		m_QuestUiList->m_QuestText[index]->SetText(L"");
		m_QuestUiList->m_CheckBoxImage[index]->SetImage
		(
			ResourceManager::GetInstance()->LoadResource<Image>(L"noneCheck", L"/UI/nonecheck.png")->GetImage()
		);
	}

	for (auto& object : m_QuestObjects)
	{
		if (object->GetObjectType() == OBJECT_TYPE::FARM)
		{
			continue;
		}

		if (object->GetName() == "CatBowl" || object->GetName() == "Truck" || object->GetName() == "wildBoarChild" || object->GetName() == "Tree")
		{
			continue;
		}

		for (auto& objectChild : object->GetObjectChildren())
		{
			if (objectChild->GetObjectType() == OBJECT_TYPE::INTERACTION_ARROW)
			{
				if (objectChild->GetName() == "warehouseAInteractionArrow" || objectChild->GetName() == "warehouseCInteractionArrow" || objectChild->GetName() == "warehouseDInteractionArrow")
				{
					if (dynamic_cast<ObjectDataScript*>(objectChild->GetComponent<MonoBehaviour>())->interactionArrowCount == 0)
					{
						objectChild->SetActivate(false);
						break;
					}
					else
					{
						--(dynamic_cast<ObjectDataScript*>(objectChild->GetComponent<MonoBehaviour>())->interactionArrowCount);

						if (dynamic_cast<ObjectDataScript*>(objectChild->GetComponent<MonoBehaviour>())->interactionArrowCount == 0)
						{
							objectChild->SetActivate(false);
							break;
						}
					}
				}
				else
				{
					objectChild->SetActivate(false);
					break;
				}


				/*objectChild->SetActivate(false);
				break;*/
			}
		}
	}
}

/// <summary>
/// 낮에 활성화된 모든 퀘스트를 완료 했는지 체크 
/// 실패 시 일시적으로 순찰 레벨 증가 
/// PoliceScript 이벤트 호출 
/// 
/// 또한 특정 퀘스트 실패 시 패널티 부여 (밤 퀘스트 멧돼지 등등)
/// </summary>
void QuestManagerScript::CheckCompleteAllActiveQuests()
{
	// 단 하나라도 실패한 퀘스트가 있다면 순찰 레벨 증가.
	for (auto& questIter : m_ActiveQuests)
	{
		if (!(questIter.second.isComplete))
		{
			m_CompleteAllActiveQuests = false;
			break;
		}
		else
		{
			m_CompleteAllActiveQuests = true;
		}
	}

	// 순찰 레벨 증가를 위한 PoliceScript 이벤트 호출
	if (m_CompleteAllActiveQuests == false)
	{
		EventManager::GetInstance()->SendEvent("PatrolLevelUp", nullptr);
		EventManager::GetInstance()->SendEvent("PatrolLevelTemporary", nullptr);
	}
}

// 밤 퀘스트 : 멧돼지 쫒아내기
// 퀘스트 발생시 씬에 멧돼지를 추가시킨다.
void QuestManagerScript::CreateWildBoar(GameObject* wildBoarObject)
{
	wildBoarObject->GetTransform()->SetLocalPosition(Vector2{ -2000.f, -150.f } + Vector2{ 960.f, 540.f });
	dynamic_cast<WildBoarScript*>(wildBoarObject->GetComponent<MonoBehaviour>())->m_PauseUpdate = false;
	dynamic_cast<WildBoarScript*>(wildBoarObject->GetComponent<MonoBehaviour>())->m_GameManager = dynamic_cast<FarmerScript*>(m_Player->GetComponent<MonoBehaviour>())->manager;
	wildBoarObject->GetComponent<Animator>()->Play(L"WildBoarRightRun", true);
	dynamic_cast<WildBoarScript*>(wildBoarObject->GetComponent<MonoBehaviour>())->m_IsCollision = false;
	wildBoarObject->SetActivate(true);
}

/// <summary>
/// 낮 상호작용 가능한 퀘스트 건물 화살표 이미지 추가 
/// </summary>
void QuestManagerScript::CreateQuestInteractionArrow()
{
	for (auto& quest : m_ActiveQuests)
	{
		for (auto& object : m_QuestObjects)
		{
			if (object->GetObjectType() == OBJECT_TYPE::FARM)
			{
				continue;
			}

			if (quest.second.objectId == dynamic_cast<ObjectDataScript*>(object->GetComponent<MonoBehaviour>())->id)
			{
				for (auto& objectChild : object->GetObjectChildren())
				{
					if (objectChild->GetObjectType() == OBJECT_TYPE::INTERACTION_ARROW)
					{
						if (objectChild->GetName() == "warehouseAInteractionArrow" || objectChild->GetName() == "warehouseCInteractionArrow" || objectChild->GetName() == "warehouseDInteractionArrow")
						{
							++(dynamic_cast<ObjectDataScript*>(objectChild->GetComponent<MonoBehaviour>())->interactionArrowCount);
							int test = dynamic_cast<ObjectDataScript*>(objectChild->GetComponent<MonoBehaviour>())->interactionArrowCount;
							objectChild->SetActivate(true);
							break;
						}
						else
						{
							objectChild->SetActivate(true);
							break;
						}
					}
				}
			}
		}
	}
}

/// <summary>
/// 밤 시작 시 기본적으로 있어야하는 퀘스트 문구 생성
/// </summary>
void QuestManagerScript::CreateBasicNightQuest()
{
	m_QuestUiList->m_QuestText[0]->SetTextColor(COLOR::EMERGENCY);
	m_ActiveQuests.insert(make_pair(999, ActiveQuestData(100000, 1, L"경찰의 눈을 피해서 시체 숨기기", m_QuestUiIndex)));
	m_QuestUiList->m_QuestText[0]->SetText((m_ActiveQuests.find(999))->second.questName);
	++m_QuestUiIndex;
}

/// <summary>
/// 밤 시작 시 시체 숨기기 가능한 구역 화살표 이미지 생성
/// </summary>
void QuestManagerScript::CreateNightInteractionArrow()
{
	for (auto& object : m_QuestObjects)
	{
		if (object->GetObjectType() == OBJECT_TYPE::FARM)
		{
			continue;
		}

		if (object->GetName() == "CatBowl" || object->GetName() == "Truck" || object->GetName() == "wildBoarChild" || object->GetName() == "Tree" || object->GetName() == "WarehouseB")
		{
			continue;
		}
		
		for (auto& objectChild : object->GetObjectChildren())
		{
			if (objectChild->GetObjectType() == OBJECT_TYPE::INTERACTION_ARROW)
			{
				objectChild->SetActivate(true);
				break;
			}
		}
	}
}

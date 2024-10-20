#pragma once

#include <MonoBehaviour.h>

#include <Map>
using std::map;
#include <Vector>
using std::vector;
using std::make_pair;
#include <string>
using std::wstring;

class QuestList;
class ItemManagerScript;
class Item;
class CameraScript;

enum class ITEM_TYPE;

#define AX_ m_QuestItemList[static_cast<int>(ITEM_TYPE::AX)]
#define BAG_ m_QuestItemList[static_cast<int>(ITEM_TYPE::BAG)]
#define CATFOOD_ m_QuestItemList[static_cast<int>(ITEM_TYPE::CATFOOD)]
#define CORN_ m_QuestItemList[static_cast<int>(ITEM_TYPE::CORN)]
#define FERTILIZER_ m_QuestItemList[static_cast<int>(ITEM_TYPE::FERTILIZER)]
#define FIREWOOD_ m_QuestItemList[static_cast<int>(ITEM_TYPE::FIREWOOD)]
#define SEED_ m_QuestItemList[static_cast<int>(ITEM_TYPE::SEED)]
#define EMPTYWATERING_ m_QuestItemList[static_cast<int>(ITEM_TYPE::EMPTYWATERING)]
#define WATERING_ m_QuestItemList[static_cast<int>(ITEM_TYPE::WATERING)]
#define KEY_ m_QuestItemList[static_cast<int>(ITEM_TYPE::KEY)]

/// <summary>
/// 활성화 중인 퀘스트 데이터
/// </summary>
struct ActiveQuestData
{
	ActiveQuestData(int objectId, int maxQuestStep, wstring questName, int uiOrder = 0, int questStep = 0, bool isComplete = false)
	{
		this->objectId = objectId;
		this->maxQuestStep = maxQuestStep;
		this->questName = questName;
		this->uiOrder = uiOrder;
		this->questStep = questStep;
		this->isComplete = isComplete;
	}

	int objectId;
	int maxQuestStep;
	wstring questName;
	int uiOrder;
	int questStep;
	bool isComplete;
};

/// <summary>
/// 퀘스트 데이터
/// </summary>
struct QuestData
{
	QuestData() {}
	QuestData(string questName, int objectId)
	{
		this->questName = questName;
		this->objectId = objectId;
	}

	string questName = "";
	int objectId = 0;
};


/// <summary>
/// 작성일 : 2023.08.17
/// 작성자 : 김동일
/// 
/// 퀘스트를 관리하는 매니저
/// </summary>
class QuestManagerScript : public MonoBehaviour
{
public:
	QuestManagerScript();
	~QuestManagerScript();

public:
	virtual void Start();
	virtual void Update(float deltaTime);
	virtual void Finalize();

public:
	// 이벤트
	void WildBoarClear(std::any);
	void WildBoarFail(std::any);
	void WareHouseClear(std::any);
	void WareHouseFail(std::any);
	void CornGameClear(std::any);
	void CornGameFail(std::any);

public:
	void CreateQuest(int dayCount, bool isMorning); // 퀘스트 생성
	void CreateCornQuest(); // 옥수수 퀘스트 생성
	void CreateChoresRandomQuest(); // 잡일 퀘스트 랜덤 생성
	void CreateEmergencyRandomQuest(); // 긴급 퀘스트 랜덤 생성
	void CreateNightRandomQuest(); // 밤 퀘스트 랜덤 생성
	void CreateQuestUi(); // 퀘스트 UI 생성
	Item* CreateQuestItem(ITEM_TYPE itemType); // 활성화된 퀘스트 관련 아이템 생성
	void CreateWildBoar(GameObject* wildBoarObject);

	// 퀘스트 상호작용 화살표 생성
	void CreateQuestInteractionArrow();

	// 밤 기본 퀘스트 문구 생성
	void CreateBasicNightQuest();

	// 밤 시체 숨기기 가능한 구역 상호작용 화살표 생성
	void CreateNightInteractionArrow();

	void DeleteAllItem();

public:
	void CheckQuest(int scanObjectId, GameObject* scanObject); // 상호작용 중인 오브젝트 아이디로 퀘스트 체크
	bool InteractionQuest(int questId, GameObject* scanObject); // 퀘스트 컨트롤 (퀘스트 진행시킴)
	void ClearQuest(); // 퀘스트 초기화
	void CheckCompleteAllActiveQuests(); // 활성화된 모든 퀘스트를 완료 했는지 체크
	
public:
	// CheckQuest 에서 사용하게 될 변수
	// 퀘스트가 생긴 순서대로 체크하기 때문에 모든 항목을 제대로 검사하기 위한 변수
	// 수행한 퀘스트라면 변수값이 변하고 이 변수를 활용하여 퀘스트 체크를 계속할지 말지 결정한다.
	int m_InteractionCount;

	static const int QUEST_UI_COUNT = 4; // 퀘스트 UI 초기화를 위한 static 변수
	int m_CornQuestCount; // 진행해야 할 옥수수 퀘스트 단계를 알려준다.
	bool m_IsCornQuestStepUp; 
	bool m_questReset; 	// 퀘스트 리셋을 했는가 (물 뿌리개 횟수 초기화를 위함)
	int m_QuestUiIndex; // 30~60초 사이에 발생하는 퀘스트 (UI 최신화 작업)
	bool m_FailWildBoar; // 멧돼지 퀘스트 실패 
	bool m_ApplyFarm;
	bool m_SaveCat;
	bool m_CompleteAllActiveQuests;

	// 일단 구현    해 
	GameObject* m_CatObject;
	GameObject* m_PondObject;
	GameObject* m_Player;
	GameObject* m_WildBoar;
	CameraScript* m_Camera;

	map<int, ActiveQuestData> m_ActiveQuests; 	// 현재 활성화 중인 모든 퀘스트들 (퀘스트 아이디, 단계 정보를 가지고 있음)
	vector<GameObject*> m_QuestObjects;  	// 전체 퀘스트 관련 오브젝트들
	map<int, QuestData> m_QuestList;  // 전체 퀘스트 리스트
	QuestList* m_QuestUiList; // 퀘스트 리스트 UI
	
	Item* m_QuestItemList[10]; 	// 퀘스트 아이템 배열 (퀘스트 생성 및 삭제시 그에 관련된 아이템들 생성,삭제)

	ItemManagerScript* m_ItemManager; 	// 아이템 매니저
};


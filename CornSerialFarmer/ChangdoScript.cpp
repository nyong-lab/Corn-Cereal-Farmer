#include "ChangdoScript.h"
#include "Transform.h"
#include "Random.h"
#include "Input.h"
#include "Collider.h"
#include "TextRenderer.h"
#include "EventManager.h"
#include "WarehouseGame.h"
#include "GameplayStatics.h"
#include "WildBoarGame.h"
#include "CornGame.h"
#include "GameManagerScript.h"
#include "ItemManagerScript.h"


ChangdoScript::ChangdoScript() :
	MonoBehaviour(typeid(this).name())
{

}

ChangdoScript::~ChangdoScript()
{

}

void ChangdoScript::WareHouseGameFunc(std::any)
{
	WarehouseGame* whGame = new WarehouseGame;
	GameplayStatics::CreateObject(whGame);
}

void ChangdoScript::CornGameFunc(std::any)
{
	CornGame* cornGame = new CornGame;
	GameplayStatics::CreateObject(cornGame);
}

void ChangdoScript::WildBoarGameFunc(std::any)
{
	WildBoarGame* wbGame = new WildBoarGame;
	GameplayStatics::CreateObject(wbGame);
}

void ChangdoScript::Start()
{
	//m_Transform->SetLocalPosition(Vector2 (Random::Range(0.f, 1920.f), Random::Range(0.f, 1080.f)));
	EventManager::GetInstance()->RegisterClient("WareHouseGame", MakeCallInfo(&ChangdoScript::WareHouseGameFunc));
	EventManager::GetInstance()->RegisterClient("WildBoarGame", MakeCallInfo(&ChangdoScript::WildBoarGameFunc));
	EventManager::GetInstance()->RegisterClient("CornGame", MakeCallInfo(&ChangdoScript::CornGameFunc));
}

void ChangdoScript::Update(float deltaTime)
{
	static float elipseTime = 0.f;
	
	elipseTime += deltaTime;
// 	if (elipseTime > 1.f)
// 	{
// 		Vector2 pos = m_Transform->GetLocalPosition();
// 		pos += Vector2(Random::Range(-50.f, 50.f), Random::Range(-50.f, 50.f));
// 		m_Transform->SetLocalPosition(pos);
// 		elipseTime = 0.f;
// 	}

	if (Input::GetKeyDown(KEY::B))
	{
		EventManager::GetInstance()->SendEvent("WareHouseGame", nullptr);
	}
	if (Input::GetKeyDown(KEY::N))
	{
		EventManager::GetInstance()->SendEvent("WildBoarGame", nullptr);
	}
	if (Input::GetKeyDown(KEY::M))
	{
		EventManager::GetInstance()->SendEvent("CornGame", nullptr);
	}

	if (Input::GetKeyDown(KEY::P))
	{
		GameplayStatics::PauseGame();
	}
	if (Input::GetKeyDown(KEY::R))
	{
		GameplayStatics::ResumeGame();
	}


	//다음날 시작으로 넘어감
	if (Input::GetKeyDown(KEY::F1))
	{
		m_GameManagerScript->m_TimePassed = 99999;
		m_GameManagerScript->m_IsDay = false;
	
	}
	if (Input::GetKeyDown(KEY::F2))
	{
		m_GameManagerScript->m_TimePassed = 99999;
		m_GameManagerScript->m_IsDay = false;
		m_GameManagerScript->m_DayCount = 5;

		Item* corn = new Item(L"corn", L"옥수수", ITEM_TYPE::CORN, true, 18);
		m_GameManagerScript->m_ItemManager->AddItem(corn);
	}
	if (Input::GetKeyDown(KEY::F3))
	{
		m_GameManagerScript->m_TimePassed = 99999;
		m_GameManagerScript->m_IsDay = false;
		m_GameManagerScript->m_DayCount = 5;
	}
// 	if (Input::GetKeyDown(KEY::F4))
// 	{
// 		GameplayStatics::SetTimeScale(6.f);
// 	}


// 	Bound bound = m_Collider->GetBound();
// 	std::wstring wstr = L"ID : ";
// 	wstr += to_wstring(m_Collider->GetID());
// 	wstr += L"\n";
// 	wstr += bound.to_wstring();
// 	m_Render->SetText(wstr);

}

void ChangdoScript::FixedUpdate(float deltaTime)
{

}

void ChangdoScript::Finalize()
{

}

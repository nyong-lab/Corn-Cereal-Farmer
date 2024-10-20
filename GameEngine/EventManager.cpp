#include "pch.h"
#include "EventManager.h"
#include "CallInfo.h"
#include "CollisionManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "GameObject.h"
#include "TimeManager.h"
EventManager* EventManager::g_Instance;


EventManager* EventManager::GetInstance()
{
	if (!g_Instance) {
		g_Instance = new EventManager;
		atexit(ReleaseInstance);
	}
	return g_Instance;
}

void EventManager::ReleaseInstance()
{
	if (g_Instance) {
		delete g_Instance;
		g_Instance = nullptr;
	}
}

void EventManager::Initialize(SceneManager* sceneManager, CollisionManager* collisionManager, TimeManager* timeManager)
{
	m_SceneManager = sceneManager;
	m_CollisionManager = collisionManager;
	m_TimeManager = timeManager;

	CallInfo setTimeScaleInfo{
		nullptr,
		[timeManager](std::any timeScale) {
			timeManager->SetTimeScale(std::any_cast<float>(timeScale));
		}
	};
	m_Database.insert({ "SetTimeScale", setTimeScaleInfo });

	CallInfo pauseGameInfo{
	nullptr,
	[sceneManager](std::any) {
		sceneManager->GetCurrentScene()->Pause();
	}
	};
	m_Database.insert({ "PauseGame", pauseGameInfo });

	CallInfo resumeGameInfo{
		nullptr,
		[sceneManager](std::any) {
			sceneManager->GetCurrentScene()->Resume();
		}
	};
	m_Database.insert({ "ResumeGame", resumeGameInfo });

	CallInfo loadSceneInfo{
		nullptr,
		[sceneManager, collisionManager](std::any sceneName) {
			collisionManager->Exit();
			sceneManager->LoadScene(std::any_cast<string>(sceneName));
			collisionManager->Enter();
		}
	};
	m_Database.insert({ "LoadScene", loadSceneInfo });

	CallInfo createObjectInfo{
		nullptr,
		[sceneManager,collisionManager](std::any gameObject) {
			GameObject* go = std::any_cast<GameObject*>(gameObject);
			sceneManager->GetCurrentScene()->AddGameObject(go);
			collisionManager->AddGameObject(go);
			go->Start();
		}
	};
	m_Database.insert({ "CreateObject", createObjectInfo });

	CallInfo destoryObjectInfo{
		nullptr,
		[sceneManager, collisionManager](std::any gameObject) {
			GameObject* go = std::any_cast<GameObject*>(gameObject);
			collisionManager->RemoveGameObject(go);
			sceneManager->GetCurrentScene()->RemoveGameObject(go);


		}
	};
	m_Database.insert({ "DestroyObject", destoryObjectInfo });

}

EventManager::EventManager() :
	m_SceneManager(nullptr),
	m_CollisionManager(nullptr),
	m_TimeManager(nullptr)
{

}

bool EventManager::AlreadyRegistered(string eventID, CallInfo callInfo)
{
	// assume they are not already registered
	bool alreadyRegistered = false;


	// 모든 이벤트 받을 수 있는 클라이언트를 찾는다.
	auto [iter, iterEnd] = m_Database.equal_range(eventID);

	// 클라이언트의 리스트중 뒤진다.
	for (; iter != iterEnd; iter++)
	{
		// 클라이언트가 이미 등록되어있으면
		if (iter->second.listener == callInfo.listener)
		{
			// 당장나가
			alreadyRegistered = true;
			break;
		}
	}

	return alreadyRegistered;
}

void EventManager::DispatchEvent(Event* event)
{


	//이 이벤트에 응답해야하는 모든 클라이언트를 가져온다.
	auto [iter, iterEnd] = m_Database.equal_range(event->GetEventID());

	// 이벤트에 응답할 수 있는 클라이언트의 리스트를 뒤진다.
	for (; iter != iterEnd; iter++)
	{
		if (iter->second.callbackFunc)
		{
			(iter->second.callbackFunc)(event->GetParameter());
		}
	}
}

void EventManager::RegisterClient(string eventID, CallInfo callInfo)
{
	// 클라이언트가 nullptr이거나 이미 등록되어있으면
	if (!callInfo.listener || AlreadyRegistered(eventID, callInfo))
	{
		// 나간다. 
		return;
	}

	m_AfterInsertDB.insert(make_pair(eventID, callInfo));

}

void EventManager::UnregisterClient(string eventID, MonoBehaviour* listener)
{

	// 이 이벤트에 등록되어있는 모든 클라이언트를 가져온다.
	auto [iter, iterEnd] = m_Database.equal_range(eventID);

	// 이벤트에 응답할 수 있는 클라이언트의 리스트를 뒤진다.
	for (; iter != iterEnd; iter++)
	{
		if (iter->second.listener == listener)
		{
			m_Database.erase(iter);
			break;
		}
	}
}

void EventManager::UnregisterAll(MonoBehaviour* client)
{
	auto iter = m_Database.begin();

	while (iter != m_Database.end())
	{
		/// 바로 삭제하면 난리를 치므로 지연삭제해준다.
		if (iter->second.listener == client)
		{
			iter->second.callbackFunc = nullptr;
		}
		iter++;
	}
}

void EventManager::SendEvent(string eventID, std::any data)
{
	Event newEvent(eventID, data);
	m_CurrentEvents.push_back(newEvent);
}

void EventManager::ProcessEvents()
{
	// 모든 이벤트에대해서 
	while (m_CurrentEvents.size())
	{
		// 처리하고
		DispatchEvent(&m_CurrentEvents.front());
		// 뺀다.
		m_CurrentEvents.pop_front();
	}

	/// 이벤트 삭제 지연처리
	auto iter = m_Database.begin();
	while (iter != m_Database.end())
	{
		if (!iter->second.callbackFunc)
		{
			iter = m_Database.erase(iter);
		}
		else
		{
			iter++;
		}
	}

	/// 이벤트 등록 지연처리
	for (auto& iter : m_AfterInsertDB)
	{
		m_Database.insert(iter);
	}
	m_AfterInsertDB.clear();
}

void EventManager::ClearEvents()
{
	m_CurrentEvents.clear();
}

void EventManager::Finalize()
{
	m_Database.clear();
	m_CurrentEvents.clear();

}

void EventManager::CheckCollisionType(OBJECT_TYPE a, OBJECT_TYPE b)
{
	m_CollisionManager->CheckCollisionType(a, b);
}

void EventManager::ResetCollisionMap()
{
	m_CollisionManager->ResetCollisionMap();
}

void EventManager::LoadScene(string sceneName)
{
	SendEvent("LoadScene", sceneName);
}

void EventManager::CreateObject(GameObject* gameObject)
{
	SendEvent("CreateObject", gameObject);
}

void EventManager::DestroyObject(GameObject* gameObject)
{
	SendEvent("DestroyObject", gameObject);
}


///
/// 2023.08.10
/// 작성자 : 정창도
/// 이벤트 브로드캐스팅 느낌을 위한
/// 이벤트매니저를 만든다
/// 이벤트 동작 처리기 function은 모노 비헤이비어에서만 작성할 수 있고 
/// 나머지 머 콜라이더나 씬 체인지나 애드 오브젝트 같은거는
/// 여기다가 그냥 쌩으로 코딩하려구 한다.
/// 
/// 
/// 
/// 



#pragma once


#include <string>
using std::string;
#include <map>
using std::multimap;
using std::pair;
#include <list>
using std::list;
#include "Event.h"
#include "CallInfo.h"
#include <functional>

#include "define.h"

using std::function;

class CollisionManager;
class SceneManager;
class Listener;
class MonoBehaviour;
class TimeManager;



class EventManager
{
private:

	/// 하위 계층에서 접근해야 하므로 싱글턴으로 만들어준다..
	/// 생성자
	EventManager();
	/// 소멸자
	~EventManager() {}
	/// 복사생성자
	EventManager(const EventManager& rhs) = delete;
	/// 대입연산자
	EventManager& operator=(const EventManager& rhs) = delete;

	/// 내부 헬퍼 함수
	bool AlreadyRegistered(string eventID, CallInfo callInfo);
	void DispatchEvent(Event* event);

public:
	/// 이벤트 매니저의 인스턴스를 리턴
	static EventManager* GetInstance();

	/// 이벤트 매니저의 인스턴스를 반납
	static void ReleaseInstance();

	/// 매니저의 포인터를 이니셜라이즈에서 보냄
	void Initialize(SceneManager* sceneManager, CollisionManager* collisionManager, TimeManager* timeManager);

	/// 이벤트를 받고 동작할 
	void RegisterClient(string eventID, CallInfo callInfo);

	/// 특정한 이벤트에서 클라이언트를 제외시킨다.
	void UnregisterClient(string eventID, MonoBehaviour* listener);

	/// 클라이언트에서 모든 이벤트를 제외시킨다.이거 추가 구현 필요
	void UnregisterAll(MonoBehaviour* client);

	/// 특정한 이벤트를 보낸다. // 이 때 오우너로 보낸다.
	void SendEvent(string eventID, std::any data);

	/// 모든 이벤트를 진행시킨다.
	void ProcessEvents();

	/// 이벤트를 클리어한다.
	void ClearEvents();

	/// 이벤트매니저 종료
	void Finalize();


public:
	/// 여기에 전역적으로 접근할 함수를 만든다.
	/// 신과 콜라이더에 관련된..
	/// 이벤트처리 느낌인가..
	void CheckCollisionType(OBJECT_TYPE a, OBJECT_TYPE b);
	void ResetCollisionMap();
	void LoadScene(string sceneName);
	void CreateObject(GameObject* gameObject);
	void DestroyObject(GameObject* gameObject);
private:
	/// 전역 객체
	static EventManager* g_Instance;

	/// 클라이언트와 그들의 이벤트에 대한 데이터베이스 
	multimap<string, CallInfo> m_Database;
	multimap<string, CallInfo> m_AfterInsertDB;

	/// 진행될 이벤트의 리스트
	list<Event> m_CurrentEvents;
	
	/// 들고있는 신매니저
	SceneManager* m_SceneManager;

	/// 돌고있는 콜리전 매니저
	/// 씬마다 콜라이더 다르게 적용시켜주고 싶다고해서 어쩔수 없이 전역적 개체인 이벤트매니저에 이거 넣어준다.
	CollisionManager* m_CollisionManager;

	TimeManager* m_TimeManager;

};


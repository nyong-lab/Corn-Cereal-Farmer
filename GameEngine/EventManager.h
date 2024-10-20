///
/// 2023.08.10
/// �ۼ��� : ��â��
/// �̺�Ʈ ��ε�ĳ���� ������ ����
/// �̺�Ʈ�Ŵ����� �����
/// �̺�Ʈ ���� ó���� function�� ��� �����̺����� �ۼ��� �� �ְ� 
/// ������ �� �ݶ��̴��� �� ü������ �ֵ� ������Ʈ �����Ŵ�
/// ����ٰ� �׳� ������ �ڵ��Ϸ��� �Ѵ�.
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

	/// ���� �������� �����ؾ� �ϹǷ� �̱������� ������ش�..
	/// ������
	EventManager();
	/// �Ҹ���
	~EventManager() {}
	/// ���������
	EventManager(const EventManager& rhs) = delete;
	/// ���Կ�����
	EventManager& operator=(const EventManager& rhs) = delete;

	/// ���� ���� �Լ�
	bool AlreadyRegistered(string eventID, CallInfo callInfo);
	void DispatchEvent(Event* event);

public:
	/// �̺�Ʈ �Ŵ����� �ν��Ͻ��� ����
	static EventManager* GetInstance();

	/// �̺�Ʈ �Ŵ����� �ν��Ͻ��� �ݳ�
	static void ReleaseInstance();

	/// �Ŵ����� �����͸� �̴ϼȶ������ ����
	void Initialize(SceneManager* sceneManager, CollisionManager* collisionManager, TimeManager* timeManager);

	/// �̺�Ʈ�� �ް� ������ 
	void RegisterClient(string eventID, CallInfo callInfo);

	/// Ư���� �̺�Ʈ���� Ŭ���̾�Ʈ�� ���ܽ�Ų��.
	void UnregisterClient(string eventID, MonoBehaviour* listener);

	/// Ŭ���̾�Ʈ���� ��� �̺�Ʈ�� ���ܽ�Ų��.�̰� �߰� ���� �ʿ�
	void UnregisterAll(MonoBehaviour* client);

	/// Ư���� �̺�Ʈ�� ������. // �� �� ����ʷ� ������.
	void SendEvent(string eventID, std::any data);

	/// ��� �̺�Ʈ�� �����Ų��.
	void ProcessEvents();

	/// �̺�Ʈ�� Ŭ�����Ѵ�.
	void ClearEvents();

	/// �̺�Ʈ�Ŵ��� ����
	void Finalize();


public:
	/// ���⿡ ���������� ������ �Լ��� �����.
	/// �Ű� �ݶ��̴��� ���õ�..
	/// �̺�Ʈó�� �����ΰ�..
	void CheckCollisionType(OBJECT_TYPE a, OBJECT_TYPE b);
	void ResetCollisionMap();
	void LoadScene(string sceneName);
	void CreateObject(GameObject* gameObject);
	void DestroyObject(GameObject* gameObject);
private:
	/// ���� ��ü
	static EventManager* g_Instance;

	/// Ŭ���̾�Ʈ�� �׵��� �̺�Ʈ�� ���� �����ͺ��̽� 
	multimap<string, CallInfo> m_Database;
	multimap<string, CallInfo> m_AfterInsertDB;

	/// ����� �̺�Ʈ�� ����Ʈ
	list<Event> m_CurrentEvents;
	
	/// ����ִ� �ŸŴ���
	SceneManager* m_SceneManager;

	/// �����ִ� �ݸ��� �Ŵ���
	/// ������ �ݶ��̴� �ٸ��� ��������ְ� �ʹٰ��ؼ� ��¿�� ���� ������ ��ü�� �̺�Ʈ�Ŵ����� �̰� �־��ش�.
	CollisionManager* m_CollisionManager;

	TimeManager* m_TimeManager;

};


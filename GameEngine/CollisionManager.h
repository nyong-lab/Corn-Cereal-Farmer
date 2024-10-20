#pragma once

#include "Bound.h"
#include "Collider.h"
#include "Manifold.h"
#include "DynamicTree.h"

class Collider;
class SceneManager;

// 이거 왜 전방선언 인식을 못함..?  임시로 Collider.h 포함 시켰다.
//union COLLIDER_KEY;



/// <summary>
/// 최초 작성일 : 2023.08.03
/// 작성자 : 김동일
/// 
/// 최종 수정일 : 2023.08.08
/// 수정자 : 김동일
///
/// 충돌 관리 매니저
/// 
/// 최종 수정일 2023.08.17
/// 수정자 :정창도
///
/// <summary>
class CollisionManager
{
public:
	friend class TestScene;
public:
	CollisionManager();
	~CollisionManager();

public:

	void Initialize(SceneManager* sceneManager);
	void Enter();
	void Update();
	void Exit();
	void Finalize();

public:
	void AddGameObject(GameObject* gameObject);
	void RemoveGameObject(GameObject* gameObject);
public:
	// 충돌 검사
	bool IsCollision(Collider* left, Collider* right);

	// 오브젝트 타입과 타입간의 충돌 설정
	void CheckCollisionType(OBJECT_TYPE a, OBJECT_TYPE b);
	bool CheckObjectType(OBJECT_TYPE a, OBJECT_TYPE b);
	void ResetCollisionMap();

	// 씬 변경 or 게임 종료시 호출
	void Clear() { m_Contacts.clear(); }


	
private:
	// 현재 프레임 충돌정보들을 저장
	list<Manifold> m_Contacts;

	// 이전 프레임 충돌정보를 저장
	std::unordered_map<unsigned long long, bool> m_KeyMap;

	std::list<Collider*> m_ColliderList;

	// 충돌 체크 (오브젝트 타입별로 충돌을 판단)
	int m_CheckCollisionMap[static_cast<int>(OBJECT_TYPE::END)] = { 0, }; 

	SceneManager* m_SceneManager;

	DynamicTree m_DynamicTree;
};


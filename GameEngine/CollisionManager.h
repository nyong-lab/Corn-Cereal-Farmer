#pragma once

#include "Bound.h"
#include "Collider.h"
#include "Manifold.h"
#include "DynamicTree.h"

class Collider;
class SceneManager;

// �̰� �� ���漱�� �ν��� ����..?  �ӽ÷� Collider.h ���� ���״�.
//union COLLIDER_KEY;



/// <summary>
/// ���� �ۼ��� : 2023.08.03
/// �ۼ��� : �赿��
/// 
/// ���� ������ : 2023.08.08
/// ������ : �赿��
///
/// �浹 ���� �Ŵ���
/// 
/// ���� ������ 2023.08.17
/// ������ :��â��
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
	// �浹 �˻�
	bool IsCollision(Collider* left, Collider* right);

	// ������Ʈ Ÿ�԰� Ÿ�԰��� �浹 ����
	void CheckCollisionType(OBJECT_TYPE a, OBJECT_TYPE b);
	bool CheckObjectType(OBJECT_TYPE a, OBJECT_TYPE b);
	void ResetCollisionMap();

	// �� ���� or ���� ����� ȣ��
	void Clear() { m_Contacts.clear(); }


	
private:
	// ���� ������ �浹�������� ����
	list<Manifold> m_Contacts;

	// ���� ������ �浹������ ����
	std::unordered_map<unsigned long long, bool> m_KeyMap;

	std::list<Collider*> m_ColliderList;

	// �浹 üũ (������Ʈ Ÿ�Ժ��� �浹�� �Ǵ�)
	int m_CheckCollisionMap[static_cast<int>(OBJECT_TYPE::END)] = { 0, }; 

	SceneManager* m_SceneManager;

	DynamicTree m_DynamicTree;
};


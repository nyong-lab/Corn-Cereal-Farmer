#include "pch.h"
#include "CollisionManager.h"

#include "GameObject.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Collider.h"
#include "CircleCollider.h"
#include "BoxCollider.h"
#include "Transform.h"
#include "Manifold.h"
#include "DynamicTree.h"

CollisionManager::CollisionManager()
{

}

CollisionManager::~CollisionManager()
{

}

void CollisionManager::Initialize(SceneManager* sceneManager)
{
	m_SceneManager = sceneManager;
}

void CollisionManager::Enter()
{
	const vector<GameObject*>& gameObjects = m_SceneManager->GetCurrentScene()->GetGameObjects();

	vector<GameObject*> founds;
	size_t index = 0;
	for (auto& motherObject : gameObjects)
	{
		founds.push_back(motherObject);
		// bst
		while (founds.size() > index)
		{
			vector<GameObject*>& rChild = founds[index]->GetObjectChildren();
			founds.insert(founds.end(), rChild.begin(), rChild.end());
			index++;
		}

	}
	for (auto& found : founds)
	{
		Collider* collider = found->GetComponent<Collider>();
		if (!collider) continue;
		m_DynamicTree.Add(collider);
		m_ColliderList.push_back(collider);
	}
}

void CollisionManager::Exit()
{
	for (auto& collider : m_ColliderList)
	{
		m_DynamicTree.Remove(collider);
	}
	m_ColliderList.clear();
}

/// <summary>
/// 업데이트
/// </summary>
void CollisionManager::Update()
{
	if (m_SceneManager->GetCurrentScene()->IsPause()) return;
#pragma region 동일코드

	// 부모 충돌 체크
// 	 	for (UINT row = 0; row < (UINT)OBJECT_TYPE::END; ++row)
// 	 	{
// 	 		for (UINT col = row; col < (UINT)OBJECT_TYPE::END; ++col)
// 	 		{
// 	 			const vector<GameObject*>& rowObject = m_SceneManager->GetCurrentScene()->GetGameObject(static_cast<OBJECT_TYPE>(row));
// 	 			const vector<GameObject*>& colObject = m_SceneManager->GetCurrentScene()->GetGameObject(static_cast<OBJECT_TYPE>(col));
// 	 
// 	 			// 충돌체가 있는지 체크 및 충돌체 정보를 만들기 위함.
// 	 			Collider* left;
// 	 			Collider* right;
// 	 
// 	 			// 모든 오브젝트에 대하여
// 	 			for (unsigned int i = 0; i < rowObject.size(); ++i)
// 	 			{
// 	 				vector<GameObject*> rowlook;
// 	 				rowlook.push_back(rowObject[i]);
// 	 				size_t rIndex = 0;
// 	 				while (rowlook.size() > rIndex)
// 	 				{
// 	 					vector<GameObject*>& rChild = rowlook[rIndex]->GetObjectChildren();
// 	 					if (!rChild.empty())
// 	 						rowlook.insert(rowlook.end(), rChild.begin(), rChild.end());
// 	 					rIndex++;
// 	 				}
// 	 
// 	 				for (unsigned int j = 0; j < colObject.size(); ++j)
// 	 				{
// 	 					vector<GameObject*> collook;
// 	 					collook.push_back(colObject[j]);
// 	 					size_t cIndex = 0;
// 	 					while (collook.size() > cIndex)
// 	 					{
// 	 						vector<GameObject*>& cChild = collook[cIndex]->GetObjectChildren();
// 	 						if (!cChild.empty())
// 	 							collook.insert(collook.end(), cChild.begin(), cChild.end());
// 	 						cIndex++;
// 	 					}
// 	 
// 	 
// 	 					for (auto& rrowObject : rowlook)
// 	 					{
// 	 						left = rrowObject->GetComponent<Collider>();
// 	 						if (left == nullptr)
// 	 							continue;
// 	 
// 	 						for (auto& ccolObject : collook)
// 	 						{
// 	 							right = ccolObject->GetComponent<Collider>();
// 	 							if (right == nullptr)
// 	 								continue;
// 	 
// 	 							if (left == right)
// 	 								continue;
// 	 
// 	 							if (m_CheckCollision
// 
// [static_cast<int>(rrowObject->GetObjectType())] & (1 << static_cast<int>(ccolObject->GetObjectType())))
// 	 							{
// 	 								COLLIDER_KEY colliderKey(left, right);
// 	 
// 	 								// 처음 체크 되는 경우
// 	 								if (m_CollisionInformations.find(colliderKey) == m_CollisionInformations.end())
// 	 								{
// 	 									CollisionInformation* info = new CollisionInformation(left, right);
// 	 
// 	 									// 맵에 insert
// 	 									m_CollisionInformations.insert({ colliderKey, info });
// 	 								}
// 	 							}
// 	 						}
// 	 					}
// 	 				}
// 	 			}
// 	 		}
// 	 	}
// 	 

#pragma endregion 동일코드



	m_Contacts.clear();

	m_DynamicTree.Update();

	using colPair = pair<Collider*, Collider*>;

	const list<colPair>& colPairList = m_DynamicTree.ComputePairs();

	for (auto& cPair : colPairList)
	{
		if (cPair.first == cPair.second)
		{
			continue;
		}
		if (m_CheckCollisionMap[static_cast<int>(cPair.first->GetGameObject()->GetObjectType())] & (1 << static_cast<int>(cPair.second->GetGameObject()->GetObjectType())))
		{

			Manifold manifold{ cPair.first, cPair.second };
			manifold.Solve();

			if (manifold.contactCount)
			{
				m_Contacts.emplace_back(manifold);
			}

		}
	}

	for (auto& iter : m_Contacts)
	{
		iter.SolveContact();
	}

	for (auto& iter : m_KeyMap)
	{
		iter.second = false;
	}

	// 모든 충돌에 대하여 
	for (auto& iter : m_Contacts)
	{
		// 충돌체 정보 만들기 
		Collider* collider1 = iter.collider1;
		Collider* collider2 = iter.collider2;

		COLLIDER_KEY colKey(collider1, collider2);

		GameObject* object1 = collider1->GetGameObject();
		GameObject* object2 = collider2->GetGameObject();

		Manifold collision1{};
		collision1.myCollider = collider1;
		collision1.otherCollider = collider2;
		collision1.otherObject = object2;

		Manifold collision2{};
		collision2.myCollider = collider2;
		collision2.otherCollider = collider1;
		collision2.otherObject = object1;

		if (m_KeyMap.find(colKey.Key) == m_KeyMap.end())
		{
			m_KeyMap.emplace(colKey.Key, true);
			iter.collider1->GetGameObject()->OnCollisionEnter(collision1);
			iter.collider2->GetGameObject()->OnCollisionEnter(collision2);
			iter.collider1->SetCollision(true);
			iter.collider2->SetCollision(true);
		}
		else if (m_KeyMap[colKey.Key] == false)
		{
			m_KeyMap[colKey.Key] = true;
			iter.collider1->GetGameObject()->OnCollisionStay(collision1);
			iter.collider2->GetGameObject()->OnCollisionStay(collision2);
		}
	}

	auto iter = m_KeyMap.begin();
	while (iter != m_KeyMap.end())
	{
		if (iter->second == false)
		{
			Collider* collider1 = nullptr;
			Collider* collider2 = nullptr;
			GameObject* object1 = nullptr;
			GameObject* object2 = nullptr;
			COLLIDER_KEY colKey(iter->first);
			for (auto& collider : m_ColliderList)
			{
				if (collider->GetID() == colKey.ColliderID1)
				{
					collider1 = collider;
					object1 = collider1->GetGameObject();
				}

				else if (collider->GetID() == colKey.ColliderID2)
				{
					collider2 = collider;
					object2 = collider2->GetGameObject();
				}

			}

			Manifold collision1{};
			collision1.myCollider = collider1;
			collision1.otherCollider = collider2;
			collision1.otherObject = object2;

			Manifold collision2{};
			collision2.myCollider = collider2;
			collision2.otherCollider = collider1;
			collision2.otherObject = object1;
			if (collider1) collider1->GetGameObject()->OnCollisionExit(collision1);
			if (collider2) collider2->GetGameObject()->OnCollisionExit(collision2);
			iter = m_KeyMap.erase(iter);
		}
		else
		{
			iter++;
		}

	}


}

void CollisionManager::Finalize()
{
}

void CollisionManager::AddGameObject(GameObject* gameObject)
{
	vector<GameObject*> founds;
	size_t index = 0;
	founds.push_back(gameObject);
	// bst
	while (founds.size() > index)
	{
		vector<GameObject*>& rChild = founds[index]->GetObjectChildren();
		founds.insert(founds.end(), rChild.begin(), rChild.end());
		index++;
	}

	for (auto& found : founds)
	{
		Collider* collider = found->GetComponent<Collider>();
		if (!collider) continue;
		m_DynamicTree.Add(collider);
		m_ColliderList.push_back(collider);
	}
}

void CollisionManager::RemoveGameObject(GameObject* gameObject)
{
	vector<GameObject*> founds;
	size_t index = 0;
	founds.push_back(gameObject);
	// bst
	while (founds.size() > index)
	{
		vector<GameObject*>& rChild = founds[index]->GetObjectChildren();
		founds.insert(founds.end(), rChild.begin(), rChild.end());
		index++;
	}

	for (auto& found : founds)
	{
		Collider* collider = found->GetComponent<Collider>();
		if (!collider) continue;
		m_DynamicTree.Remove(collider);
		m_ColliderList.remove_if([collider](Collider* col)->bool { return col == collider; });
	}

}

/// <summary>
/// 충돌 체크
/// </summary>
bool CollisionManager::IsCollision(Collider* left, Collider* right)
{
	return left->Collides(right);

}
/// <summary>
/// 비트 플래그를 이용한 충돌 설정
/// </summary>
void CollisionManager::CheckCollisionType(OBJECT_TYPE a, OBJECT_TYPE b)
{
	m_CheckCollisionMap[static_cast<int>(a)] |= 1 << static_cast<int>(b);
	m_CheckCollisionMap[static_cast<int>(b)] |= 1 << static_cast<int>(a);
}

/// <summary>
/// 충돌 가능한 타입인지 체크
/// </summary>
bool CollisionManager::CheckObjectType(OBJECT_TYPE a, OBJECT_TYPE b)
{
	return m_CheckCollisionMap[static_cast<int>(a)] & 1 << static_cast<int>(b);
}

/// <summary>
/// 모든 충돌 판정 0 으로 리셋
/// </summary>
void CollisionManager::ResetCollisionMap()
{
	for (int i = 0; i < static_cast<int>(OBJECT_TYPE::END); i++)
	{
		m_CheckCollisionMap[i] = 0;
	}
}

#include "pch.h"
#include "Scene.h"
#include "GameObject.h"
#include "EventManager.h"
/// 임시
#include "Transform.h"
#include "MonoBehaviour.h"

#include "Input.h"
#include "ResourceManager.h"
#include "Image.h"

Scene::Scene(string name) :
	m_Name(name)
{

}

Scene::Scene() :
	m_Name(typeid(*this).name())
{

}

Scene::~Scene()
{

}

void Scene::Exit()
{

	for (auto& gameObject : m_GameObjects)
	{
		if (gameObject != nullptr)
		{
			gameObject->Finalize();
			delete gameObject;
		}
	}
	m_GameObjects.clear();
}

void Scene::Start()
{

	for (auto& gameObject : m_GameObjects)
	{
		gameObject->Start();
	}
}

void Scene::Update(float deltaTime)
{

	for (auto gameObject : m_GameObjects)
	{
		if (gameObject->GetObjectType() < OBJECT_TYPE::UI && !m_IsPaused)
		{
			gameObject->Update(deltaTime);
		}

		if (gameObject->GetObjectType() >= OBJECT_TYPE::UI)
		{
			gameObject->Update(deltaTime);
		}
	}


}

void Scene::FixedUpdate(float deltaTime)
{

	for (auto gameObject : m_GameObjects)
	{
		if (gameObject->GetObjectType() < OBJECT_TYPE::UI && !m_IsPaused)
		{
			gameObject->FixedUpdate(deltaTime);
		}

		if (gameObject->GetObjectType() >= OBJECT_TYPE::UI)
		{
			gameObject->FixedUpdate(deltaTime);
		}
	}

}

void Scene::Render()
{

	GraphicsEngine::GetInstance()->DrawEffectBufferBegin();

	for (auto gameObject : m_GameObjects)
	{
		if (gameObject->GetObjectType() == OBJECT_TYPE::CAMERA)
		{
			gameObject->Render();
		}
	}

	GraphicsEngine::GetInstance()->DrawEffectBufferEnd();

	for (auto uis : m_GameObjects)
	{
		if (uis->GetObjectType() == OBJECT_TYPE::UI)
		{
			uis->Render();
		}
	}


#pragma region 렌더나중
	// 	vector<GameObject*> founds;
	// 
	// 	for (auto& motherObject : m_GameObjects)
	// 	{
	// 		if (motherObject->GetObjectType() != OBJECT_TYPE::UI) continue;
	// 		founds.push_back(motherObject);
	// 		size_t rIndex = 0;
	// 		// bst
	// 		while (founds.size() > rIndex)
	// 		{
	// 			vector<GameObject*>& rChild = founds[rIndex]->GetObjectChildren();
	// 			founds.insert(founds.end(), rChild.begin(), rChild.end());
	// 			rIndex++;
	// 		}
	// 	}
#pragma endregion
}

void Scene::DebugRender()
{
	for (auto gameObject : m_GameObjects)
	{
		if (gameObject->GetObjectType() == OBJECT_TYPE::CAMERA)
		{
			gameObject->DebugRender();
		}
	}
	for (auto uis : m_GameObjects)
	{
		if (uis->GetObjectType() == OBJECT_TYPE::UI)
		{
			uis->DebugRender();
		}
	}
}

void Scene::AddGameObject(GameObject* object)
{
	object->SetScene(this);
/*	int objectType = static_cast<int>(object->GetObjectType());*/
	m_GameObjects.push_back(object);
}

void Scene::RemoveGameObject(GameObject* object)
{
	object->Finalize();
	for (auto iter = m_GameObjects.begin(); iter != m_GameObjects.end(); ++iter)
	{
		if ((*iter) == object)
		{
			m_GameObjects.erase(iter);
			break;
		}
	}
	delete object;
}

//void Scene::DestroyGameObject(GameObject* object)
//{
//	int objectType = static_cast<int>(object->GetObjectType());
//
//	auto& objects = m_GameObjects[objectType];
//	auto it = std::find(objects.begin(), objects.end(), object);
//
//	assert(it != objects.end() && "삭제시킬 오브젝트를 씬 오브젝트 배열에서 못찾음");
//
//	if (it != objects.end())
//	{
//		delete* it;
//		objects.erase(it);
//	}
//}

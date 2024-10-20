#pragma once

#include "Component.h"

#include <assert.h>
#include<vector>
#include <string>
#include <vector>

using std::string;
using std::vector;

class Transform;
class Scene;
class Collider;
struct Manifold;

enum class OBJECT_TYPE;

/// <summary>
/// ���� �ۼ��� : 2023.07.28
/// �ۼ��� : ��â��
/// 
/// ���� ������ : 2023.07.31
/// ������ : �赿�� 
/// 
/// ��� ������Ʈ�� �θ� Ŭ����
/// ���� ������Ʈ�� �� �����̰� ������Ʈ ��ǰ���� �ϳ��ϳ� ���δ�
/// <summary>
class GameObject
{
public:
	GameObject(string name, OBJECT_TYPE type);
	virtual ~GameObject();

public:
	virtual void Start();
	virtual void Update(float deltaTime);
	void FixedUpdate(float deltaTime);
	void Render();
	void DebugRender();
	void Finalize();

public:
	// Get - Set
	OBJECT_TYPE GetObjectType() const { return m_Type; }
	const string& GetName() const { return m_Name; }
	Scene* GetScene() const { return m_Scene; }
	Transform* GetTransform() const { return m_Transform; }
	bool GetActivate() const { return m_IsActivate; }

	void SetScene(Scene* scene) { m_Scene = scene; }
	virtual void SetActivate(bool val) { m_IsActivate = val; }

public:
	// �������� Get - Set
	GameObject* GetObjectParent();
	vector<GameObject*>& GetObjectChildren();
	GameObject* GetObjectChild(const string& name);
	Transform* GetTransformParent();
	vector<Transform*>& GetTransformChildren();

	void AddObjectChild(GameObject* objectChild);
	void SetObjectParent(GameObject* objectParent);
	void AddTransformChild(Transform* transformChild);
	void SetTransformParent(Transform* transformParent);
	
public:
	// �浹 ���� �Լ�
	void OnCollisionEnter(const Manifold& collision);
	void OnCollisionStay(const Manifold& collision);
	void OnCollisionExit(const Manifold& collision);

public:
	// ���� ���ڱ� 3���� ����? ���Ŀ� �ٽ� ��������  
	// �̺�Ʈ ó���ؼ� �������Ѿ� �������� ������ ����
	//void DestroyObject();
	void DestroyAllComponent();

public:
	template <typename T>
	T* AddComponent(T* component);
	template <typename T>
	T* GetComponent();

protected:
	OBJECT_TYPE m_Type;

	const string m_Name;
	bool m_IsActivate = true;
	Scene* m_Scene = nullptr;

	Transform* m_Transform;
	vector<Component*> m_Components;

	GameObject* m_ObjectParent = nullptr;
	vector<GameObject*> m_ObjectChildren;
};


template <typename T>
T* GameObject::AddComponent(T* component)
{
	if (GetComponent<T>() != nullptr)
	{
		assert(nullptr && "���� ������Ʈ �ϴ��� 2�� �߰����� ������");
		return nullptr;
	}
	m_Components.push_back(component);
	component->SetGameObject(this);
	component->SetTransform(this->m_Transform);
	return component;
}

template <typename T>
T* GameObject::GetComponent()
{
	for (auto& component : m_Components)
	{
		T* temp = dynamic_cast<T*>(component);

		if (temp == nullptr)
		{
			continue;
		}

		return temp;
	}

	return nullptr;
}
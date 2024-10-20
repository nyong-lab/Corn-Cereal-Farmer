#include "pch.h"

#include "GameObject.h"
#include "Transform.h"
#include "Scene.h"
#include "EventManager.h"
#include "MonoBehaviour.h"

/// <summary>
/// 생성자
/// </summary>
GameObject::GameObject(string name, OBJECT_TYPE type)
	: m_Name(name)
	, m_Type(type)
	, m_Components{}
	, m_ObjectChildren{}
{
	// 모든 오브젝트는 Transform 컴포넌트를 들고 있는다.
	m_Transform = new Transform();
	AddComponent(m_Transform);
}

/// <summary>
/// 소멸자
/// </summary>
GameObject::~GameObject()
{

}

/// <summary>
/// 오브젝트 생성시 호출
/// </summary>
void GameObject::Start()
{


	for (Component* component : m_Components)
	{
		component->Start();
	}
	for (auto objectChildren : m_ObjectChildren)
	{
		objectChildren->Start();
	}
}

/// <summary>
/// 업데이트
/// </summary>
void GameObject::Update(float deltaTime)
{
	for (Component* component : m_Components)
	{
		component->Update(deltaTime);
	}
	for (auto objectChildren : m_ObjectChildren)
	{
		objectChildren->Update(deltaTime);
	}
}

/// <summary>
/// 물리 충돌
/// </summary>
void GameObject::FixedUpdate(float deltaTime)
{
	for (Component* component : m_Components)
	{
		component->FixedUpdate(deltaTime);
	}

	for (auto objectChildren : m_ObjectChildren)
	{
		objectChildren->FixedUpdate(deltaTime);
	}
}

void GameObject::Render()
{
	// TODO : 임시

	for (Component* component : m_Components)
	{
		component->Render();
	}
	for (auto objectChildren : m_ObjectChildren)
	{
		objectChildren->Render();
	}
}

void GameObject::DebugRender()
{
	for (Component* component : m_Components)
	{
		component->DebugRender();
	}
	for (auto objectChildren : m_ObjectChildren)
	{
		objectChildren->DebugRender();
	}
}

/// <summary>
/// 명시적 해제
/// </summary>
void GameObject::Finalize()
{
	//StateMachine을 삭제
	

	MonoBehaviour* Mono = GetComponent<MonoBehaviour>();
	if (Mono)
	{
		EventManager::GetInstance()->UnregisterAll(Mono);
	}

	for (auto objectChildren : m_ObjectChildren)
	{
		objectChildren->Finalize();
		delete objectChildren;
	}


	DestroyAllComponent();
}


GameObject* GameObject::GetObjectParent()
{
	return m_ObjectParent;
}

vector<GameObject*>& GameObject::GetObjectChildren()
{
	return m_ObjectChildren;
}

GameObject* GameObject::GetObjectChild(const string& name)
{
	for (GameObject* child : m_ObjectChildren)
	{
		if (child->GetName() == name)
		{
			return child;
		}
	}

	//assert(nullptr && "일치하는 이름이 없어 :(");

	return nullptr; // 일치하는 자식 오브젝트를 찾지 못한 경우
}

Transform* GameObject::GetTransformParent()
{
	Transform* transform = m_Transform;
	assert(transform);

	return transform->GetParent();
}

vector<Transform*>& GameObject::GetTransformChildren()
{
	Transform* transform = m_Transform;
	assert(transform);

	return transform->GetChildren();
}

void GameObject::AddObjectChild(GameObject* objectChild)
{
// 	m_Scene->AddGameObject(objectChild);

	m_ObjectChildren.push_back(objectChild);
	objectChild->SetObjectParent(this);

	AddTransformChild(objectChild->GetTransform());
	
}

void GameObject::AddTransformChild(Transform* child)
{
	Transform* transform = m_Transform;
	assert(transform);

	transform->AddChild(child);
}

void GameObject::SetObjectParent(GameObject* objectParent)
{
	m_ObjectParent = objectParent;
}

void GameObject::SetTransformParent(Transform* parent)
{
	Transform* transform = m_Transform;
	assert(transform);

	transform->SetParent(parent);
}

void GameObject::OnCollisionEnter(const Manifold& collision)
{
	for (Component* component : m_Components)
	{
		component->OnCollisionEnter(collision);
	}
}

void GameObject::OnCollisionStay(const Manifold& collision)
{
	for (Component* component : m_Components)
	{
		component->OnCollisionStay(collision);
	}
}

void GameObject::OnCollisionExit(const Manifold& collision)
{
	for (Component* component : m_Components)
	{
		component->OnCollisionExit(collision);
	}
}

//void GameObject::DestroyObject()
//{
//	Finalize();
//
//	GetScene()->DestroyGameObject(this);
//}

/// <summary>
/// 할당된 컴포넌트 해제
void GameObject::DestroyAllComponent()
/// </summary>
{
	for (Component* component : m_Components)
	{
		if (component != nullptr)
		{
			component->Finalize();
			delete component;
		}
	}
	m_Components.clear();
}
#pragma once

#include <string>
using std::string;

class GameObject;
class Transform;
class CollisionManager;
class Collider;

struct Manifold;

/// <summary>
/// ���� �ۼ��� : 2023.07.31
/// �ۼ��� : �赿�� 
/// 
/// ��� ������Ʈ�� �θ� Ŭ����
/// <summary>
/// 
class Component
{
public:
	Component();
	Component(string name);
	virtual ~Component();

public:
	virtual void Start() {};
	virtual void Update(float deltaTime) {};
	virtual void FixedUpdate(float deltaTime) {};
	virtual void Render() {};
	virtual void DebugRender() {};
	virtual void Finalize() {};

public:
	// �浹 ���� �Լ�
	virtual void OnCollisionEnter(const Manifold& collision) {};
	virtual void OnCollisionStay(const Manifold& collision) {};
	virtual void OnCollisionExit(const Manifold& collision) {};

public:
	// Get - Set
	GameObject* GetGameObject() const { return m_GameObject; }
	Transform* GetTransform() const { return m_Transform; }
	const string& GetName() const { return m_Name; }

	void SetGameObject(GameObject* gameObject) { m_GameObject = gameObject; }
	void SetTransform(Transform* transform) { m_Transform = transform; }

protected:
	GameObject* m_GameObject = nullptr;
	Transform* m_Transform = nullptr;
	
	// ������Ʈ Ŭ������ (RTTI ����)
	const string m_Name = {};
};
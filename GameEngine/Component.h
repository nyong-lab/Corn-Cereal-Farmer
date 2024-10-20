#pragma once

#include <string>
using std::string;

class GameObject;
class Transform;
class CollisionManager;
class Collider;

struct Manifold;

/// <summary>
/// 최초 작성일 : 2023.07.31
/// 작성자 : 김동일 
/// 
/// 모든 컴포넌트의 부모 클래스
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
	// 충돌 관련 함수
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
	
	// 컴포넌트 클래스명 (RTTI 위함)
	const string m_Name = {};
};
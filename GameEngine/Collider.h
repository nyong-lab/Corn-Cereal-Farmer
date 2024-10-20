#pragma once


#include "Component.h"
#include "ZicoMath.h"
#include "Bound.h"
#include <any>

class CircleCollider;
class BoxCollider;

/// <summary>
/// ���� �ۼ��� : 2023.08.02
/// �ۼ��� : �赿��
/// 
/// ���� ������ : 2023.08.08
/// ������ : �赿��
/// 
/// �浹ü �������̽�
/// 
/// 
/// <summary>
class Collider : public Component
{
public:
	Collider(string name);
	virtual ~Collider();

public:
	virtual void Start() override {};
	virtual void Update(float deltaTime) override {};
	virtual void FixedUpdate(float deltaTime) override {};
	virtual void Render() override {};
	virtual void Finalize() override {};
	virtual void DebugRender() override {};

public:
	// Get - Set
	Vector2 GetOffset() const { return m_Offset; }	
	bool GetCollision() const { return m_IsCollision; }
	bool GetActive() const { return m_IsActive; }
	int GetCurrentCollisonCount() { return m_CurrentCollisionCount; }
	Bound GetBound() const { return m_Bound; }
	void SetBound(Bound bound) { m_Bound = bound; }
	void SetTrigger(bool val) { m_IsTrigger = val; }
	bool IsTrigger() { return m_IsTrigger; }

	void SetOffset(Vector2 offset) { m_Offset = offset; }
	void SetCollision(bool val) { m_IsCollision = val; }
	void SetActive(bool val) { m_IsActive = val; }
	void SetUserdata(std::any data) { m_Userdata = data; }
	std::any GetUserdata() { return m_Userdata; }
	const unsigned int GetID() const { return m_ID; }


public:
	// �浹 ���� �Լ�
	virtual bool Collides(CircleCollider* circle) abstract;
	virtual bool Collides(BoxCollider* box) abstract;
	bool Collides(Collider* collider);

	virtual Vector2 FindFurthestVertice(Vector2 direction) abstract;
	virtual int FindFurthestVerticeIndex(Vector2 direction) abstract;

protected:
	int m_CurrentCollisionCount = 0; // ���� �浹���� �浹ü ����   (�浹 �� �ݶ��̴� �� ������ ����)

private:
	const unsigned int m_ID;
	static unsigned int m_Index;

	Vector2 m_Offset = { 0.f,0.f }; // ������Ʈ �������� �󸶳� ������ �ִ���
	bool m_IsCollision = false;  // �浹 ���ΰ�
	bool m_IsActive = true; // �ݶ��̴� Ȱ��ȭ ����
	Bound m_Bound = {};

	bool m_IsTrigger;

public:
	std::any m_Userdata;
};

/// ������ ��ȯ���� ����
/// �ݶ��̴� �浹���� ������ Key���� �����
// struct �� ���ϰ� union ���� �ϴ� ������?
// Collider key �� ������? 
union COLLIDER_KEY
{
	COLLIDER_KEY(Collider* collider1, Collider* collider2) : Key(0)
	{
		ColliderID1 = min(collider1->GetID(), collider2->GetID());
		ColliderID2 = max(collider1->GetID(), collider2->GetID());
	}

	COLLIDER_KEY(unsigned long long num) : Key(num)
	{

	}

	struct
	{
		unsigned int ColliderID1;
		unsigned int ColliderID2;
	};

	unsigned long long Key;

};

/// ColliderKey�� �ʿ��� ����ϴ� ���ľ˰���
inline bool operator <(const COLLIDER_KEY& colliderKey1, const COLLIDER_KEY& colliderKey2)
{
	if (colliderKey1.Key < colliderKey2.Key)
		return true;

	return false;
}
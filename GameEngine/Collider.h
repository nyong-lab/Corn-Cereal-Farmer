#pragma once


#include "Component.h"
#include "ZicoMath.h"
#include "Bound.h"
#include <any>

class CircleCollider;
class BoxCollider;

/// <summary>
/// 최초 작성일 : 2023.08.02
/// 작성자 : 김동일
/// 
/// 최종 수정일 : 2023.08.08
/// 수정자 : 김동일
/// 
/// 충돌체 인터페이스
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
	// 충돌 관련 함수
	virtual bool Collides(CircleCollider* circle) abstract;
	virtual bool Collides(BoxCollider* box) abstract;
	bool Collides(Collider* collider);

	virtual Vector2 FindFurthestVertice(Vector2 direction) abstract;
	virtual int FindFurthestVerticeIndex(Vector2 direction) abstract;

protected:
	int m_CurrentCollisionCount = 0; // 현재 충돌중이 충돌체 갯수   (충돌 시 콜라이더 색 변경을 위함)

private:
	const unsigned int m_ID;
	static unsigned int m_Index;

	Vector2 m_Offset = { 0.f,0.f }; // 오브젝트 기준으로 얼마나 떨어져 있는지
	bool m_IsCollision = false;  // 충돌 중인가
	bool m_IsActive = true; // 콜라이더 활성화 여부
	Bound m_Bound = {};

	bool m_IsTrigger;

public:
	std::any m_Userdata;
};

/// 기태형 형환이형 고마워
/// 콜라이더 충돌쌍을 가지고 Key값을 만든다
// struct 로 안하고 union 으로 하는 이유는?
// Collider key 에 역할은? 
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

/// ColliderKey의 맵에서 사용하는 정렬알고리즘
inline bool operator <(const COLLIDER_KEY& colliderKey1, const COLLIDER_KEY& colliderKey2)
{
	if (colliderKey1.Key < colliderKey2.Key)
		return true;

	return false;
}
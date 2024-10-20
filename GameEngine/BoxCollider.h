#pragma once

#include "Collider.h"


/// <summary>
/// 최초 작성일 : 2023.08.03
/// 작성자 : 김동일
/// 
/// 최종 수정일 : 2023.08.08
/// 수정자 : 김동일
/// 
/// 박스 콜라이더 
/// </summary>
class BoxCollider : public Collider
{
public:
	BoxCollider(Vector2 size);
	~BoxCollider();

public:
	virtual void Start() override;
	virtual void Update(float deltaTime) override;
	virtual void FixedUpdate(float deltaTime) override;
	virtual void Render() override;
	virtual void DebugRender() override;
	virtual void Finalize() override;

public:
	// Get - Set
 	Vector2 GetSize() const { return m_Size; }
 	void SetSize(Vector2 size) { m_Size = size; }

public:
	// 충돌 관련 함수
	virtual void OnCollisionEnter(const Manifold& collision) override;
	virtual void OnCollisionStay(const Manifold& collision) override;
	virtual void OnCollisionExit(const Manifold& collision) override;

public:
	virtual bool Collides(CircleCollider* circle) override;
	virtual bool Collides(BoxCollider* box) override;
	virtual Vector2 FindFurthestVertice(Vector2 direction) override;
	virtual int FindFurthestVerticeIndex(Vector2 direction) override;

private:
	Vector2 m_Size = { 100,100 };

	// 회전 가능한 박스인지 여부를 체크해서 AABB,OBB등의 처리
	// 는 안할거임
	// bool m_IsRotatable = true;
};
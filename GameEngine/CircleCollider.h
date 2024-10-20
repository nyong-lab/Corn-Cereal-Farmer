#pragma once

#include "Collider.h"


/// <summary>
/// ���� �ۼ��� : 2023.08.03
/// �ۼ��� : �赿��
/// 
/// ���� ������ : 2023.08.08
/// ������ : �赿��
/// 
/// ���� �ݶ��̴� 
/// </summary>
class CircleCollider : public Collider
{
public:
	CircleCollider(float radius);
	~CircleCollider();

public:
	virtual void Start() override;
	virtual void Update(float deltaTime) override;
	virtual void FixedUpdate(float deltaTime) override;
	virtual void Render() override;
	virtual void DebugRender() override;
	virtual void Finalize() override;

public:
	// Get - Set
	float GetRadius() const { return m_Radius; }

	void SetRadius(float radius) { m_Radius = radius; }

public:
	// �浹 ���� �Լ�
	virtual void OnCollisionEnter(const Manifold& collision) override;
	virtual void OnCollisionStay(const Manifold& collision) override;
	virtual void OnCollisionExit(const Manifold& collision) override;

public:
	virtual bool Collides(CircleCollider* circle) override;
	virtual bool Collides(BoxCollider* box) override;
	virtual Vector2 FindFurthestVertice(Vector2 direction) override;
	virtual int FindFurthestVerticeIndex(Vector2 direction) override { return (int)direction.x * 10000 + (int)direction.y; }


private:
	float m_Radius = 100.f;
};
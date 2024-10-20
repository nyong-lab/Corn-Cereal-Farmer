#pragma once

#include "Collider.h"


/// <summary>
/// ���� �ۼ��� : 2023.08.03
/// �ۼ��� : �赿��
/// 
/// ���� ������ : 2023.08.08
/// ������ : �赿��
/// 
/// �ڽ� �ݶ��̴� 
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
	// �浹 ���� �Լ�
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

	// ȸ�� ������ �ڽ����� ���θ� üũ�ؼ� AABB,OBB���� ó��
	// �� ���Ұ���
	// bool m_IsRotatable = true;
};
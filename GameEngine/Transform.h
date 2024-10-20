#pragma once

#include "Component.h"
#include "ZicoMath.h"
#include <vector>
#include <d2d1.h>
#pragma comment(lib, "d2d1.lib")


using std::vector;

/// <summary>
/// ���� �ۼ��� : 2023.07.31
/// �ۼ��� : �赿�� 
/// 
/// ���� ������ : 2023.08.02
/// ������ : �赿��
/// 
/// ��ġ,ũ��,�θ� �ڽİ��踦 �����ϴ� Ŭ����
/// 
/// ���� ������ : 2023.08.13
/// ������ : �ڿ���
/// 
/// ������ 2D ������Ʈ�� ��� Rect Transform�� ����ϱ� ������
/// Transform�� Size�� �־���
/// * ���� ���� �Ϸ�
/// 
/// <summary>

// ���� ��ǥ�迡�� �θ��� ��ǥ��� �Ѿ�°��� ���� SRT(scale,rotation,translation) �� ���� ������ ���̰� 
// (SRT ���ϴ� ���� �߿���!!)
// �� �׷��� �Ѿ ��ǥ�迡�� �Ȱ��� SRT ������ ����ؼ� �� ������� �ٽ� �θ��� ��ǥ��� �Ѿ�� ��ȯ���.
// ������ �ش� ��ǥ�迡�� �� �ٽ� SRT �������� �� ��ȯ����� �ִµ� �� ��ǥ���� �θ� ���ٸ�?
// �� ��ȯ����� �� ���� ��ȯ���!

class Transform : public Component
{
public:
	Transform();
	~Transform();
public:
	virtual void Start() override;
	virtual void Update(float deltaTime) override;
	virtual void FixedUpdate(float deltaTime) override;
	virtual void Render() override;
	virtual void DebugRender() override;
	virtual void Finalize() override;

public:
	void UpdateTransform();

	// ���� ��ȯ ��İ� �� ����� ���� ���
	void CalculateWVMatrix();

public:
	// Get - Set
	Vector2 GetLocalScale() const { return m_LocalScale; }
	Vector2 GetLocalPosition() const { return m_LocalPosition; }
	float GetLocalRotation() const { return m_LocalRotation; }

	void SetLocalScale(const Vector2& localScale) {
		m_LocalScale = localScale;
		UpdateTransform();
	}
	void SetLocalRotation(const float& localRotation) {
		m_LocalRotation = localRotation;
		UpdateTransform();
	}
	void SetLocalPosition(const Vector2& localPosition) {
		m_LocalPosition = localPosition;
		UpdateTransform();
	}

	Vector2 GetWorldPosition() const { return Vector2{ m_MatrixWorld.dx, m_MatrixWorld.dy }; }

	D2D1::Matrix3x2F GetLocalMatrix() { return m_MatrixLocal; }
	D2D1::Matrix3x2F GetWorldMatrix() { return m_MatrixWorld; }

public:
	void SetSize(Vector2 size) { m_Size = size; }
	Vector2 GetSize() { return m_Size; }

public:
	// ���� ����
	bool HasParent() const { return m_Parent != nullptr; }

	Transform* GetParent() const { return m_Parent; }
	void SetParent(Transform* parent) { m_Parent = parent; }

	vector<Transform*>& GetChildren() { return m_Children; }
	void AddChild(Transform* child);

	void SetViewMatrix(D2D1::Matrix3x2F viewMatrix) { m_ViewMatrix = viewMatrix; }

private:
	// �θ� ��������� �ϴ� ���� ���� ��ǥ
	Vector2 m_LocalScale = { 1.f,1.f };
	float m_LocalRotation = 0.f;
	Vector2 m_LocalPosition = { 0.f,0.f };

	// �θ� ��ǥ��� �Ѿ�� ��ȯ ���
	D2D1::Matrix3x2F m_MatrixLocal = D2D1::Matrix3x2F::Identity();

	// ���� ��ǥ��� �Ѿ�� ��ȯ ���
	D2D1::Matrix3x2F m_MatrixWorld = D2D1::Matrix3x2F::Identity();

	// ���� ��ǥ�踦 ī�޶� ��ǥ��� �Ѿ�� ��ȯ ���
	D2D1::Matrix3x2F m_ViewMatrix = D2D1::Matrix3x2F::Identity();

	// ���� ��ȯ ��İ� �� ��ȯ ����� ���� ���
	D2D1::Matrix3x2F m_MVMatrix = D2D1::Matrix3x2F::Identity();

private:
	Transform* m_Parent = nullptr;
	vector<Transform*> m_Children;

private:
	Vector2 m_Size;
};
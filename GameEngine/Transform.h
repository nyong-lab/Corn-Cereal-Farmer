#pragma once

#include "Component.h"
#include "ZicoMath.h"
#include <vector>
#include <d2d1.h>
#pragma comment(lib, "d2d1.lib")


using std::vector;

/// <summary>
/// 최초 작성일 : 2023.07.31
/// 작성자 : 김동일 
/// 
/// 최종 수정일 : 2023.08.02
/// 수정자 : 김동일
/// 
/// 위치,크기,부모 자식관계를 관리하는 클래스
/// 
/// 최종 수정일 : 2023.08.13
/// 수정자 : 박연하
/// 
/// 어차피 2D 프로젝트는 모두 Rect Transform을 사용하기 때문에
/// Transform에 Size를 넣었다
/// * 팀장 승인 완료
/// 
/// <summary>

// 로컬 좌표계에서 부모의 좌표계로 넘어가는것은 로컬 SRT(scale,rotation,translation) 를 전부 곱해준 것이고 
// (SRT 곱하는 순서 중요함!!)
// 또 그렇게 넘어간 좌표계에서 똑같이 SRT 공식을 사용해서 얻어낸 결과물이 다시 부모의 좌표계로 넘어가는 변환행렬.
// 하지만 해당 좌표계에서 또 다시 SRT 공식으로 얻어낸 변환행렬이 있는데 그 좌표계의 부모가 없다면?
// 그 변환행렬은 즉 월드 변환행렬!

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

	// 월드 변환 행렬과 뷰 행렬을 곱한 결과
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
	// 계층 관계
	bool HasParent() const { return m_Parent != nullptr; }

	Transform* GetParent() const { return m_Parent; }
	void SetParent(Transform* parent) { m_Parent = parent; }

	vector<Transform*>& GetChildren() { return m_Children; }
	void AddChild(Transform* child);

	void SetViewMatrix(D2D1::Matrix3x2F viewMatrix) { m_ViewMatrix = viewMatrix; }

private:
	// 부모를 상대적으로 하는 나의 로컬 좌표
	Vector2 m_LocalScale = { 1.f,1.f };
	float m_LocalRotation = 0.f;
	Vector2 m_LocalPosition = { 0.f,0.f };

	// 부모 좌표계로 넘어가는 변환 행렬
	D2D1::Matrix3x2F m_MatrixLocal = D2D1::Matrix3x2F::Identity();

	// 월드 좌표계로 넘어가는 변환 행렬
	D2D1::Matrix3x2F m_MatrixWorld = D2D1::Matrix3x2F::Identity();

	// 월드 좌표계를 카메라 좌표계로 넘어가는 변환 행렬
	D2D1::Matrix3x2F m_ViewMatrix = D2D1::Matrix3x2F::Identity();

	// 월드 변환 행렬과 뷰 변환 행렬을 곱한 결과
	D2D1::Matrix3x2F m_MVMatrix = D2D1::Matrix3x2F::Identity();

private:
	Transform* m_Parent = nullptr;
	vector<Transform*> m_Children;

private:
	Vector2 m_Size;
};
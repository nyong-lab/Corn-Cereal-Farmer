#include "pch.h"
#include "CircleCollider.h"

#include "BoxCollider.h"
#include "Transform.h"
#include "Component.h"
#include "GameObject.h"

CircleCollider::CircleCollider(float radius)
	: Collider(typeid(this).name())
	, m_Radius(radius)
{

}

CircleCollider::~CircleCollider()
{

}

void CircleCollider::Start()
{
}

void CircleCollider::Update(float deltaTime)
{
	Vector2 pos = m_Transform->GetWorldPosition();
	SetBound({ pos + GetOffset(), {m_Radius * 2, m_Radius * 2 } });
}

void CircleCollider::FixedUpdate(float deltaTime)
{

}

void CircleCollider::Render()
{
	// offset을 월드 변환 행렬의 스케일 값으로 나눠서 사용하는 이유
	// 물체의 스케일이 변경되었을 때 충돌 박스의 위치와 크기를 적절하게 조절하기 위함
	// 게임 오브젝트의 로컬 좌표계에서 정의된 충돌 박스는 게임 오브젝트의 스케일에 영향을 받지 않고 고정되어 있음.
	// 하지만 게임 오브젝트가 스케일되면 충돌 박스도 같은 비율로 확대 또는 축소되어야 하는데,
	// 이를 위해 월드 변환 행렬을 사용하여 스케일 값을 보정
	// 즉 변환 행렬의 스케일 값으로 나눠주는 이유는,
	// 충돌 박스의 위치를 로컬 좌표계로 되돌려서 스케일에 상관없이 원래의 로컬 위치로 조정하기 위함


	/*Vector2 offset = { GetOffset().x / m_Transform->GetWorldMatrix()._11, GetOffset().y / m_Transform->GetWorldMatrix()._22 };

	if (!m_CurrentCollisionCount)
		GraphicsEngine::GetInstance()->DrawEllipse(offset, Vector2(m_Radius, m_Radius), COLOR::APPLEGREEN);
	else
		GraphicsEngine::GetInstance()->DrawEllipse(offset, Vector2(m_Radius, m_Radius), COLOR::EMERGENCY, true);*/

}

void CircleCollider::DebugRender()
{
	Vector2 offset = { GetOffset().x / m_Transform->GetWorldMatrix()._11, GetOffset().y / m_Transform->GetWorldMatrix()._22 };

	if (!m_CurrentCollisionCount)
		GraphicsEngine::GetInstance()->DrawEllipse(offset, Vector2(m_Radius, m_Radius), COLOR::APPLEGREEN);
	else
		GraphicsEngine::GetInstance()->DrawEllipse(offset, Vector2(m_Radius, m_Radius), COLOR::EMERGENCY, true);
}

void CircleCollider::Finalize()
{

}

void CircleCollider::OnCollisionEnter(const Manifold& collision)
{
	SetCollision(true);
	++m_CurrentCollisionCount;
}

void CircleCollider::OnCollisionStay(const Manifold& collision)
{

}

void CircleCollider::OnCollisionExit(const Manifold& collision)
{
	SetCollision(false);
	--m_CurrentCollisionCount;
	assert(0 <= m_CurrentCollisionCount);
}

bool CircleCollider::Collides(CircleCollider* circle)
{
	// 원과 원의 충돌
	D2D1_MATRIX_3X2_F originMatrix = m_Transform->GetWorldMatrix();
	Vector2 position = Vector2(originMatrix.dx, originMatrix.dy) + GetGameObject()->GetComponent<Collider>()->GetOffset();
	float radius = GetRadius();

	D2D1_MATRIX_3X2_F otherMatrix = circle->m_Transform->GetWorldMatrix();
	Vector2 otherPosition = Vector2(otherMatrix.dx, otherMatrix.dy) + circle->GetGameObject()->GetComponent<Collider>()->GetOffset();
	float otherRadius = circle->GetRadius();

	float distance = (position - otherPosition).Length();

	if (distance <= radius + otherRadius)
	{
		return true;
	}

	return false;
}

bool CircleCollider::Collides(BoxCollider* box)
{
	return box->Collides(this);
}

Vector2 CircleCollider::FindFurthestVertice(Vector2 direction)
{
	Vector2 ret = (direction.Normalize() * this->m_Radius) *
		D2D1::Matrix3x2F::Translation(m_Transform->GetWorldMatrix().dx, m_Transform->GetWorldMatrix().dy);
	return ret;
}

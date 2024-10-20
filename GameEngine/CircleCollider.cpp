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
	// offset�� ���� ��ȯ ����� ������ ������ ������ ����ϴ� ����
	// ��ü�� �������� ����Ǿ��� �� �浹 �ڽ��� ��ġ�� ũ�⸦ �����ϰ� �����ϱ� ����
	// ���� ������Ʈ�� ���� ��ǥ�迡�� ���ǵ� �浹 �ڽ��� ���� ������Ʈ�� �����Ͽ� ������ ���� �ʰ� �����Ǿ� ����.
	// ������ ���� ������Ʈ�� �����ϵǸ� �浹 �ڽ��� ���� ������ Ȯ�� �Ǵ� ��ҵǾ�� �ϴµ�,
	// �̸� ���� ���� ��ȯ ����� ����Ͽ� ������ ���� ����
	// �� ��ȯ ����� ������ ������ �����ִ� ������,
	// �浹 �ڽ��� ��ġ�� ���� ��ǥ��� �ǵ����� �����Ͽ� ������� ������ ���� ��ġ�� �����ϱ� ����


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
	// ���� ���� �浹
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

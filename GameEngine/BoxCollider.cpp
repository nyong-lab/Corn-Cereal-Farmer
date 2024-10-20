#include "pch.h"
#include "BoxCollider.h"

#include "../Math/Vector2.h"
#include "Component.h"
#include "GameObject.h"
#include "Transform.h"
#include "CircleCollider.h"


BoxCollider::BoxCollider(Vector2 size)
	: Collider(typeid(this).name())
	, m_Size(size)
{

}

BoxCollider::~BoxCollider()
{

}

void BoxCollider::Start()
{

}

void BoxCollider::Update(float deltaTime)
{
	if (m_Transform->GetSize() == Vector2{ 0.f, 0.f })
	{
		m_Transform->SetSize(m_Size);
	}

	Vector2 minVertice = { FLT_MAX, FLT_MAX };
	Vector2 maxVertice = { FLT_MIN, FLT_MIN };

	Vector2 vertices[4] = {
		GetOffset() + Vector2(-m_Size.x / 2.f, -m_Size.y / 2.f) ,
		GetOffset() + Vector2(m_Size.x / 2.f,  -m_Size.y / 2.f),
		GetOffset() + Vector2(-m_Size.x / 2.f,  +m_Size.y / 2.f),
		GetOffset() + Vector2(m_Size.x / 2.f,  +m_Size.y / 2.f)
	};

	for (int i = 0; i < 4; ++i)
	{
		Vector2 calcPoint = vertices[i] * m_Transform->GetWorldMatrix();
		minVertice.x = min(minVertice.x, calcPoint.x);
		minVertice.y = min(minVertice.y, calcPoint.y);
		maxVertice.x = max(maxVertice.x, calcPoint.x);
		maxVertice.y = max(maxVertice.y, calcPoint.y);

	}

	SetBound(Bound(minVertice, maxVertice));


}

void BoxCollider::FixedUpdate(float deltaTime)
{

}

void BoxCollider::Render()
{
	// offset을 월드 변환 행렬의 스케일 값으로 나눠서 사용하는 이유
	// 물체의 스케일이 변경되었을 때 충돌 박스의 위치와 크기를 적절하게 조절하기 위함
	// 게임 오브젝트의 로컬 좌표계에서 정의된 충돌 박스는 게임 오브젝트의 스케일에 영향을 받지 않고 고정되어 있음.
	// 하지만 게임 오브젝트가 스케일되면 충돌 박스도 같은 비율로 확대 또는 축소되어야 하는데,
	// 이를 위해 월드 변환 행렬을 사용하여 스케일 값을 보정
	// 즉 변환 행렬의 스케일 값으로 나눠주는 이유는,
	// 충돌 박스의 위치를 로컬 좌표계로 되돌려서 스케일에 상관없이 원래의 로컬 위치로 조정하기 위함

	/// rotation 을 고려하지 않았기에 폐기처분 
	/// 우리는 scale을 1로만 쓰자.. 
	/// 정상적으로 되려면 rotation을 고려한 연산 추가 및 obb 구현 해야함 
	//Vector2 offset = { GetOffset().x / m_Transform->GetWorldMatrix()._11, GetOffset().y / m_Transform->GetWorldMatrix()._22 };


	/*Vector2 offset = GetOffset();

	if (!m_CurrentCollisionCount)
		GraphicsEngine::GetInstance()->DrawRectangle(offset, Vector2(m_Size.x, m_Size.y), COLOR::APPLEGREEN);
	else
		GraphicsEngine::GetInstance()->DrawRectangle(offset, Vector2(m_Size.x, m_Size.y), COLOR::EMERGENCY, true);*/

}

void BoxCollider::DebugRender()
{
	Vector2 offset = GetOffset();

	if (!m_CurrentCollisionCount)
		GraphicsEngine::GetInstance()->DrawRectangle(offset, Vector2(m_Size.x, m_Size.y), COLOR::APPLEGREEN);
	else
		GraphicsEngine::GetInstance()->DrawRectangle(offset, Vector2(m_Size.x, m_Size.y), COLOR::EMERGENCY, true);
}

void BoxCollider::Finalize()
{

}

void BoxCollider::OnCollisionEnter(const Manifold& collision)
{
	SetCollision(true);
	++m_CurrentCollisionCount;
}

void BoxCollider::OnCollisionStay(const Manifold& collision)
{

}

void BoxCollider::OnCollisionExit(const Manifold& collision)
{
	SetCollision(false);
	--m_CurrentCollisionCount;
	assert(0 <= m_CurrentCollisionCount);
}

bool BoxCollider::Collides(CircleCollider* circle)
{
	// 박스
	D2D1_MATRIX_3X2_F originMatrix = m_Transform->GetWorldMatrix();
	Vector2 boxPosition = Vector2(originMatrix.dx, originMatrix.dy) + GetGameObject()->GetComponent<Collider>()->GetOffset();
	Vector2 boxHalfScale = GetSize() * 0.5f;

	// 원
	D2D1_MATRIX_3X2_F otherMatrix = circle->GetTransform()->GetWorldMatrix();
	Vector2 circlePosition = Vector2(otherMatrix.dx, otherMatrix.dy) + circle->GetGameObject()->GetComponent<Collider>()->GetOffset();
	float radius = circle->GetRadius();

	float minBoxX = boxPosition.x - boxHalfScale.x;
	float maxBoxX = boxPosition.x + boxHalfScale.x;
	float minBoxY = boxPosition.y - boxHalfScale.y;
	float maxBoxY = boxPosition.y + boxHalfScale.y;

	// 1. 먼저 사각형의 변들을 반지름만큼 확장해서 원의 중심좌표와 비교해서 판단
	if ((minBoxX - radius <= circlePosition.x && maxBoxX + radius >= circlePosition.x
		&& minBoxY <= circlePosition.y && maxBoxY >= circlePosition.y) ||
		(minBoxX <= circlePosition.x && maxBoxX >= circlePosition.x
			&& maxBoxY + radius >= circlePosition.y && minBoxY - radius <= circlePosition.y))
	{
		return true;
	}

	// 2. 가장 가까운 사각형의 꼭지점 좌표를 계산해서 원과의 거리를 계산 
	Vector2 boxVertex{};
	boxVertex.x = (boxPosition.x < circlePosition.x) ? maxBoxX : minBoxX;
	boxVertex.y = (boxPosition.y < circlePosition.y) ? maxBoxY : minBoxY;

	Vector2 temp = boxVertex - circlePosition;
	float distanceSquared = temp.x * temp.x + temp.y * temp.y;

	if (distanceSquared <= radius * radius)
	{
		return true;
	}

	return false;
}

bool BoxCollider::Collides(BoxCollider* box)
{
	// 월드 좌표계의 실제 위치와 오프셋 값만큼 더하는 포지션 값을 가져온다. 
	// 
	// 원본 박스
	D2D1_MATRIX_3X2_F originMatrix = m_Transform->GetWorldMatrix();
	Vector2 position = Vector2(originMatrix.dx, originMatrix.dy) + GetGameObject()->GetComponent<Collider>()->GetOffset();
	Vector2 scale = GetSize();
	scale.x *= originMatrix._11;
	scale.y *= originMatrix._22;

	// 상대 박스
	D2D1_MATRIX_3X2_F otherMatrix = box->m_Transform->GetWorldMatrix();
	Vector2 otherPosition = Vector2(otherMatrix.dx, otherMatrix.dy) + box->GetGameObject()->GetComponent<Collider>()->GetOffset();
	Vector2 otherScale = box->GetSize();
	otherScale.x *= otherMatrix._11;
	otherScale.y *= otherMatrix._22;

	// AABB 충돌처리
	Vector2 min = position - scale / 2.f;
	Vector2 max = position + scale / 2.f;
	Vector2 otherMin = otherPosition - otherScale / 2.f;
	Vector2 otherMax = otherPosition + otherScale / 2.f;

	if (min.x <= otherMax.x && max.x >= otherMin.x && min.y <= otherMax.y && max.y >= otherMin.y)
	{
		return true;
	}

	return false;
}

Vector2 BoxCollider::FindFurthestVertice(Vector2 direction)
{
	Vector2 maxVertice;
	float maxDistance = -FLT_MAX;
	Vector2 vertices[4] = {
		Vector2(-m_Size.x / 2.f, -m_Size.y / 2.f),
		Vector2(m_Size.x / 2.f,  -m_Size.y / 2.f),
		Vector2(-m_Size.x / 2.f,  +m_Size.y / 2.f),
		Vector2(m_Size.x / 2.f,  +m_Size.y / 2.f)
	};

	for (int i = 0; i < 4; ++i)
	{
		Vector2 calcPoint = vertices[i] * m_Transform->GetWorldMatrix();
		float distance = calcPoint.Dot(direction);
		if (distance > maxDistance) {
			maxDistance = distance;
			maxVertice = calcPoint;
		}
	}

	return maxVertice + GetOffset();
}

int BoxCollider::FindFurthestVerticeIndex(Vector2 direction)
{
	int maxIndex = 0;
	float maxDistance = -FLT_MAX;
	Vector2 vertices[4] = {
		 Vector2(-m_Size.x / 2.f, -m_Size.y / 2.f) ,
		 Vector2(m_Size.x / 2.f,  -m_Size.y / 2.f),
		 Vector2(-m_Size.x / 2.f,  +m_Size.y / 2.f),
		 Vector2(m_Size.x / 2.f,  +m_Size.y / 2.f)
	};

	for (int i = 0; i < 4; ++i)
	{
		Vector2 calcPoint = vertices[i] * m_Transform->GetWorldMatrix();
		float distance = calcPoint.Dot(direction);
		if (distance > maxDistance) {
			maxDistance = distance;
			maxIndex = i;
		}
	}

	return maxIndex;
}

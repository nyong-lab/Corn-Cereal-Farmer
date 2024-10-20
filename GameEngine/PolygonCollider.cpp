#include "pch.h"
#include "PolygonCollider.h"
#include "Transform.h"

PolygonCollider::PolygonCollider() :
	Collider(typeid(this).name()),
	vertices(nullptr),
	verticeCount(0)
{

}

PolygonCollider::~PolygonCollider()
{

}

void PolygonCollider::Start()
{
}

void PolygonCollider::Update(float deltaTime)
{
	Vector2 minVertice = { FLT_MAX, FLT_MAX };
	Vector2 maxVertice = { FLT_MIN, FLT_MIN };

	for (int i = 0; i < 4; ++i)
	{
		Vector2 calcPoint = vertices[i] * m_Transform->GetWorldMatrix();
		minVertice.x = min(minVertice.x, calcPoint.x);
		minVertice.y = min(minVertice.y, calcPoint.y);
		maxVertice.x = max(maxVertice.x, calcPoint.x);
		maxVertice.y = max(maxVertice.y, calcPoint.y);

	}


	for (int i = 0; i < verticeCount; ++i)
	{
		Vector2 calcPoint = vertices[i] * m_Transform->GetWorldMatrix();
		minVertice.x = min(minVertice.x, calcPoint.x);
		minVertice.y = min(minVertice.y, calcPoint.y);
		maxVertice.x = max(maxVertice.x, calcPoint.x);
		maxVertice.y = max(maxVertice.y, calcPoint.y);
	}
	SetBound(Bound(minVertice, maxVertice));
	Vector2 size = GetBound().upperBound - GetBound().lowerBound;
	Vector2 pos = (GetBound().lowerBound + GetBound().upperBound) / 2.f;

	
}

void PolygonCollider::FixedUpdate(float deltaTime)
{
}

void PolygonCollider::Render()
{

	//if (!m_CurrentCollisionCount)
	//	GraphicsEngine::GetInstance()->DrawPolygon(vertices, verticeCount, COLOR::APPLEGREEN);
	//else
	//	GraphicsEngine::GetInstance()->DrawPolygon(vertices, verticeCount, COLOR::EMERGENCY, true);
	
}

void PolygonCollider::DebugRender()
{
	if (!m_CurrentCollisionCount)
		GraphicsEngine::GetInstance()->DrawPolygon(vertices, verticeCount, COLOR::APPLEGREEN);
	else
		GraphicsEngine::GetInstance()->DrawPolygon(vertices, verticeCount, COLOR::EMERGENCY, true);
}

void PolygonCollider::Finalize()
{
}


void PolygonCollider::AddVertice(Vector2 vertice)
{
	D2D1_POINT_2F* tempArray = new D2D1_POINT_2F[verticeCount + 1];
	//double min = 100000.f;

	int tempIndex = verticeCount;

	for (int i = 0; i < verticeCount; ++i)
	{
		tempArray[i] = vertices[i];
	}


	if (vertices != nullptr)
	{
		delete[] vertices;
	}
	
	vertices = tempArray;

	if (verticeCount == 0)
	{
		vertices[0] = D2D1_POINT_2F{ vertice.x, vertice.y };
		verticeCount++;
		return;
	}

// 	for (int i = 0; i < verticeCount; ++i) {
// 		double temp = sqrt(pow(vertice.x - vertices[i].x, 2) + pow(vertice.y - vertices[i].y, 2));
// 		if (min > temp)
// 		{
// 			min = temp;
// 			tempIndex = i;
// 		}
// 	}


	++verticeCount;
// 	if (sqrt(pow(vertice.x - vertices[(verticeCount + tempIndex - 1) % verticeCount].x, 2)
// 		+ pow(vertice.y - vertices[(verticeCount + tempIndex - 1) % verticeCount].y, 2))
// 	>
// 		sqrt(pow(vertice.x - vertices[(verticeCount + tempIndex + 1) % verticeCount].x, 2)
// 			+ pow(vertice.y - vertices[(verticeCount + tempIndex + 1) % verticeCount].y, 2)))
// 	{
// 		tempIndex = (tempIndex + 1) % verticeCount;
// 	}


	//tempIndex = (tempIndex + 1) % verticeCount;

// 	for (int i = 0; i > tempIndex; --i) {
// 		vertices[i] = vertices[i - 1];
// 	}

	vertices[tempIndex] = D2D1_POINT_2F{ vertice.x, vertice.y };

}

void PolygonCollider::OnCollisionEnter(const Manifold& collision)
{
	SetCollision(true);
	++m_CurrentCollisionCount;
}

void PolygonCollider::OnCollisionStay(const Manifold& collision)
{

}

void PolygonCollider::OnCollisionExit(const Manifold& collision)
{
	SetCollision(false);
	--m_CurrentCollisionCount;
	assert(0 <= m_CurrentCollisionCount);
}


bool PolygonCollider::Collides(CircleCollider* circle)
{
	return false;
}

bool PolygonCollider::Collides(BoxCollider* box)
{
	return false;
}

Vector2 PolygonCollider::FindFurthestVertice(Vector2 direction)
{
	Vector2 maxVertice;
	float maxDistance = -FLT_MAX;

	for (int i = 0; i < verticeCount; ++i)
	{
		Vector2 calcPoint = vertices[i] * m_Transform->GetWorldMatrix();
		float distance = calcPoint.Dot(direction);
		if (distance > maxDistance) {
			maxDistance = distance;
			maxVertice = calcPoint;
		}
	}

	return maxVertice;
}

int PolygonCollider::FindFurthestVerticeIndex(Vector2 direction)
{
	int maxIndex = 0;
	float maxDistance = -FLT_MAX;

	for (int i = 0; i < verticeCount; ++i)
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


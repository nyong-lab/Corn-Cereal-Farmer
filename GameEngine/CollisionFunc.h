#pragma once

struct Manifold;

struct Edge
{
	double distance;
	Vector2 normal;
	int index;
};

struct SimplexVertex
{
	Vector2 point1;	// first�� ����Ʈ
	Vector2 point2; // second�� ����Ʈ
	Vector2 point; // point2 - point1
	float u;	// unnormalized barycentric coordinate for closest point �ϳ��� �־ u, v �ϴ°� �����ϴϱ�
	int index1; // point1�� �ε���
	int index2;	// point2�� �ε���
};

struct Simplex
{
	SimplexVertex vertexA, vertexB, vertexC;
	int count;


	Vector2 GetSearchDirection() const;
	Vector2 ComputeVoronoiRegion(const Vector2& q);
	Vector2 ComputeVoronoiRegionTriangle(Vector2 q);
};

namespace CollisionFunc
{



	Edge FindClosestEdge(vector<Vector2>& simplex);
	bool CheckGJK(Manifold* manifold, Collider* first, Collider* second);
	void EPAProcess(Manifold* manifold, Simplex* simplex, Collider* first, Collider* second);
	Vector2 Support(Collider* first, Collider* second, Vector2 direction);
};


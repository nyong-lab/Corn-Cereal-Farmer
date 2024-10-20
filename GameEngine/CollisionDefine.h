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
	Vector2 point1;	// first꺼 포인트
	Vector2 point2; // second꺼 포인트
	Vector2 point; // point2 - point1
	float u = 0;	// unnormalized barycentric coordinate for closest point 하나만 있어도 u, v 하는게 가능하니깐
	int index1  = 0; // point1의 인덱스
	int index2 = 0;	// point2의 인덱스
};

struct Simplex
{
	SimplexVertex vertexA, vertexB, vertexC;
	int count;


	Vector2 GetSearchDirection() const;
	void ComputeVoronoiRegion();
	void ComputeVoronoiRegionTriangle();
};






namespace CollisionFunc
{



	Edge FindClosestEdge(vector<Vector2>& simplex);
	bool CheckGJK(Manifold* manifold, Collider* first, Collider* second);
	void EPAProcess(Manifold* manifold, Simplex* simplex, Collider* first, Collider* second);
	Vector2 Support(Collider* first, Collider* second, Vector2 direction);
};


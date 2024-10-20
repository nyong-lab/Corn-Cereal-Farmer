#include "pch.h"
#include "CollisionFunc.h"
#include "Collider.h"
#include "Manifold.h"

Edge CollisionFunc::FindClosestEdge(vector<Vector2>& simplex)
{
	Edge closest{};

	closest.distance = DBL_MAX;

	for (int i = 0; i < simplex.size(); ++i)
	{
		//compute the next point index
		int j = i + 1 == simplex.size() ? 0 : i + 1;

		Vector2 a = simplex[i];
		Vector2 b = simplex[j];

		// ab 벡터
		Vector2 e = b - a;

		Vector2 oa = a;

		// get the vector from the edge towards the origin
		// 이거 벡터 감김으로 보완해보자
		Vector2 n;
		//= TripleProduct(e, oa, e);

		float sgn = e.Cross(a);
		if (sgn > 0.f)
		{
			n = Cross(1.f, e);
		}
		else
		{
			n = Cross(e, 1.f);
		}

		n = n.Normalize();

		double d = n.Dot(a);

		if (d < closest.distance)
		{
			closest.distance = d;
			closest.normal = n;
			closest.index = j;
		}
	}
	return closest;
}

Vector2 Simplex::GetSearchDirection() const
{
	switch (count)
	{
		case 1:
			return -vertexA.point;
		case 2:
		{
			Vector2 edgeAB = vertexB.point - vertexA.point;
			float sgn = edgeAB.Cross(-vertexA.point);
			if (sgn > 0.f)
			{
				return Cross(1.f, edgeAB);
			}
			else
			{
				return Cross(edgeAB, 1.f);
			}
		}

		default:
			assert(false);
			return Vector2(0.0f, 0.0f);
	}
}

Vector2 Simplex::ComputeVoronoiRegion(const Vector2& q)
{
	Vector2 a = vertexA.point;
	Vector2 b = vertexB.point;

	Vector2 normalizedVector = (b - a).Normalize();
	float ablength = (b - a).length();
	float v = (q - a).Dot(normalizedVector) / ablength;
	float u = (b - q).Dot(normalizedVector) / ablength;

	// G(u, v)  = uA + vB
	// B 영역에 있다. 
	if (u <= 0)
	{
		// 심플렉스 크기를 줄인다. 다른 점 A가 영향을 미치지 않기 때문에
		vertexA = vertexB;
		vertexA.u = 1.0f;
		count = 1;
		return b;
	}
	// A영역에 있다. 
	else if (v <= 0)
	{
		// 심플렉스 크기를 줄인다. 다른 점 B가 영향을 미치지 않기 때문에
		vertexA.u = 1.0f;
		count = 1;
		return a;
	}

	// AB사이에 있다.	

	vertexA.u = u;
	vertexB.u = v;
	count = 2;
	return a * u + b * v;
}

Vector2 Simplex::ComputeVoronoiRegionTriangle(Vector2 q)
{

	Vector2 a = vertexA.point;
	Vector2 b = vertexB.point;
	Vector2 c = vertexC.point;

	float uAB, vAB, uBC, vBC, uCA, vCA;
	float uABC, vABC, wABC;

	Vector2 normalizedVectorAB = (b - a).Normalize();
	float lengthAB = (b - a).length();
	Vector2 normalizedVectorBC = (c - b).Normalize();
	float lengthBC = (c - b).length();
	Vector2 normalizedVectorCA = (a - c).Normalize();
	float lengthCA = (a - c).length();

	vAB = (q - a).Dot(normalizedVectorAB) / lengthAB;
	uAB = (b - q).Dot(normalizedVectorAB) / lengthAB;

	vBC = (q - b).Dot(normalizedVectorBC) / lengthBC;
	uBC = (c - q).Dot(normalizedVectorBC) / lengthBC;

	vCA = (q - c).Dot(normalizedVectorCA) / lengthCA;
	uCA = (a - q).Dot(normalizedVectorCA) / lengthCA;


	float areaABC = (b - a).Cross(c - a) / 2.f;
	float areaQBC, areaQCA, areaQAB;
	areaQBC = (b - q).Cross(c - q) / 2.f;
	areaQCA = (c - q).Cross(a - q) / 2.f;
	areaQAB = (a - q).Cross(b - q) / 2.f;

	uABC = areaQBC * areaABC;
	vABC = areaQCA * areaABC;
	wABC = areaQAB * areaABC;


	// 지역 A테스트
	if (vAB <= 0 && uCA <= 0)
	{
		vertexA.u = 1.0f;
		count = 1;
		return a;
	}
	else if (uAB <= 0 && vBC <= 0)
	{
		vertexA = vertexB;
		vertexA.u = 1.0f;
		count = 1;
		return b;
	}
	else if (vCA <= 0 && uBC <= 0)
	{
		vertexA = vertexC;
		vertexA.u = 1.0f;
		count = 1;
		return c;
	}


	// AB 지역 테스트
	if (uAB > 0 && vAB > 0 && wABC <= 0)
	{
		vertexA.u = uAB;
		vertexB.u = vAB;
		count = 2;
		return a * uAB + b * vAB;
	}
	else if (uBC > 0 && vBC > 0 && uABC <= 0)
	{
		vertexA = vertexB;
		vertexB = vertexC;
		vertexA.u = uBC;
		vertexB.u = vBC;
		count = 2;
		return b * uBC + c * vBC;
	}
	else if (uCA > 0 && vCA > 0 && vABC <= 0)
	{
		vertexB = vertexA;
		vertexA = vertexC;
		vertexA.u = uCA;
		vertexB.u = vCA;
		count = 2;
		return c * uCA + a * vCA;
	}

	assert(uABC > 0 && vABC > 0 && wABC > 0);
	vertexA.u = uABC;
	vertexB.u = vABC;
	vertexC.u = wABC;

	count = 3;

	return q;
}

bool CollisionFunc::CheckGJK(Manifold* manifold, Collider* first, Collider* second)
{
	Simplex simplex;

	Vector2 direction{ 1.f, 0.f };

	simplex.vertexA.index1 = first->FindFurthestVerticeIndex(-direction);
	simplex.vertexA.index2 = second->FindFurthestVerticeIndex(direction);
	// 사실 위에 두개 없어도 되네?
	simplex.vertexA.point1 = first->FindFurthestVertice(-direction);
	simplex.vertexA.point2 = second->FindFurthestVertice(direction);
	simplex.vertexA.point = simplex.vertexA.point2 - simplex.vertexA.point1;
	simplex.vertexA.u = 1.f;
	simplex.count = 1;


	// Get simplex vertices as an array.
	SimplexVertex* vertices = &simplex.vertexA;

	// These store the vertices of the last simplex so that we
	// can check for duplicates and prevent cycling.(이부분에 초점을 두자 )
	// 중복처리를 위해 써주는 코드.
	int save1[3], save2[3];
	int saveCount = 0;



	const int maxIters = 20;
	Vector2 origin = Vector2(0.f, 0.f);
	Vector2 resultVoronoi;
	int iter = 0;
	while (iter < maxIters)
	{
		saveCount = simplex.count;
		for (int i = 0; i < saveCount; ++i)
		{
			save1[i] = vertices[i].index1;
			save2[i] = vertices[i].index2;
		}


		switch (simplex.count)
		{

			case 1:
				break;
			case 2:
				resultVoronoi = simplex.ComputeVoronoiRegion(origin);
				break;
			case 3:
				resultVoronoi = simplex.ComputeVoronoiRegionTriangle(origin);
				break;
			default:
				assert(false);
				break;
		}


		if (simplex.count == 3)
		{
			manifold->contactCount++;
			EPAProcess(manifold, &simplex, first, second);
			return true;
		}

		direction = simplex.GetSearchDirection();


		if (direction.length() == 0.0f)
		{
			break;
		}

		SimplexVertex* vertex = vertices + simplex.count;


		vertex->index1 = first->FindFurthestVerticeIndex(-direction);
		vertex->index2 = second->FindFurthestVerticeIndex(direction);
		// 사실 위에 두개 없어도 되네?
		vertex->point1 = first->FindFurthestVertice(-direction);
		vertex->point2 = second->FindFurthestVertice(direction);
		// 하지만 밑에께 더 빠르고 이렇게 하고싶으면 해도됨
// 		vertex->point2 = second->GetVertices()[vertex->index2] * second->transform->GetTransformMatrix();
		vertex->point = vertex->point2 - vertex->point1;

		++iter;


		// Check for duplicate support points. This is the main termination criteria.
		bool duplicate = false;
		for (int i = 0; i < saveCount; ++i)
		{
			if (vertex->index1 == save1[i] && vertex->index2 == save2[i])
			{
				duplicate = true;
				break;
			}
		}

		// If we found a duplicate support point we must exit to avoid cycling.
		if (duplicate)
		{
			break;
		}


		++simplex.count;

	}



	return false;
}

void CollisionFunc::EPAProcess(Manifold* manifold, Simplex* simplex, Collider* first, Collider* second)
{

	vector<Vector2> simplexVector;
	simplexVector.push_back(simplex->vertexA.point);
	simplexVector.push_back(simplex->vertexB.point);
	simplexVector.push_back(simplex->vertexC.point);

	while (true)
	{
		Edge edge = FindClosestEdge(simplexVector);

		Vector2 point = Support(first, second, edge.normal);

		double d = point.Dot(edge.normal);

		double ss = d - edge.distance;
		// 이정도 오차는..
		/// 이거 오차 이하로 떠러지면..
		if (d - edge.distance < 1e-4)
		{
			// 이 상황이 되면 더이상 확장할 수 없고 이게 최종 최단거리이다.

			manifold->normal = edge.normal;
			manifold->depth = (float)d;
			//D2DEngine::GetInstance()->DrawLine(manifold->normal.x, manifold->normal.y, manifold->normal.x * manifold->depth, manifold->normal.y * manifold->depth);
			return;
		}
		else
		{
			vector<Vector2>::iterator iter = simplexVector.begin() + edge.index;
			simplexVector.insert(iter, point);
		}
	}
}

Vector2 CollisionFunc::Support(Collider* first, Collider* second, Vector2 direction)
{
    return  second->FindFurthestVertice(direction) - first->FindFurthestVertice(-direction);
}

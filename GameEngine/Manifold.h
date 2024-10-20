#pragma once
#include "Vector2.h"

struct Manifold
{
	Manifold(Collider* collider1, Collider* collider2)
		: collider1(collider1)
		, collider2(collider2)
		, normal()
		, depth(0.f)
		, contactCount(0)
		, myCollider(nullptr)
		, otherCollider(nullptr)
		, otherObject(nullptr)
	{}

	Manifold() :
		collider1(nullptr),
		collider2(nullptr),
		normal{},
		depth(0.f),
		contactCount(0), 
		myCollider(nullptr), 
		otherCollider(nullptr), 
		otherObject(nullptr)

	{
	}

	Collider* collider1;
	Collider* collider2;

	Vector2 normal;
	float depth;

	int contactCount;

	Collider* myCollider;
	Collider* otherCollider;
	GameObject* otherObject;


public:
	void Solve();
	void SolveContact();
};

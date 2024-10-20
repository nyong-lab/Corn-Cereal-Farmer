#include "pch.h"
#include "Collider.h"

#include "BoxCollider.h"
#include "CircleCollider.h"

Collider::Collider(string name) 
	: m_ID(++m_Index)
	, Component(name)
	
{
	
}

Collider::~Collider()
{

}

/// <summary>
/// Collision manager 에서 충돌체크를 통과했다면 
/// 여기서 RTTI 를 통해 충돌 검사를 한다.
/// </summary>
/// <param name="collider"></param>
/// <returns></returns>
bool Collider::Collides(Collider* collider)
{
	static const string box = typeid(BoxCollider*).name();
	static const string circle = typeid(CircleCollider*).name();

	const string& name = collider->GetName();


	if (name == box)
	{
		return Collides(dynamic_cast<BoxCollider*>(collider));
	}
	else if (name == circle)
	{
		return Collides(dynamic_cast<CircleCollider*>(collider));
	}

	assert(nullptr);

	return false;
}

/// <summary>
/// 충돌체 아이디 값
/// </summary>
unsigned int Collider::m_Index = 0;
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
/// Collision manager ���� �浹üũ�� ����ߴٸ� 
/// ���⼭ RTTI �� ���� �浹 �˻縦 �Ѵ�.
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
/// �浹ü ���̵� ��
/// </summary>
unsigned int Collider::m_Index = 0;
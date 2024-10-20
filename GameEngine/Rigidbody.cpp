#include "pch.h"
#include "Rigidbody.h"
#include "Transform.h"
#include "GameObject.h"

Rigidbody::Rigidbody() : 
	Component(typeid(this).name())
{

}

Rigidbody::~Rigidbody()
{

}

void Rigidbody::Start()
{

}

void Rigidbody::Update(float deltaTime)
{
// 	if (m_IsGravity)
// 	{
// 		ApplyForce(GRAVITY * m_Mass);
// 	}
// 
// 	ApplyDamping();
// 
// 	Vector2 acceleration = m_Force / m_Mass;
// 	m_Velocity += acceleration * deltaTime;
// 
// 	Vector2 pos = m_Transform->GetLocalPosition();
// 	pos += m_Velocity * deltaTime;
// 	m_Transform->SetLocalPosition(pos);
// 
// 	m_Force = Vector2(0.0f, 0.0f);
}

void Rigidbody::FixedUpdate(float deltaTime)
{

}

void Rigidbody::Render()
{

}

void Rigidbody::Finalize()
{

}

void Rigidbody::ApplyForce(const Vector2& force)
{
	m_Force += force;
}

void Rigidbody::ApplyDamping()
{
	
	m_Velocity = m_Velocity * (1.0f - linearDamping);

}

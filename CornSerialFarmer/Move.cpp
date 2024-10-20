#include "Move.h"
#include "ZicoMath.h"
#include "Input.h"
#include "Transform.h"
#include "EventManager.h"


Move::Move() :
	MonoBehaviour(typeid(this).name())
{

}

Move::~Move()
{

}

void Move::Start()
{

}

void Move::Update(float deltaTime)
{
	Vector2 pos = m_Transform->GetLocalPosition();
	float rot = m_Transform->GetLocalRotation();

	if (Input::GetKey(KEY::RIGHT) || Input::GetKey(KEY::D))
	{
		pos.x += 300 * deltaTime;
	}
	if (Input::GetKey(KEY::LEFT) || Input::GetKey(KEY::A))
	{
		pos.x -= 300 * deltaTime;
	}
	if (Input::GetKey(KEY::UP) || Input::GetKey(KEY::W))
	{
		pos.y -= 300 * deltaTime;
	}
	if (Input::GetKey(KEY::DOWN) || Input::GetKey(KEY::S))
	{
		pos.y += 300 * deltaTime;
	}
	/*if (Input::GetKey(KEY::Q))
	{
		rot -= 500 * deltaTime;
	}
	if (Input::GetKey(KEY::E))
	{
		rot += 500 * deltaTime;
	}*/


	m_Transform->SetLocalPosition(pos);
	m_Transform->SetLocalRotation(rot);
}

void Move::FixedUpdate(float deltaTime)
{

}

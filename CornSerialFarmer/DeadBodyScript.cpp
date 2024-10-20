#include "DeadBodyScript.h"
#include "Transform.h"
#include "EventManager.h"
#include "GameObject.h"
#include "Input.h"
#include <typeinfo>
#include "../GraphicsEngine/GraphicsEngine.h"


DeadBodyScript::DeadBodyScript()
	: MonoBehaviour(typeid(this).name())
{

}

DeadBodyScript::~DeadBodyScript()
{

}

void DeadBodyScript::Start()
{
	Vector2 pos{ 150,-200 };
	GetTransform()->SetLocalPosition(pos);

	Vector2 scale{ 1,1 };
	GetTransform()->SetLocalScale(scale);
}

void DeadBodyScript::Update(float deltaTime)
{

}

void DeadBodyScript::FixedUpdate(float deltaTime)
{
	
}

void DeadBodyScript::Finalize()
{

}

void DeadBodyScript::OnCollisionEnter(const Manifold& collision)
{

}

void DeadBodyScript::OnCollisionStay(const Manifold& collision)
{

}

void DeadBodyScript::OnCollisionExit(const Manifold& collision)
{

}

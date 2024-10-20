#include "PoliceViewScript.h"
#include "Transform.h"
#include "EventManager.h"
#include "Input.h"
#include "GameObject.h"

#include <typeinfo>

#include "Collider.h"

#include "FarmerScript.h"
#include "PoliceScript.h"
#include "ObjectDataScript.h"

PoliceViewScript::PoliceViewScript()
	:MonoBehaviour(typeid(this).name())
{

}

PoliceViewScript::~PoliceViewScript()
{

}

void PoliceViewScript::Start()
{

}

void PoliceViewScript::Update(float deltaTime)
{

}

void PoliceViewScript::FixedUpdate(float deltaTime)
{

}

void PoliceViewScript::Finalize()
{

}

void PoliceViewScript::OnCollisionEnter(const Manifold& collision)
{
	if (collision.otherObject->GetObjectType() == OBJECT_TYPE::PLAYER)
	{
		if (dynamic_cast<FarmerScript*>(collision.otherObject->GetComponent<MonoBehaviour>())->haveDeadBody == true)
		{
			dynamic_cast<FarmerScript*>(collision.otherObject->GetComponent<MonoBehaviour>())->isGameOver = true;
			dynamic_cast<PoliceScript*>(collision.myCollider->GetGameObject()->GetObjectParent()->GetComponent<MonoBehaviour>())->isCatch = "true";
		}
	}

	if (collision.otherObject->GetObjectType() == OBJECT_TYPE::BUILDING)
	{
		if (dynamic_cast<ObjectDataScript*>(collision.otherObject->GetComponent<MonoBehaviour>())->isDeadBodyHave == true)
		{
			
			dynamic_cast<PoliceScript*>(collision.myCollider->GetGameObject()->GetObjectParent()->GetComponent<MonoBehaviour>())->isCatch = "true";

		}
		
	}
}

void PoliceViewScript::OnCollisionStay(const Manifold& collision)
{

}

void PoliceViewScript::OnCollisionExit(const Manifold& collision)
{

}

#include "Police2ViewScript.h"
#include "Transform.h"
#include "EventManager.h"
#include "Input.h"
#include "GameObject.h"

#include <typeinfo>

#include "Collider.h"

#include "FarmerScript.h"
#include "Police2Script.h"
#include "ObjectDataScript.h"

Police2ViewScript::Police2ViewScript()
	:MonoBehaviour(typeid(this).name())
{

}

Police2ViewScript::~Police2ViewScript()
{

}

void Police2ViewScript::Start()
{

}

void Police2ViewScript::Update(float deltaTime)
{

}

void Police2ViewScript::FixedUpdate(float deltaTime)
{

}

void Police2ViewScript::Finalize()
{

}

void Police2ViewScript::OnCollisionEnter(const Manifold& collision)
{
	if (collision.otherObject->GetObjectType() == OBJECT_TYPE::PLAYER)
	{
		if (dynamic_cast<FarmerScript*>(collision.otherObject->GetComponent<MonoBehaviour>())->haveDeadBody == true)
		{
			dynamic_cast<FarmerScript*>(collision.otherObject->GetComponent<MonoBehaviour>())->isGameOver = true;
			dynamic_cast<Police2Script*>(collision.myCollider->GetGameObject()->GetObjectParent()->GetComponent<MonoBehaviour>())->isCatch = "true";
		}
	}

	if (collision.otherObject->GetObjectType() == OBJECT_TYPE::BUILDING)
	{
		if (dynamic_cast<ObjectDataScript*>(collision.otherObject->GetComponent<MonoBehaviour>())->isDeadBodyHave == true)
		{
			dynamic_cast<Police2Script*>(collision.myCollider->GetGameObject()->GetObjectParent()->GetComponent<MonoBehaviour>())->isCatch = "true";
		}

	}
}

void Police2ViewScript::OnCollisionStay(const Manifold& collision)
{

}

void Police2ViewScript::OnCollisionExit(const Manifold& collision)
{

}

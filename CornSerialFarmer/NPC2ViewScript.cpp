#include "NPC2ViewScript.h"
#include "Transform.h"
#include "EventManager.h"
#include "Input.h"
#include "GameObject.h"

#include <typeinfo>

#include "Collider.h"
#include "NPC2Script.h"
#include "ObjectDataScript.h"


NPC2ViewScript::NPC2ViewScript()
	:MonoBehaviour(typeid(this).name())
{

}

NPC2ViewScript::~NPC2ViewScript()
{

}

void NPC2ViewScript::Start()
{

}

void NPC2ViewScript::Update(float deltaTime)
{

}

void NPC2ViewScript::FixedUpdate(float deltaTime)
{

}

void NPC2ViewScript::Finalize()
{

}

void NPC2ViewScript::OnCollisionEnter(const Manifold& collision)
{
	if (collision.otherObject->GetObjectType() == OBJECT_TYPE::BUILDING && dynamic_cast<ObjectDataScript*>(collision.otherObject->GetComponent<MonoBehaviour>())->isDeadBodyHave == true)
	{
		Vector2 bodyPosCheck = collision.otherObject->GetTransform()->GetLocalPosition();
		dynamic_cast<NPC2Script*>(collision.myCollider->GetGameObject()->GetObjectParent()->GetComponent<MonoBehaviour>())->deadBodyCollisionCheck = true;
		dynamic_cast<NPC2Script*>(collision.myCollider->GetGameObject()->GetObjectParent()->GetComponent<MonoBehaviour>())->bodyPos = bodyPosCheck;
	}
}

void NPC2ViewScript::OnCollisionStay(const Manifold& collision)
{
	
}

void NPC2ViewScript::OnCollisionExit(const Manifold& collision)
{
	dynamic_cast<NPC2Script*>(collision.myCollider->GetGameObject()->GetObjectParent()->GetComponent<MonoBehaviour>())->deadBodyCollisionCheck = false;
}

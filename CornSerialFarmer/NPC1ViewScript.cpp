#include "NPC1ViewScript.h"
#include "Transform.h"
#include "EventManager.h"
#include "Input.h"
#include "GameObject.h"

#include <typeinfo>

#include "Collider.h"

#include "NPC1Script.h"
#include "ObjectDataScript.h"

NPC1ViewScript::NPC1ViewScript()
	:MonoBehaviour(typeid(this).name())
{

}

NPC1ViewScript::~NPC1ViewScript()
{

}

void NPC1ViewScript::Start()
{

}

void NPC1ViewScript::Update(float deltaTime)
{
	
}

void NPC1ViewScript::FixedUpdate(float deltaTime)
{

}

void NPC1ViewScript::Finalize()
{

}

void NPC1ViewScript::OnCollisionEnter(const Manifold& collision)
{

	if (collision.otherObject->GetObjectType() == OBJECT_TYPE::BUILDING && dynamic_cast<ObjectDataScript*>(collision.otherObject->GetComponent<MonoBehaviour>())->isDeadBodyHave == true)
	{
		Vector2 bodyPosCheck = collision.otherObject->GetTransform()->GetLocalPosition();
		dynamic_cast<NPC1Script*>(collision.myCollider->GetGameObject()->GetObjectParent()->GetComponent<MonoBehaviour>())->deadBodyCollisionCheck = true;
		dynamic_cast<NPC1Script*>(collision.myCollider->GetGameObject()->GetObjectParent()->GetComponent<MonoBehaviour>())->bodyPos = bodyPosCheck;

	}

}

void NPC1ViewScript::OnCollisionStay(const Manifold& collision)
{

}

void NPC1ViewScript::OnCollisionExit(const Manifold& collision)
{
	dynamic_cast<NPC1Script*>(collision.myCollider->GetGameObject()->GetObjectParent()->GetComponent<MonoBehaviour>())->deadBodyCollisionCheck = false;
}

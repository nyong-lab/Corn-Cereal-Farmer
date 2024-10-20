#include "ObjectDataScript.h"

ObjectDataScript::ObjectDataScript(int id = 0)
	: MonoBehaviour(typeid(this).name())
	, id(id)
	, isDeadBodyHave(false)
	, inabilityGetWater(false)
	, interactionArrowCount(0)
{

}

ObjectDataScript::~ObjectDataScript()
{

}

void ObjectDataScript::Update(float deltaTime)
{
	if (isDeadBodyHave)
	{
		static bool inabilityGetWater = true;
		this->inabilityGetWater = inabilityGetWater;
	}
}

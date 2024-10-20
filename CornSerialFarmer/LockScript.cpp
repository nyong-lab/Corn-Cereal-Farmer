#include "LockScript.h"
#include "EventManager.h"
#include "Transform.h"
#include "GameplayStatics.h"
#include "GameObject.h"
LockScript::LockScript() :
	MonoBehaviour(typeid(this).name())
{

}

LockScript::~LockScript()
{

}

void LockScript::WareHouseHelper(std::any)
{
	m_IsClear = true;
}

void LockScript::Start()
{
	EventManager::GetInstance()->RegisterClient("WareHouseHelper", MakeCallInfo(&LockScript::WareHouseHelper));
}

void LockScript::Update(float deltaTime)
{
	if (m_IsClear)
	{
		m_ElipseTime += deltaTime;
		if (m_ElipseTime >= DELAY_TIME)
		{
			Vector2 pos = m_Transform->GetLocalPosition();
			pos += Vector2::Y() * 500 * deltaTime;
			m_Transform->SetLocalPosition(pos);


		}
		
	}
}

void LockScript::FixedUpdate(float deltaTime)
{

}

void LockScript::Finalize()
{

}


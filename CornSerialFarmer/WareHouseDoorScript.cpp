#include "WareHouseDoorScript.h"
#include "Transform.h"
#include "ImageRenderer.h"
#include "EventManager.h"
#include "GameplayStatics.h"
#include "GameObject.h"

WareHouseDoorScript::WareHouseDoorScript() :
	MonoBehaviour(typeid(this).name())
{
}

WareHouseDoorScript::~WareHouseDoorScript()
{
}

void WareHouseDoorScript::Start()
{
	EventManager::GetInstance()->RegisterClient("WareHouseHelper", MakeCallInfo(&WareHouseDoorScript::WareHouseHelper));
}

void WareHouseDoorScript::WareHouseHelper(std::any)
{
	m_IsClear = true;
}
void WareHouseDoorScript::Update(float deltaTime)
{
	if (m_IsClear)
	{

		m_ElipseTime += deltaTime;
		if (m_ElipseTime >= DELAY_TIME)
		{
			m_DoorRenderer->SetSliceStartPos(Vector2{900.f * static_cast<int>(m_ElipseTime / DELAY_TIME), 0.f});
		}
		if (m_ElipseTime >= 4.f)
		{
			GameplayStatics::ResumeGame();
			EventManager::GetInstance()->SendEvent("WareHouseClear", nullptr);
			GameplayStatics::DestroyObject(this->GetGameObject()->GetObjectParent());
		}

	}
}

void WareHouseDoorScript::FixedUpdate(float deltaTime)
{
}

void WareHouseDoorScript::Finalize()
{
}

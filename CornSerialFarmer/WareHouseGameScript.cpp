#include "WareHouseGameScript.h"
#include "EventManager.h"
#include "GameplayStatics.h"

WareHouseGameScript::WareHouseGameScript() :
	MonoBehaviour(typeid(this).name())
{

}

WareHouseGameScript::~WareHouseGameScript()
{

}

void WareHouseGameScript::CountDownEnd(std::any)
{
	GameplayStatics::DestroyObject(this->GetGameObject());
	EventManager::GetInstance()->SendEvent("WareHouseFail", nullptr);
	GameplayStatics::ResumeGame();

}

void WareHouseGameScript::Start()
{
	GameplayStatics::PauseGame();

	EventManager::GetInstance()->RegisterClient("CountDownEnd", MakeCallInfo(&WareHouseGameScript::CountDownEnd));
}

void WareHouseGameScript::Update(float deltaTime)
{
}

void WareHouseGameScript::FixedUpdate(float deltaTime)
{
}

void WareHouseGameScript::Finalize()
{
}

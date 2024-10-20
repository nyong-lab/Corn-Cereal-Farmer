#include "PauseButtonScript.h"
#include "EventManager.h"

PauseButtonScript::PauseButtonScript()
	: MonoBehaviour(typeid(this).name())
{

}

PauseButtonScript::~PauseButtonScript()
{

}

void PauseButtonScript::ResumeGame(std::any)
{
	m_IsClicked = false;
}

void PauseButtonScript::Start()
{
	EventManager::GetInstance()->RegisterClient("ResumeGame", MakeCallInfo(&PauseButtonScript::ResumeGame));
}

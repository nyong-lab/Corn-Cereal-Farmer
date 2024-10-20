#include "CornGameManagerScript.h"
#include <assert.h>
#include "Input.h"
#include "EventManager.h"
#include "GameplayStatics.h"
#include "GameObject.h"
#include "ImageRenderer.h"

CornGameManagerScript::CornGameManagerScript() :
	MonoBehaviour(typeid(this).name()),
	m_CornInBoxCount(0)
{
}

CornGameManagerScript::~CornGameManagerScript()
{
}

void CornGameManagerScript::CountDownEnd(std::any)
{
	EventManager::GetInstance()->SendEvent("CornGameFail", nullptr);
	GameplayStatics::ResumeGame();
	GameplayStatics::DestroyObject(this->GetGameObject()->GetObjectParent());
}

void CornGameManagerScript::Start()
{
	GameplayStatics::PauseGame();
	EventManager::GetInstance()->RegisterClient("CornComplete", MakeCallInfo(&CornGameManagerScript::CompleteCorn));
	EventManager::GetInstance()->RegisterClient("CountDownEnd", MakeCallInfo(&CornGameManagerScript::CountDownEnd));
}

void CornGameManagerScript::CompleteCorn(std::any)
{
	m_CornInBoxCount++;
}

void CornGameManagerScript::Update(float deltaTime)
{
	
	if (m_CornInBoxCount >= 4)
	{
		if (m_CornInBoxCount == 4)
		{
			EventManager::GetInstance()->SendEvent("CountDownStop", nullptr);
			m_Renderer->FadeIn(1.f);
			m_CornInBoxCount++;

		}
		m_ElipseTime += deltaTime;
		if (m_ElipseTime >= DELAY_TIME)
		{
			GameplayStatics::ResumeGame();
			EventManager::GetInstance()->SendEvent("CornGameClear", nullptr);
			GameplayStatics::DestroyObject(this->GetGameObject()->GetObjectParent());
		}

	}
}

void CornGameManagerScript::FixedUpdate(float deltaTime)
{
}

void CornGameManagerScript::Finalize()
{
}

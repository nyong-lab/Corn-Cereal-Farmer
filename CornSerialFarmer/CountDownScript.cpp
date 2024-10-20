#include "CountDownScript.h"
#include "Animator.h"
#include "Animation.h"
#include "EventManager.h"

CountDownScript::CountDownScript() :
	MonoBehaviour(typeid(this).name())
{
}

CountDownScript::~CountDownScript()
{
}

void CountDownScript::CountDownStop(std::any)
{
	m_Animator->GetCurrentAnimation()->SetFrameFixed(
		m_Animator->GetCurrentAnimation()->GetCurrentAnimationIndex()
	);
}

void CountDownScript::Start()
{
	EventManager::GetInstance()->RegisterClient("CountDownStop", MakeCallInfo(&CountDownScript::CountDownStop));
	m_Animator->Play(L"CountDownAnim", false);
}

void CountDownScript::Update(float deltaTime)
{
	if (m_Animator->GetCurrentAnimation()->IsAnimationFinished())
	{
		EventManager::GetInstance()->SendEvent("CountDownEnd", nullptr);
	}
}

void CountDownScript::FixedUpdate(float deltaTime)
{
}

void CountDownScript::Finalize()
{
}

#include "FarmNoWaterState.h"
#include "StateMachine.h"

#include "GameObject.h"
#include "Component.h"
#include "Animation.h"
#include "Animator.h"

FarmNoWaterState::FarmNoWaterState(StateMachine* owner)
	:FSMState(owner, "FarmNoWater")
{

}

FarmNoWaterState::~FarmNoWaterState()
{

}

void FarmNoWaterState::Enter()
{

}

void FarmNoWaterState::Update(float deltaTime)
{
	if (m_Machine->m_DetailState.compare("NoSeed") == 0)
	{
		m_Machine->m_Owner->GetComponent<Animator>()->Play(L"farmNoSeed", true);
	}
	if (m_Machine->m_DetailState.compare("Seed") == 0)
	{
		m_Machine->m_Owner->GetComponent<Animator>()->Play(L"farmSeed", true);
	}
	if (m_Machine->m_DetailState.compare("First") == 0)
	{
		m_Machine->m_Owner->GetComponent<Animator>()->Play(L"farmFirst", true);
	}
	if (m_Machine->m_DetailState.compare("Second") == 0)
	{
		m_Machine->m_Owner->GetComponent<Animator>()->Play(L"farmSecond", true);
	}
	if (m_Machine->m_DetailState.compare("Third") == 0)
	{
		m_Machine->m_Owner->GetComponent<Animator>()->Play(L"farmThird", true);
	}
}

void FarmNoWaterState::Exit()
{

}

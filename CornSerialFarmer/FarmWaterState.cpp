#include "FarmWaterState.h"
#include "StateMachine.h"

#include "GameObject.h"
#include "Component.h"
#include "Animation.h"
#include "Animator.h"

FarmWaterState::FarmWaterState(StateMachine* owner)
	:FSMState(owner, "FarmWater")
{

}

FarmWaterState::~FarmWaterState()
{

}

void FarmWaterState::Enter()
{

}

void FarmWaterState::Update(float deltaTime)
{
	if (m_Machine->m_DetailState.compare("NoSeed") == 0)
	{
		m_Machine->m_Owner->GetComponent<Animator>()->Play(L"farmNoSeedWater", true);
	}
	if (m_Machine->m_DetailState.compare("Seed") == 0)
	{
		m_Machine->m_Owner->GetComponent<Animator>()->Play(L"farmSeedWater", true);
	}
	if (m_Machine->m_DetailState.compare("First") == 0)
	{
		m_Machine->m_Owner->GetComponent<Animator>()->Play(L"farmFirstWater", true);
	}
	if (m_Machine->m_DetailState.compare("Second") == 0)
	{
		m_Machine->m_Owner->GetComponent<Animator>()->Play(L"farmSecondWater", true);
	}
	if (m_Machine->m_DetailState.compare("Third") == 0)
	{
		m_Machine->m_Owner->GetComponent<Animator>()->Play(L"farmThirdWater", true);
	}
}

void FarmWaterState::Exit()
{

}

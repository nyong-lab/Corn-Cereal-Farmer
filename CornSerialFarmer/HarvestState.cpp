#include "HarvestState.h"
#include "StateMachine.h"
#include "Input.h"

#include "GameObject.h"
#include "Component.h"
#include "Transform.h"
#include "Animator.h"
#include "Animation.h"

HarvestState::HarvestState(StateMachine* owner)
	:FSMState(owner, "Harvest")
{

}

HarvestState::~HarvestState()
{

}

void HarvestState::Enter()
{

}

void HarvestState::Update(float deltaTime)
{
	m_Machine->m_Owner->GetComponent<Animator>()->Play(L"farmerHarvest", false);
}

void HarvestState::Exit()
{

}

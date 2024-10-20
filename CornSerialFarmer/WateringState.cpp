#include "WateringState.h"
#include "StateMachine.h"
#include "Input.h"

#include "GameObject.h"
#include "Component.h"
#include "Transform.h"
#include "Animator.h"
#include "Animation.h"
#include "FarmerScript.h"

WateringState::WateringState(StateMachine* owner)
	: FSMState(owner, "Watering")
{

}

WateringState::~WateringState()
{
	
}

void WateringState::Enter()
{

}

void WateringState::Update(float deltaTime)
{
	m_Machine->m_Owner->GetComponent<Animator>()->Play(L"farmerWatering", false);
}

void WateringState::Exit()
{

}

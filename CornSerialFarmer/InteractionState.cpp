#include "InteractionState.h"
#include "StateMachine.h"

#include "GameObject.h"
#include "Component.h"
#include "Transform.h"
#include "Animator.h"
#include "Animation.h"

InteractionState::InteractionState(StateMachine* onwer)
	:FSMState(onwer, "Interaction")
{

}

InteractionState::~InteractionState()
{

}

void InteractionState::Enter()
{

}

void InteractionState::Update(float deltaTime)
{
	m_Machine->m_Owner->GetComponent<Animator>()->Play(L"farmerInteraction", false);
}

void InteractionState::Exit()
{

}

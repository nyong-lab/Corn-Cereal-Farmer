#include "PoliceDieState.h"
#include "StateMachine.h"
#include "Input.h"

#include "GameObject.h"
#include "Component.h"
#include "Transform.h"
#include "Animator.h"
#include "Animation.h"
#include "BoxCollider.h"

PoliceDieState::PoliceDieState(StateMachine* owner)
	:FSMState(owner, "PoliceDie")
{

}

PoliceDieState::~PoliceDieState()
{

}

void PoliceDieState::Enter()
{
	
}

void PoliceDieState::Update(float deltaTime)
{

}

void PoliceDieState::Exit()
{

}

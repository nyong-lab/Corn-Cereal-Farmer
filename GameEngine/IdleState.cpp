#include "pch.h"
#include "IdleState.h"

IdleState::IdleState(StateMachine* owner)
	: FSMState(owner, "IDEL")
{

}

IdleState::~IdleState()
{

}

void IdleState::Enter()
{

}

void IdleState::Update()
{

}

void IdleState::Exit()
{

}

bool IdleState::CheckTransition()
{
	return true;
}


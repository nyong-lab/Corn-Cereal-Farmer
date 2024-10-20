#include "pch.h"
#include "FSMState.h"

#include "StateMachine.h"

FSMState::FSMState(StateMachine* machine, string fsmState)
	: m_FSMState(fsmState)
	, m_Machine(machine)
{

}

FSMState::~FSMState()
{
	
}

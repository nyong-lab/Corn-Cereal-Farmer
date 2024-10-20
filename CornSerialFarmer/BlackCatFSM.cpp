#include "BlackCatFSM.h"

#include "GameObject.h"

BlackCatFSM::BlackCatFSM(GameObject* owner)
	: m_BlackCatIdleState(this)
	, m_BlackCatMoveState(this)
{
	m_Owner = owner;

	AddState(&m_BlackCatIdleState);
	AddState(&m_BlackCatMoveState);

	string initState = "BlackCatIdle";
	SetInitialState(initState);
	m_DetailState = "IdleDown";

}

BlackCatFSM::~BlackCatFSM()
{
}

void BlackCatFSM::Update(float deltaTime)
{
	StateMachine::Update(deltaTime);
}

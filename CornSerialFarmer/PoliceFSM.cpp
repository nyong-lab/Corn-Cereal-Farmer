#include "PoliceFSM.h"

#include "GameObject.h"

PoliceFSM::PoliceFSM(GameObject* owner)
	: m_PoliceCatchState(this)
	, m_PoliceFindState(this)
	, m_PolicePatroState(this)
	, m_PoliceTraceState(this)
	, m_PoliceIdleState(this)
	, m_PoliceDieState(this)
{
	m_Owner = owner;

	AddState(&m_PoliceCatchState);
	AddState(&m_PoliceFindState);
	AddState(&m_PolicePatroState);
	AddState(&m_PoliceTraceState);
	AddState(&m_PoliceIdleState);
	AddState(&m_PoliceDieState);

	string initState = "PolicePatrol";
	SetInitialState(initState);
	m_DetailState = "MoveFront";
}

PoliceFSM::~PoliceFSM()
{

}

void PoliceFSM::Update(float deltaTime)
{
	StateMachine::Update(deltaTime);
}

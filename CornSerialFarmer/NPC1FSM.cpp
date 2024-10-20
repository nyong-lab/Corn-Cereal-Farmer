#include "NPC1FSM.h"

#include "GameObject.h"
#include "Transform.h"

NPC1FSM::NPC1FSM(GameObject* owner)
	: m_NPC1PatrolState(this)
	, m_NPC1ReturnState(this)
	, m_NPC1TalkState(this)
	, m_NPC1CheckState(this)
	, m_NPC1FindState(this)
	, m_NPC1IdleState(this)
{
	m_Owner = owner;

	AddState(&m_NPC1PatrolState);
	AddState(&m_NPC1ReturnState);
	AddState(&m_NPC1TalkState);
	AddState(&m_NPC1CheckState);
	AddState(&m_NPC1FindState);
	AddState(&m_NPC1IdleState);

	string initState = "NPC1Patrol";
	SetInitialState(initState);
	m_DetailState = "MoveDown";
}

NPC1FSM::~NPC1FSM()
{

}

void NPC1FSM::Update(float deltaTime)
{
	StateMachine::Update(deltaTime);
}

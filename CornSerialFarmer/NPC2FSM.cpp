#include "NPC2FSM.h"

NPC2FSM::NPC2FSM(GameObject* owner)
	: m_NPC2TraceState(this)
	, m_NPC2ReturnState(this)
	, m_NPC2TalkState(this)
	, m_NPC2CheckState(this)
	, m_NPC2FindState(this)
	, m_NPC2IdleState(this)
{
	m_Owner = owner;

	AddState(&m_NPC2TraceState);
	AddState(&m_NPC2ReturnState);
	AddState(&m_NPC2TalkState);
	AddState(&m_NPC2CheckState);
	AddState(&m_NPC2FindState);
	AddState(&m_NPC2IdleState);

	string initState = "NPC2Trace";
	SetInitialState(initState);
	m_DetailState = "MoveFront";
}

NPC2FSM::~NPC2FSM()
{

}

void NPC2FSM::Update(float deltaTime)
{
	StateMachine::Update(deltaTime);
}
